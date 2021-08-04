#include "mainwidget.h"
#pragma execution_character_set("utf-8")

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    m_width = parent->width()-200;
    m_height = parent->height();
    this->resize(m_width,parent->height()/5*3+80);
    initUI();
    initCheckInfoUI();
}

void MainWidget::initUI()
{
    parent = new QWidget(this);
    parent->setStyleSheet("background-color:rgb(255,255,254);border-radius: 7px;");
    parent->resize(m_width-40,m_height/5*3.3);
    parent->move(20,20);
    m_camerLab = new QLabel(parent);
    m_camerLab->setStyleSheet("background-color:rgb(0,0,0);border-radius: 5px;border-width: 2px;border-color:rgb(230,230,225);border-image:url(:/src/Image/cameraInit.png)");
    m_camerLab->resize(m_width/3*1.2,m_height/3*1.2);
    m_camerLab->move(m_width/3*1.6,9);
}

void MainWidget::initCheckInfoUI()
{
    int icoWidth = 30;
    QFont font("Times", 23);
    QWidget *checkWidget = new QWidget(parent);
    checkWidget->setStyleSheet("background-color:rgb(245,245,240);border-radius: 5px;font-family:Times; font:19px;color:white;");
    checkWidget->resize(m_width/3*1.5,m_height/6-4);
    checkWidget->move(5,9);
    QLabel *userLab = new QLabel("hi root: \r\n           欢迎使用 ",parent);
    userLab->setAttribute(Qt::WA_TranslucentBackground, true);
    userLab->setStyleSheet("color:rgb(45,45,40)");
    userLab->move(20,20);
    userLab->setFont(font);
    QLabel *cLab = new QLabel(checkWidget);
    cLab->resize(checkWidget->width()-3,50);
    cLab->setStyleSheet("background-color:rgb(59,59,59);");
    cLab->move(2,checkWidget->height()- 55);
    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *bordLab = new QLabel("Bord:");
    QLabel *bordLab_ico = new QLabel();
    bordLab_ico->setFixedSize(icoWidth,icoWidth);
    bordLab_ico->setStyleSheet("border-image:url(:/src/Image/ok (1).ico)");
    hbox->addWidget(bordLab);
    hbox->addWidget(bordLab_ico);
    hbox->addStretch();

    QLabel *Sqlit = new QLabel("Sqlit:");
    QLabel *Sqlit_ico = new QLabel();
    Sqlit_ico->setFixedSize(icoWidth,icoWidth);
    Sqlit_ico->setStyleSheet("border-image:url(:/src/Image/ok (1).ico)");
    hbox->addWidget(Sqlit);
    hbox->addWidget(Sqlit_ico);
    hbox->addStretch();

    QLabel *camer_LLab = new QLabel("camer_L:");
    QLabel *camer_LLab_ico = new QLabel();
    camer_LLab_ico->setFixedSize(icoWidth,icoWidth);
    camer_LLab_ico->setStyleSheet("border-image:url(:/src/Image/ok (1).ico)");
    hbox->addWidget(camer_LLab);
    hbox->addWidget(camer_LLab_ico);
    hbox->addStretch();

    QLabel *camer_LRight = new QLabel("camer_R:");
    QLabel *camer_LRight_ico = new QLabel();
    camer_LRight_ico->setFixedSize(icoWidth,icoWidth);
    camer_LRight_ico->setStyleSheet("border-image:url(:/src/Image/ok (1).ico)");
    hbox->addWidget(camer_LRight);
    hbox->addWidget(camer_LRight_ico);
    hbox->addStretch();

    QLabel *printer = new QLabel("printer:");
    QLabel *printer_ico = new QLabel();
    printer_ico->setFixedSize(icoWidth,icoWidth);
    printer_ico->setStyleSheet("border-image:url(:/src/Image/ok (1).ico)");
    hbox->addWidget(printer);
    hbox->addWidget(printer_ico);
    hbox->addStretch();

    cLab->setLayout(hbox);
    m_perrwidget = new CPieWidget(m_width/2,m_height/2+400,parent);
    SetErrwidgetInfo();
    m_perrwidget->setPieStyleSheet(PieStyle::DountDefault);
    m_perrwidget->setCharTitle("Err Info");
    m_perrwidget->update();
    m_perrwidget->move(10,m_height/3-150);



    QWidget *nozzleWidget = new QWidget(parent);
    nozzleWidget->setStyleSheet("background-color:rgb(245,245,240);border-radius: 5px;font-family:Times; font:22px;color:black;");
    nozzleWidget->resize(m_width/3*1.2,m_height/3*0.65);
    nozzleWidget->move(m_width/3*1.6,m_height/3*1.3);
    QLabel *layerLab = new QLabel("当前打印层:              -- / --",nozzleWidget);
    layerLab->setAttribute(Qt::WA_TranslucentBackground, true);
    QFont font1("Times", 24);
    layerLab->setFont(font1);
    layerLab->move(15,15);


    QLabel *infoLab = new QLabel("机台状态:              正在打印",nozzleWidget);
    infoLab->setAttribute(Qt::WA_TranslucentBackground, true);
    infoLab->setFont(font1);
    infoLab->move(15,50);


    QLabel *timeLab = new QLabel("预估时间:              88:00",nozzleWidget);
    timeLab->setAttribute(Qt::WA_TranslucentBackground, true);
    timeLab->setFont(font1);
    timeLab->move(15,85);
}

QImage MainWidget::matToQImage(cv::Mat mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Grayscale8);
            return img;
        }
    case CV_8UC3:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
            return img.rgbSwapped();
        }
    case CV_8UC4:
        {
            QImage img((const unsigned char *)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
            return img;
        }
    default:
        {
            QImage img;
            return img;
        }
    }
}

void MainWidget::showMark(cv::Mat &src)
{
    QImage img = matToQImage(src);
    QImage new_img = img.scaled( m_camerLab->width(),m_camerLab->height());
    QPixmap pixmap = QPixmap::fromImage(new_img);

    QPainter painter(&pixmap);
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial", 30));
    painter.drawLine(0,m_camerLab->height()/2,m_camerLab->width(),m_camerLab->height()/2);
    painter.drawLine(m_camerLab->width()/2,0,m_camerLab->width()/2,m_camerLab->height());
    painter.end();
    m_camerLab->setPixmap(pixmap);

}
void MainWidget::SetErrwidgetInfo()
{
    m_colorlist << QColor(116,169,26);
    m_colorlist << QColor(201,64,73);
    m_colorlist << QColor(210,151,153);
    m_colorlist << QColor(77,82,175);
    m_colorlist << QColor(158,102,155);
    m_colorlist << QColor(172,126,126);
    m_colorlist << QColor(90,179,86);
    QMap<QString,float> data;//1=喷头 2=相机 3=运动 4=气缸 5=逻辑 6=数据存储故障  7=其他故障
    data.insert("喷头:",6);
    data.insert("相机:",3);
    data.insert("运动:",2);
    data.insert("气缸:",5);
    data.insert("逻辑:",1);
    data.insert("数据存储:",1);
    data.insert("其他:",1);
    m_perrwidget->setColors(m_colorlist);
    m_perrwidget->setData(data);
    m_perrwidget->init();
}

