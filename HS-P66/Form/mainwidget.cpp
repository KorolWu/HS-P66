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
    m_camerLab->setStyleSheet("background-color:rgb(0,0,0);border-radius: 5px;border-image:url(:/src/Image/cameraInit.png)");
    m_camerLab->resize(m_width/3*1.2,m_height/3*1.2);
    m_camerLab->move(m_width/3*1.6,9);
}

void MainWidget::initCheckInfoUI()
{
    int icoWidth = 30;
    QFont font("Times", 23);
    QWidget *checkWidget = new QWidget(parent);
     checkWidget->setStyleSheet("background-color:rgb(192,192,192,218);border-radius: 5px;font-family:Times; font:19px;color:white;");
    checkWidget->resize(m_width/3*1.5,m_height/6-4);
    checkWidget->move(5,9);
    QLabel *userLab = new QLabel("hi root: \r\n           欢迎使用 ",parent);
    userLab->setStyleSheet("background-color:rgb(169,203,202);color:white");
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

