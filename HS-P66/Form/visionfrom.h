#ifndef VISIONFROM_H
#define VISIONFROM_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QPushButton>
#include <QSpinBox>
#include <QImage>
#include <QGroupBox>
#include "sharedata.h"
#include "motioncontrol.h"
#include "Units/cameradevice.h"
#include "Units/imageprocess.h"
#include "databasemanager.h"

using namespace cv;
using namespace std;
class VisionFrom : public QWidget
{
public:
    VisionFrom(QWidget *parent = nullptr);
    void setDeviceObj(CameraDevice* obj);
    void setGrouboxTitle(QString teitle);
private:
    int m_width;
    int m_height;
    bool m_trigger = false;
   // QTimer *m_timer;
    CameraDevice *m_pDevice;
    Mat frame;
    VideoCapture m_videoCapture;
    QGroupBox *m_pGroupBox;
    QLabel *m_vision_label;
    QPushButton *m_openBtn;
    QPushButton *m_closeBtn;
    QPushButton *m_pTriggerBtn;
    QPushButton *m_pSaveBtn;
    QPushButton *m_pCheckerBoardBtn;
    QSpinBox *m_pExpossureEdit;
    QPushButton *m_pExpossureBtn;
    QSpinBox *m_pGainEdit;
    QPushButton *m_pGainBtn;
    //test
    std::vector<Point2f> point_camera;
    std::vector<Point2f> point_rebot;
    //end test
    int m_matWidth;
    int m_matHeight;
    void initUI();
    void readFram();
    void openCamera();
    void closeCamera();
    QMap<double,double> transformation(double x, double y);
    bool CheckerboardResuleSave(const QString &cameraName, const double &pix2mm);
    bool saveVisionParmeter(const double &a, const double &b, const double &c, const double &d, const double &e, const double &f, const double &pix2mm = 0.0);
private slots:
    void resiveImageData(unsigned char *data);
    void setExpossure();
    void setGain();
    void save();
    void onTrigger();
    void onCheckerBoardClicked();
public:
    bool trigger(QPoint &point, QString &msg);
};

#endif // VISIONFROM_H
