#include "iomonitor.h"

IoMonitor::IoMonitor(int carNum, QStringList alisaList, QStringList outAlisaList, QWidget *parent):QWidget(parent)
{
    if(alisaList.size() != 16)
    {
        for (int i = 8; i < 24 ; i++) {
            m_alsaList << QString("DI%1").arg(i);
        }
    }
    else
        m_alsaList = alisaList;
    if(outAlisaList.size() != 16)
    {
        for (int i = 8; i < 24 ; i++) {
            m_outAlisaList << QString("DO%1").arg(i);
        }
    }
    else
        m_outAlisaList = outAlisaList;
    m_carNum = carNum;
    m_vbox = new QVBoxLayout();
    m_hbox = new QHBoxLayout();
    this->resize(1600,130);
    this->setLayout(m_vbox);
    this->setStyleSheet("background-color:rgb(79,79,79);border-radius: 5px;");
    initUi();

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&IoMonitor::updateIo);
    m_timer->start(80);
}

void IoMonitor::initUi()
{
    QVBoxLayout *v = nullptr;
    QLabel* titel = new QLabel(QString("Car ID: %1").arg(m_carNum));
    titel->setStyleSheet("font:Times;font-size:20px; color: rgb(197, 197, 197);");
    titel->setAlignment(Qt::AlignLeft);
    m_vbox->addWidget(titel);
    for (int i = 0; i <16; i++) {
        v = new QVBoxLayout();
        m_io_light[i] = new QLabel();
        m_io_light[i]->setFixedSize(30,30);
        m_io_light[i]->setStyleSheet("border-image:url(:/src/Image/gray.png)");
        m_io_name[i] = new QLabel();
        m_io_name[i]->setText(m_alsaList[i]);
        m_io_name[i]->setStyleSheet("font:Times;font-size:15px; color: rgb(197, 197, 197);");
        v->addWidget(m_io_light[i]);
        v->addWidget(m_io_name[i]);

        //v = new QVBoxLayout();
        m_do_light[i] = new QLabel();
        m_do_light[i]->setFixedSize(30,30);
        m_do_light[i]->setStyleSheet("border-image:url(:/src/Image/gray.png)");
        m_btn[i] = new QPushButton();
        m_btn[i]->setFixedSize(60,30);
        m_btn[i]->setText(m_outAlisaList[i]);
        m_btn[i]->setObjectName(QString("%1").arg(i));
        connect(m_btn[i],&QPushButton::clicked,this,&IoMonitor::onDoClicked);
        m_btn[i]->setStyleSheet("QPushButton{background-color:rgb(210,210,190);color:grb(200,200,200);border-radius: 5px;}\
                                    QPushButton:hover{background-color:rgb(100,100,100);}\
                                    QPushButton:pressed{background-color:rgb(190,190,190);}");
        v->addWidget(m_do_light[i]);
        v->addWidget(m_btn[i]);
        v->setAlignment(Qt::AlignVCenter);
        m_hbox->addLayout(v);
    }
    m_vbox->addLayout(m_hbox);
}

void IoMonitor::updateIo()
{
    long result = 0;
    APS_read_d_input(m_carNum,0,&result);
    DIInfostru d;
    d.InputValue = result;
    if(ShareData::GetInstance()->m_DI_Status.contains(m_carNum))
    {
        ShareData::GetInstance()->m_DI_Status[m_carNum] = d;
    }
    else
        ShareData::GetInstance()->m_DI_Status.insert(m_carNum,d);
    d.bit8 == 0 ? m_io_light[0]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[0]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit9 == 0 ? m_io_light[1]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[1]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit10 == 0 ? m_io_light[2]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[2]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit11 == 0 ? m_io_light[3]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[3]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit12 == 0 ? m_io_light[4]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[4]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit13 == 0 ? m_io_light[5]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[5]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit14 == 0 ? m_io_light[6]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[6]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit15 == 0 ? m_io_light[7]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[7]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit16 == 0 ? m_io_light[8]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[8]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit17 == 0 ? m_io_light[9]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[9]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit18 == 0 ? m_io_light[10]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[10]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit19 == 0 ? m_io_light[11]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[11]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit20 == 0 ? m_io_light[12]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[12]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit21 == 0 ? m_io_light[13]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[13]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit22 == 0 ? m_io_light[14]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[14]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    d.bit23 == 0 ? m_io_light[15]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_io_light[15]->setStyleSheet("border-image:url(:/src/Image/green.png)");


    if(APS_read_d_output(m_carNum,0,&result) != 0)
        return;

    DoInfostru o;
    o.OutputValue = result;
    o.bit8 == 0 ? m_do_light[0]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[0]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit9 == 0 ? m_do_light[1]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[1]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit10 == 0 ? m_do_light[2]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[2]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit11 == 0 ? m_do_light[3]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[3]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit12== 0 ? m_do_light[4]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[4]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit13 == 0 ? m_do_light[5]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[5]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit14 == 0 ? m_do_light[6]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[6]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit15 == 0 ? m_do_light[7]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[7]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit16 == 0 ? m_do_light[8]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[8]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit17 == 0 ? m_do_light[9]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[9]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit18 == 0 ? m_do_light[10]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[10]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit19 == 0 ? m_do_light[11]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[11]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit20 == 0 ? m_do_light[12]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[12]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit21 == 0 ? m_do_light[13]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[13]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit22 == 0 ? m_do_light[14]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[14]->setStyleSheet("border-image:url(:/src/Image/green.png)");
    o.bit23 == 0 ? m_do_light[15]->setStyleSheet("border-image:url(:/src/Image/gray.png)") : m_do_light[15]->setStyleSheet("border-image:url(:/src/Image/green.png)");


}
///
/// \brief IoMonitor::onDoClicked
/// on -> off
/// 0ff -> on
///
void IoMonitor::onDoClicked()
{
   QString objName = sender()->objectName();
   int doNum = objName.toInt()+8;
   I32 currentData;
   APS_read_d_output(m_carNum,0,&currentData);
   MotionControl d;
   if(((currentData >> doNum) & 1) != 1) //on
   {
        d.outPutDo(m_carNum,doNum,1);
        QLOG_ERROR()<<doNum<<"on"<<" currentData<<"<<currentData;;
   }
   else //off
   {
        d.outPutDo(m_carNum,doNum,0);
        QLOG_ERROR()<<doNum<<"off";
   }
//   qDebug()<<value;
}
