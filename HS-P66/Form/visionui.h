#ifndef VISIONUI_H
#define VISIONUI_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QGroupBox>
#include "visionfrom.h"
#include "Units/cameradevice.h"
#include "motioncontrol.h"
#include "QsLog.h"
#include "QsLogDest.h"
#include "QsLogLevel.h"
#include <QPushButton>

//using namespace std;
class VisionUi : public QWidget
{
    Q_OBJECT
public:
    VisionUi(QWidget *parent = nullptr);
    void init();
private:
    bool initCameraDevice();
    CameraDevice* m_pDeviceProcess[2];
    GxIAPICPP::gxdeviceinfo_vector m_vectorDeviceInfo;
    QMap <QString,CameraDevice* > m_mapDeviceInformation;      ///< 用于存储设备处理类
    int m_width;
    int m_height;
    VisionFrom* m_pVision_L;
    VisionFrom* m_pVision_R;
    QPushButton *m_pMoveBtn[6];
private slots:
    void onMoveButtonClicked();


signals:

};

#endif // VISIONUI_H
