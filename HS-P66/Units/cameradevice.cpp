#include "cameradevice.h"

CameraDevice::CameraDevice(QObject *parent) : QObject(parent)
{
    m_pSampleCaptureEventHandle = NULL;
    m_bIsOpen                   = false;
    m_bIsSnap                   = false;
    m_bShowDeviceFPS            = true;
    m_nDeviceIndex              = 0;
    m_strDeviceSN               = "";
    m_pSampleCaptureEventHandle = new CSampleCaptureEventHandler();
    m_pRecordDeviceSNFPS        = new char[1024];
}

CameraDevice::~CameraDevice()
{
    if (m_pSampleCaptureEventHandle != NULL)
        {
            delete m_pSampleCaptureEventHandle;
            m_pSampleCaptureEventHandle = NULL;
        }

        if (m_pRecordDeviceSNFPS != NULL)
        {
            delete[] m_pRecordDeviceSNFPS;
            m_pRecordDeviceSNFPS = NULL;
        }
}

void CameraDevice::OpenDevice()
{
    bool bIsDeviceOpen   = false;      ///< 判断设备是否已打开标志
        bool bIsStreamOpen   = false;      ///< 判断设备流是否已打开标志
        try
        {
            if (m_bIsOpen || m_strDeviceSN == "")
            {
                throw std::exception("无效参数!");
            }


            //打开设备
            m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(m_strDeviceSN,GX_ACCESS_EXCLUSIVE);
            bIsDeviceOpen = true;

            //获取属性控制器
            m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

            //获取相机属性参数
            width = m_objFeatureControlPtr->GetIntFeature("Width")->GetValue();
            height = m_objFeatureControlPtr->GetIntFeature("Height")->GetValue();

            MinExposure = m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetMin();
            MaxExposure = m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetMax();
            MinGain = m_objFeatureControlPtr->GetFloatFeature("Gain")->GetMin();
            MaxGain = m_objFeatureControlPtr->GetFloatFeature("Gain")->GetMax();

            CurrentExposure=m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetValue();
            CurrentGain= m_objFeatureControlPtr->GetFloatFeature("Gain")->GetValue();


            //设置采集模式为连续采集
            m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");

            //设置触发模式为关
            m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("On");

            //获取设备流个数
            int nCount = m_objDevicePtr->GetStreamCount();

            if (nCount > 0)
            {
                m_objStreamPtr = m_objDevicePtr->OpenStream(0);
                m_objStreamFeatureControlPtr = m_objStreamPtr->GetFeatureControl();
                bIsStreamOpen = true;
            }
            else
            {
                throw std::exception("未发现设备流!");
            }

            // 建议用户在打开网络相机之后，根据当前网络环境设置相机的流通道包长值，
            // 以提高网络相机的采集性能,设置方法参考以下代码。
            GX_DEVICE_CLASS_LIST objDeviceClass = m_objDevicePtr->GetDeviceInfo().GetDeviceClass();
            if(GX_DEVICE_CLASS_GEV == objDeviceClass)
            {
                // 判断设备是否支持流通道数据包功能
                if(true == m_objFeatureControlPtr->IsImplemented("GevSCPSPacketSize"))
                {
                    // 获取当前网络环境的最优包长值
                    int nPacketSize = m_objStreamPtr->GetOptimalPacketSize();
                    // 将最优包长值设置为当前设备的流通道包长值
                    m_objFeatureControlPtr->GetIntFeature("GevSCPSPacketSize")->SetValue(nPacketSize);
                }
            }
            m_bIsOpen = true;


            //设置心跳
            m_objFeatureControlPtr->GetIntFeature("GevHeartbeatTimeout")->SetValue(6000);


            if (!m_bIsOpen)
            {
                return;
            }

            try
            {
                //设置Buffer处理模式
                m_objStreamFeatureControlPtr->GetEnumFeature("StreamBufferHandlingMode")->SetValue("OldestFirst");

                //注册回调函数
                m_objStreamPtr->RegisterCaptureCallback(m_pSampleCaptureEventHandle, this);
            }
            catch (CGalaxyException& e)
            {
                throw e;
            }

            try
            {

                //开启流层采集
                m_objStreamPtr->StartGrab();
            }
            catch (CGalaxyException& e)
            {
                //注销回调函数
                m_objStreamPtr->UnregisterCaptureCallback();
                throw e;
            }

            try
            {
                //发送开采命令
                m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();

                m_bIsSnap = true;
            }
            catch (CGalaxyException& e)
            {
                //关闭流层采集
                m_objStreamPtr->StopGrab();

                //注销回调函数
                m_objStreamPtr->UnregisterCaptureCallback();
                throw e;
            }
            catch (std::exception& e)
            {
                //关闭流层采集
                m_objStreamPtr->StopGrab();

                //注销回调函数
                m_objStreamPtr->UnregisterCaptureCallback();
                throw e;
            }
        }
        catch (CGalaxyException& e)
        {

            //判断设备流是否已打开
            if (bIsStreamOpen)
            {
                m_objStreamPtr->Close();
            }

            //判断设备是否已打开
            if (bIsDeviceOpen)
            {
                m_objDevicePtr->Close();
            }

            m_bIsOpen = false;

            throw e;

        }
        catch (std::exception& e)
        {
            //判断设备流是否已打开
            if (bIsStreamOpen)
            {
                m_objStreamPtr->Close();
            }

            //判断设备是否已打开
            if (bIsDeviceOpen)
            {
                m_objDevicePtr->Close();
            }

            m_bIsOpen = false;

            throw e;
        }
}

