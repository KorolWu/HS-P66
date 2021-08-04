#ifndef VISIONFROM_H
#define VISIONFROM_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QPushButton>
#include <QSpinBox>
#include <QImage>
#include <QPainter>
#include <QGroupBox>
#include "sharedata.h"
#include "motioncontrol.h"
#include "Units/cameradevice.h"
#include "Units/imageprocess.h"
#include "databasemanager.h"
#include <QtMath>

using namespace cv;
using namespace std;
class VisionFrom : public QWidget
{
    Q_OBJECT
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
    QPushButton *m_pCliabreationBtn;
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
    VisionStu computMatrix();
private slots:
    void resiveImageData(unsigned char *data);
    void setExpossure();
    void setGain();
    void save();
    void onTrigger();
    void onCheckerBoardClicked();
    bool autoGetTransformationParameter(const int interval, VisionStu &result);
    void delay_msc(int msc);
    void onCliabreationClicked();
public:
    bool trigger(QPoint &point, double &angle, QString &msg, QMap<double, double> &cornerPosition);
signals:
    void onFindMark(Mat &mark);
};

#endif // VISIONFROM_H
