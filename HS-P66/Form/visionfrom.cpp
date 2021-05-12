#include "visionfrom.h"

VisionFrom::VisionFrom(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width(),parent->height());
    m_width = parent->width();
    m_height = parent->height();
    initUI();
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&VisionFrom::readFram);
}

void VisionFrom::initUI()
{
    m_vision_label = new QLabel(this);
    m_vision_label->resize(m_width/4*1.5,m_width/16*3);
    m_vision_label->move(m_width/4*3-200,80);
    m_vision_label->setStyleSheet("background-color:rgb(233,233,233)");

    m_openBtn = new QPushButton(this);
    m_openBtn->setText("open");
    m_openBtn->resize(50,33);
    m_openBtn->move(m_width/4*3,m_vision_label->height()+100);
    connect(m_openBtn,&QPushButton::clicked,this,&VisionFrom::openCamera);

    m_closeBtn = new QPushButton(this);
    m_closeBtn->setText("close");
     m_closeBtn->resize(50,33);
    m_closeBtn->move(m_width/4*3+100,m_vision_label->height()+100);
    connect(m_closeBtn,&QPushButton::clicked,this,&VisionFrom::closeCamera);
}

void VisionFrom::readFram()
{
    //获取图像帧
    m_videoCapture>>frame;
    /*
        //将抓取到的帧,转换为QImage格式,QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像
        //此时没有使用rgbSwapped()交换所有像素的红色和蓝色分量的值，底色偏蓝
        QImage image = QImage((const uchar*)frame.data,frame.cols, frame.rows,QImage::Format_RGB888);
        //将图片显示到label上
        ui->label->setPixmap(QPixmap::fromImage(image));
        */
//    Mat gray,therold;
//    cvtColor(frame,gray,cv::COLOR_BGR2GRAY);
    //cv::threshold(gray,frame,0,255,ThresholdTypes::THRESH_BINARY);
    //将视频显示到label上

    line(frame,Point(frame.cols/2,0),Point(frame.cols/2,frame.rows),Scalar(0,255,0));
    line(frame,Point(0,frame.rows/2),Point(frame.cols,frame.rows/2),Scalar(0,255,0));
    QImage image = QImage((const uchar*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
    m_vision_label->setPixmap(QPixmap::fromImage(image));
}

void VisionFrom::openCamera()
{
    m_videoCapture.open(0);//打开摄像头
    m_timer->start(25);//开启定时器，一次25ms
}

void VisionFrom::closeCamera()
{
    m_timer->stop();//关闭定时器
    m_videoCapture.release();//释放图像
}