void CameraDevice::CloseDevice()
{
    if (!m_bIsOpen)
        {
            return;
        }

        try
        {
            //判断是否停止采集
            if (m_bIsSnap)
            {

                //发送停采命令
                m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();

                //关闭流层采集
                m_objStreamPtr->StopGrab();

                //注销回调函数
                m_objStreamPtr->UnregisterCaptureCallback();
            }
        }
        catch (CGalaxyException)
        {
            //do noting
        }

        try
        {
            //关闭流对象
            m_objStreamPtr->Close();
        }
        catch (CGalaxyException)
        {
            //do noting
        }

        try
        {
            //关闭设备
            m_objDevicePtr->Close();
        }
        catch (CGalaxyException)
        {
            //do noting
        }

        m_bIsSnap = false;
        m_bIsOpen = false;
}

void CameraDevice::StartSnap()
{
    //判断设备是否已打开
    if (!m_bIsOpen)
    {
        return;
    }

    try
    {
        //设置Buffer处理模式
        //m_objStreamFeatureControlPtr->GetEnumFeature("StreamBufferHandlingMode")->SetValue("OldestFirst");
    }
    catch (CGalaxyException& e)
    {
        throw e;
    }

    try
    {
        //发送开采命令
        m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");
        m_bIsSnap = true;
    }
    catch (CGalaxyException& e)
    {
        //关闭流层采集
        m_objStreamPtr->StopGrab();

        //注销回调函数
        m_objStreamPtr->UnregisterCaptureCallback();
        throw e;
    }
    catch (std::exception& e)
    {
        //关闭流层采集
        m_objStreamPtr->StopGrab();

        //注销回调函数
        m_objStreamPtr->UnregisterCaptureCallback();
        throw e;
    }
}

void CameraDevice::StopSnap()
{
    //判断设备是否已打开
        if (!m_bIsOpen || !m_bIsSnap)
        {
            return;
        }

        try
        {
            m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("On");
            m_bIsSnap = false;
        }
        catch (CGalaxyException& e)
        {
            throw e;

        }
        catch (std::exception& e)
        {
            throw e;

        }
}

void CameraDevice::OnceSnap()
{
    try
        {
            //判断设备是否已打开
            if (!m_bIsOpen)
            {
                return;
            }

            //如果处于连续采集状态，则停止
            m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("On");
            //触发单次采集
            m_objFeatureControlPtr->GetCommandFeature("TriggerSoftware")->Execute();

        }
        catch (CGalaxyException& e)
        {
            //关闭流层采集
            m_objStreamPtr->StopGrab();

            //注销回调函数
            m_objStreamPtr->UnregisterCaptureCallback();
            throw e;
    }
}

bool CameraDevice::IsOpen() const
{
    return m_bIsOpen;
}

bool CameraDevice::IsSnap() const
{
    return m_bIsSnap;
}

void CameraDevice::SetShowFPS(bool bIsShowFps)
{
    m_bShowDeviceFPS = bIsShowFps;
}

bool CameraDevice::GetShowFPS()
{
    return m_bShowDeviceFPS;
}

void CameraDevice::SetExposure(int ExposureValue)
{
    m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue(ExposureValue);
}

void CameraDevice::SetGain(int GainValue)
{
    m_objFeatureControlPtr->GetFloatFeature("Gain")->SetValue(GainValue);
}
