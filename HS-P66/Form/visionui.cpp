#include "visionui.h"
#pragma execution_character_set("utf-8")
VisionUi::VisionUi(QWidget *parent) : QWidget(parent)
{
    m_width = parent->width();
    m_height = parent->height();
    this->resize(m_width,m_height);
    if(initCameraDevice())
    {
        init();
        if(m_mapDeviceInformation.contains("Camera_1"))
        {
            m_pVision_R->setDeviceObj(m_mapDeviceInformation["Camera_1"]);
            m_pVision_R->setGrouboxTitle("右CCD");
        }
        if(m_mapDeviceInformation.contains("Camera_2"))
        {
            m_pVision_L->setDeviceObj(m_mapDeviceInformation["Camera_2"]);
            m_pVision_L->setGrouboxTitle("左CCD");
        }
        QLOG_INFO()<<"相机连接成功";
    }
    else
        QLOG_ERROR()<<"相机初始化失败！";
}

void VisionUi::init()
{
    m_pVision_L = new VisionFrom(this);
    m_pVision_L->move(20,20);
    m_pVision_R = new VisionFrom(this);
    m_pVision_R->move(20+m_pVision_L->width(),20);
    int gw = 200;
    QString title = "Move";
    QGroupBox *group = new QGroupBox(title,this);
    group->resize(m_pVision_L->width()/3*2,gw);
    group->move(m_pVision_L->width()*2+65,475);
    for (int i = 0; i < 6 ;i++ ) {
        m_pMoveBtn[i] = new QPushButton(group);
        m_pMoveBtn[i]->resize(40,30);
        connect(m_pMoveBtn[i],&QPushButton::clicked,this,&VisionUi::onMoveButtonClicked);
    }
    m_pMoveBtn[0]->setIcon(QIcon(":/src/Image/m_up.png"));
    m_pMoveBtn[0]->move(m_pVision_L->width()/2,38);
    m_pMoveBtn[0]->setObjectName("Y+");
    QLabel *y = new QLabel("Y",group);
    y->move(m_pVision_L->width()/2+12,70);
    m_pMoveBtn[1]->setIcon(QIcon(":/src/Image/m_down.png"));
    m_pMoveBtn[1]->move(m_pVision_L->width()/2,gw/2);
    m_pMoveBtn[1]->setObjectName("Y-");
    m_pMoveBtn[2]->setIcon(QIcon(":/src/Image/m_left.png"));
    m_pMoveBtn[2]->move(8,38);
    m_pMoveBtn[2]->setObjectName("L+");
    QLabel *label = new QLabel("CCD_L",group);
    label->move(68,45);
    m_pMoveBtn[3]->setIcon(QIcon(":/src/Image/m_right.png"));
    m_pMoveBtn[3]->move(gw-38,38);
    m_pMoveBtn[3]->setObjectName("L-");
   // m_pMoveBtn[4]->setIcon(QIcon(":/src/Image/m_left.png"));
    m_pMoveBtn[4]->setObjectName("ORG");
    m_pMoveBtn[4]->setText("ORG");
    m_pMoveBtn[4]->move(8,gw/2);
    m_pinterval = new QDoubleSpinBox(group);
    m_pinterval->setMaximum(1); //单次只允许行走1mm
    m_pinterval->setMinimum(0.01);
    m_pinterval->setValue(1);
    m_pinterval->move(68,gw/2+1);
    //m_pMoveBtn[5]->setIcon(QIcon(":/src/Image/m_right.png"));
    m_pMoveBtn[5]->setObjectName("R-");
    m_pMoveBtn[5]->setText("mm");
    m_pMoveBtn[5]->move(gw-38,gw/2);
    group->setStyleSheet("QLabel{font: 20px;}QDoubleSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Min-width:45px;Min-height:25px;border-radius:5px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Min-width:90px;Min-height:25px;border-radius:5px;}QGroupBox{border: 2px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 22px;}");

}

void VisionUi::closeDevice()
{
    for(int i = 0; i < 2 ; i++)
    {
        if(m_pDeviceProcess[i] != nullptr)
        {
            m_pDeviceProcess[i]->CloseDevice();
            m_pDeviceProcess[i] = nullptr;
            delete m_pDeviceProcess[i];
        }

    }
}

bool VisionUi::initCameraDevice()
{
    try
    {
        for (int i = 0; i < 2; i++)
        {
            m_pDeviceProcess[i] = new CameraDevice;
        }
        //初始化设备库
        IGXFactory::GetInstance().Init();

        //枚举设备
        IGXFactory::GetInstance().UpdateDeviceList(1000, m_vectorDeviceInfo);

        //未检测到设备
        if (m_vectorDeviceInfo.size() <= 0)
        {
            return false;
        }

        //将设备名称显示到设备列表中
        for (uint32_t i = 0; i < m_vectorDeviceInfo.size(); i++)
        {
            //如果设备数大于4则只保留4个设备信息
            if (i >= 2)
            {
                break;
            }

            gxstring strDeviceInformation = "";
            gxstring strDeviceInformation1 = "";
            m_pDeviceProcess[i]->modelName = m_vectorDeviceInfo[i].GetModelName().c_str();
            m_pDeviceProcess[i]->sn = m_vectorDeviceInfo[i].GetSN().c_str();
            m_pDeviceProcess[i]->ip = m_vectorDeviceInfo[i].GetIP().c_str();
            m_pDeviceProcess[i]->userName = m_vectorDeviceInfo[i].GetUserID().c_str();
            m_pDeviceProcess[i]->m_strDeviceSN = m_vectorDeviceInfo[i].GetSN();
            m_mapDeviceInformation.insert(QString::fromStdString(m_pDeviceProcess[i]->userName), m_pDeviceProcess[i]);
        }
    }
    catch (CGalaxyException& e)
    {
        return false;
    }
    catch (std::exception& e)
    {
        return false;
    }
    return true;
}

void VisionUi::onMoveButtonClicked()
{
    ShareData::GetInstance()->m_isHomePosition = false;
    QString objName = sender()->objectName();
    MotionControl m;
     int val = m_pinterval->value()*2000;
    if(objName == "Y+")
    {
        m.relativeMove(3,val);
    }
    else if(objName == "Y-")
    {
        m.relativeMove(3,-1*val);
    }
    else if(objName == "L-")
    {
      m.relativeMove(1,val);
      m.relativeMove(2,-1*val);
    }
    else if(objName == "L+")
    {
        m.relativeMove(1,-1*val);
        m.relativeMove(2,val);
    }
    else if(objName == "R-")
    {
        //m.relativeMove(7,-1500);

    }
    else if(objName == "ORG")
    {
        QVector<int> axisVec;
        axisVec.append(1);//上载台x
        axisVec.append(2);//上载台x
        axisVec.append(3);//上载台y
        if(m.goHomes(axisVec))
        {

        }
    }
}
