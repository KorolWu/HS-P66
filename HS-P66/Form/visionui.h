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
    void closeDevice();
    VisionFrom* m_pVision_L;
    VisionFrom* m_pVision_R;
private:
    bool initCameraDevice();
    CameraDevice* m_pDeviceProcess[2];
    GxIAPICPP::gxdeviceinfo_vector m_vectorDeviceInfo;
    QMap <QString,CameraDevice* > m_mapDeviceInformation;      ///< 用于存储设备处理类
    int m_width;
    int m_height;
    QPushButton *m_pMoveBtn[6];
    QDoubleSpinBox *m_pinterval;
private slots:
    void onMoveButtonClicked();


signals:

};

#endif // VISIONUI_H
