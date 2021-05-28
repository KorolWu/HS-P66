#ifndef CAMERADEVICE_H
#define CAMERADEVICE_H

#include "GalaxyIncludes.h"
#include <QObject>

class CameraDevice : public QObject
{
    Q_OBJECT
    //---------------------------------------------------------------------------------
    /**
    \brief   用户继承采集事件处理类
    */
    //----------------------------------------------------------------------------------
    class CSampleCaptureEventHandler :public ICaptureEventHandler
    {
        //---------------------------------------------------------------------------------
        /**
        \brief   采集回调函数
        \param   objImageDataPointer      图像处理参数
        \param   pFrame                   用户参数

        \return  无
        */
        //----------------------------------------------------------------------------------
        void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam)
        {
            try
            {
                CameraDevice* pDeviceProcess = (CameraDevice*)pUserParam;

                //获取图像数据（直接将SDK中的数据头浅拷贝过来）
                unsigned char* pbuffer = (unsigned char*)objImageDataPointer->GetBuffer();
                //显示图像
                //pDeviceProcess->__ShowPicture(objImageDataPointer);

               emit pDeviceProcess->readReady(pbuffer);
            }
            catch (CGalaxyException)
            {
                //do nothing

            }
            catch (std::exception)
            {
                //do nothing
            }
        }
    };
public:

    explicit CameraDevice(QObject *parent = nullptr);
    ~CameraDevice();
signals:
    void readReady(unsigned char*);
public:
    /// 打开设备
    void OpenDevice();

    /// 关闭设备
    void CloseDevice();

    /// 开始采集
    void StartSnap();

    /// 停止采集
    void StopSnap();

    ///单拍
    void OnceSnap();

    /// 获取设备打开标识
    bool IsOpen() const;

    /// 获取设备采集标识
    bool IsSnap() const;

    /// 设置是否显示帧率标志
    void SetShowFPS(bool bIsShowFps);

    /// 获取是否显示帧率标志
    bool GetShowFPS();

    //设置曝光
    void SetExposure(int ExposureValue);

    //设置增益
    void SetGain(int GainValue);


    //注册采集回调
   //void(*m_CaptureCallback)(byte* pBuffer, void* params);
   // void* m_CaptureParams;
   // void RegisterCaptureCallback(void(*captureCallback)(byte* pBuffer, void *params), void * params);

    CGXFeatureControlPointer    m_objFeatureControlPtr;           ///< 属性控制器
    CGXFeatureControlPointer    m_objStreamFeatureControlPtr;     ///< 流层控制器对象

public:
    std::string modelName;//型号名称
    std::string sn;//序列号
    std::string ip;//相机IP
    std::string userName;//自定义名称
    gxstring                    m_strDeviceSN;                   ///< 设备序列号

    int width;  //图像宽
    int height; //图像高

    int MinExposure;//相机最小曝光
    int MaxExposure;//相机最大曝光
    int MinGain;//相机最小增益
    int MaxGain;//相机最大增益
    int CurrentExposure; //相机当前曝光
    int CurrentGain; //相机当前增益

private:

    CGXDevicePointer            m_objDevicePtr;                  ///< 设备句柄
    CGXStreamPointer            m_objStreamPtr;                  ///< 设备流对象
    //CGXBitmap*                  m_pBitmap;                       ///< 画图指针
    CSampleCaptureEventHandler* m_pSampleCaptureEventHandle;     ///< 回调指针
    bool                        m_bIsOpen;                       ///< 设备是否打开标志
    bool                        m_bIsSnap;                       ///< 设备是否开采标志
    bool                        m_bShowDeviceFPS;                ///< 显示设备帧率标志
    char                        *m_pRecordDeviceSNFPS;           ///< 设备型号及帧率信息
    //CFps                        m_objfps;                        ///< 计算帧率
    int							m_nDeviceIndex;                  ///< 设备序号
};

#endif // CAMERADEVICE_H
