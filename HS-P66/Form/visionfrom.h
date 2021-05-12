#ifndef VISIONFROM_H
#define VISIONFROM_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include "opencv2/opencv.hpp"
#include <QPushButton>
#include <QImage>
using namespace cv;
class VisionFrom : public QWidget
{
public:
    VisionFrom(QWidget *parent = nullptr);
private:
    int m_width;
    int m_height;
    QTimer *m_timer;
    Mat frame;
    VideoCapture m_videoCapture;
    QLabel *m_vision_label;
    QPushButton *m_openBtn;
    QPushButton *m_closeBtn;
    void initUI();
    void readFram();
    void openCamera();
    void closeCamera();
};

#endif // VISIONFROM_H
