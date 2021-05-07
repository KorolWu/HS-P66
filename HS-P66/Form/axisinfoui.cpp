#include "axisinfoui.h"
#pragma execution_character_set("utf-8")

AxisInfoUI::AxisInfoUI(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpInputData()));
    font.setPointSize(13);
    font.setFamily("黑体");
    QWidget *wg = new QWidget(this);
    wg->setStyleSheet(tr("background-color:rgb(35,35,35);color:rgb(166,167,166);border-radius:10px;"));
    for(int i = 0; i < 3;++i)
    {
        lable[i]   = new QLabel(wg);
        lable[i]->setFont(font);
        lable[i]->setFixedSize(96,32);
        hBox[i]       = new QHBoxLayout();
        hBox[i]->setAlignment(Qt::AlignLeft);
    }
    vBox = new QVBoxLayout(this);
    wg->setLayout(vBox);
    curPos = new QLineEdit("0",wg);
    curPos->setStyleSheet(tr("background-color:rgb(40,42,51);"));
    curPos->setAlignment(Qt::AlignCenter);
    curPos->setFixedSize(96,32);
    curPos->setFont(font);
    for(int i = 0; i < 8;++i)
    {
        btn[i] = new PushButton(wg);
        btn[i]->setFixedSize(96,32);
        btn[i]->setFont(font);
        //btn[i]->setStatusImageNum(2);
    }
    btn[0]->getIconPath(":/src/Image/ok.png");
    btn[0]->setStatusImageNum(1);
    btn[1]->getIconPath(":/src/Image/ORG");
    btn[2]->getIconPath(":/src/Image/son");
    btn[3]->getIconPath(":/src/Image/reset");
    btn[4]->getIconPath(":/src/Image/left");
    btn[5]->getIconPath(":/src/Image/right");
    btn[6]->getIconPath(":/src/Image/FixPos");
    btn[7]->getIconPath(":/src/Image/stop");
    cbb = new QComboBox(wg);
    cbb->setFixedSize(96,32);
    cbb->setFont(font);
    cbb->setStyleSheet(tr("background-color:rgb(40,42,51);"));
    dsb = new QDoubleSpinBox(wg);
    dsb->setStyleSheet(tr("background-color:rgb(40,42,51);"));
    dsb->setFixedSize(96,32);
    dsb->setFont(font);
    dsb->setDecimals(3);
    CreatAsixUI();
    wg->setFixedSize(410,200);
    connect(btn[1],&QPushButton::clicked,this,&AxisInfoUI::RunORG);
    connect(btn[2],&QPushButton::clicked,this,&AxisInfoUI::RunSon);
    connect(btn[3],&QPushButton::clicked,this,&AxisInfoUI::RunReSet);
    connect(btn[4],&QPushButton::pressed,this,&AxisInfoUI::RunLeft);
    connect(btn[4],&QPushButton::released,this,&AxisInfoUI::RunStop);
    connect(btn[5],&QPushButton::pressed,this,&AxisInfoUI::RunRight);
    connect(btn[5],&QPushButton::released,this,&AxisInfoUI::RunStop);
    connect(btn[6],&QPushButton::clicked,this,&AxisInfoUI::RunQuickFixPos);
    connect(btn[7],&QPushButton::clicked,this,&AxisInfoUI::RunStop);
    return;
}
void AxisInfoUI::CreatAsixUI()
{
    vBox->addWidget(lable[0]);
    for(int i = 0;i < 4;++i)
    {
        hBox[0]->addWidget(btn[i]);
    }
    btn[0]->setText("run ok");
    //btn[0]->setTextSpacing(15);
    lable[1]->setText("速度:");
    QStringList list;
    list << "1" << "5" << "10" << "15" << "20" << "25" << "30" << "40" << "50" << "60" << "70" << "80" << "90" << "100";
    cbb->addItems(list);
    curPos->setDisabled(true);
    btn[4]->setFixedSize(48,32);
    btn[5]->setFixedSize(48,32);
    hBox[1]->addWidget(lable[1]);
    hBox[1]->addWidget(cbb);
    hBox[1]->addWidget(btn[4]);
    hBox[1]->addWidget(curPos);
    hBox[1]->addWidget(btn[5]);

    btn[6]->setText("FixPos");
    //btn[6]->setTextSpacing(15);
    lable[2]->setText("目标位置:");
    hBox[2]->addWidget(lable[2]);
    hBox[2]->addWidget(dsb);
    hBox[2]->addWidget(btn[6]);
    hBox[2]->addWidget(btn[7]);

    vBox->addLayout(hBox[0]);
    vBox->addLayout(hBox[1]);
    vBox->addLayout(hBox[2]);
}
void AxisInfoUI::SetAxisName(const QString strName)
{
     lable[0]->setText("轴 " + strName);
     m_axisName = strName;

}
void AxisInfoUI::SetAxisRanage(const double dstart,const double dend)
{
    dsb->setRange(dstart,dend);
}

QString AxisInfoUI::GetAxisName()
{
    return lable[0]->text().replace("轴 ","");
}
double AxisInfoUI::GetTraPos()
{
    return curPos->text().toDouble()/1000;
}

uint  AxisInfoUI::GetTraSpeed()
{
    return cbb->currentText().toUInt();
}
void AxisInfoUI::SetTraPos(double d)
{
    curPos->setText(QString("%1").arg(d));
}

void AxisInfoUI::RunORG()
{

}

void AxisInfoUI::RunSon()
{
    static bool ison = true;
    if(m_bytePos == -1) return;
    QVector<QPair<int,int>> temp;
//    foreach (auto it, ConfigData::GetInstance()->xmlMap.swConfigXml.swXml_SER_Map.son_Stru.OutPutVec) {
//        QPair<int,int> pair = QPair<int,int>(it.bit,it.value);
//        temp.append(pair);
//    }
//    if(ison)
//    {
//        btn[2]->setText("S_OFF");

//        CoreGlobal::BaseAxisOperate::SetAxisExcite(temp,m_bytePos);
//    }
//    else
//    {
//        btn[2]->setText("S_ON");
//        for (auto ior = temp.begin();ior != temp.end();++ior)
//        {
//            if(ior->second == 1)
//            {
//                ior->second = 0;
//            }
//            else
//            {
//                ior->second = 1;
//            }
//        }
//        CoreGlobal::BaseAxisOperate::SetAxisExciteOff(temp,m_bytePos);
//    }
//    ison = !ison;
}

void AxisInfoUI::RunReSet()
{
//    if(m_bytePos == -1) return;
//    if(m_bitInfo.contains("ReSet"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisReset(m_bitInfo["ReSet"].bit,m_bytePos);
//    }
}

void AxisInfoUI::RunLeft()
{
//    uint Traspeed = cbb->currentText().toUInt()/200.0 *ConfigData::GetInstance()->iSpeed ;
//    if(!ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap.contains(m_axisName))
//        return;
//    uint accel = ConfigData::GetInstance()->iAccel;
//    uint dccel = ConfigData::GetInstance()->iDccel;
//    int imodel = ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap[m_axisName].modelType.toInt();
//    int Trapos = ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap[m_axisName].swLimitStart.toInt();
//    if(m_byteInfoMap.contains("Model"))
//    {
//        CoreGlobal::BaseAxisOperate::ChangeAxisModel(m_byteInfoMap["Model"].strType,m_byteInfoMap["Model"].byteNum,m_byteInfoMap["Model"].bytePos,imodel);
//    }
//    if(m_byteInfoMap.contains("Trapos"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisPos(m_byteInfoMap["Trapos"].strType,m_byteInfoMap["Trapos"].byteNum,m_byteInfoMap["Trapos"].bytePos,Trapos);
//    }
//    if(m_byteInfoMap.contains("Traspeed"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisSpeed(m_byteInfoMap["Traspeed"].strType,m_byteInfoMap["Traspeed"].byteNum,m_byteInfoMap["Traspeed"].bytePos,Traspeed);
//    }
//    if(m_byteInfoMap.contains("Accel"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisACC(m_byteInfoMap["Accel"].strType,m_byteInfoMap["Accel"].byteNum,m_byteInfoMap["Accel"].bytePos,accel);
//    }
//    if(m_byteInfoMap.contains("Decel"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisDCC(m_byteInfoMap["Decel"].strType,m_byteInfoMap["Decel"].byteNum,m_byteInfoMap["Decel"].bytePos,dccel);
//    }
//    if(m_bytePos == -1) return;
//    if(m_bitInfo.contains("Run"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisRun(m_bitInfo["Run"].bit,m_bytePos);
//    }
//    return;
}

void AxisInfoUI::RunRight()
{
    /*int Traspeed = cbb->currentText().toUInt()/200.0 *ConfigData::GetInstance()->iSpeed;
    if(!ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap.contains(m_axisName))
        return;
    uint accel = ConfigData::GetInstance()->iAccel;
    uint dccel = ConfigData::GetInstance()->iDccel;
    int imodel = ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap[m_axisName].modelType.toInt();
    int Trapos = ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap[m_axisName].swLimitEnd.toInt();
    if(m_byteInfoMap.contains("Model"))
    {
        CoreGlobal::BaseAxisOperate::ChangeAxisModel(m_byteInfoMap["Model"].strType,m_byteInfoMap["Model"].byteNum,m_byteInfoMap["Model"].bytePos,imodel);
    }
    if(m_byteInfoMap.contains("Trapos"))
    {
        CoreGlobal::BaseAxisOperate::SetAxisPos(m_byteInfoMap["Trapos"].strType,m_byteInfoMap["Trapos"].byteNum,m_byteInfoMap["Trapos"].bytePos,Trapos);
    }
    if(m_byteInfoMap.contains("Traspeed"))
    {
        CoreGlobal::BaseAxisOperate::SetAxisSpeed(m_byteInfoMap["Traspeed"].strType,m_byteInfoMap["Traspeed"].byteNum,m_byteInfoMap["Traspeed"].bytePos,Traspeed);
    }
    if(m_byteInfoMap.contains("Accel"))
    {
        CoreGlobal::BaseAxisOperate::SetAxisACC(m_byteInfoMap["Accel"].strType,m_byteInfoMap["Accel"].byteNum,m_byteInfoMap["Accel"].bytePos,accel);
    }
    if(m_byteInfoMap.contains("Decel"))
    {
        CoreGlobal::BaseAxisOperate::SetAxisDCC(m_byteInfoMap["Decel"].strType,m_byteInfoMap["Decel"].byteNum,m_byteInfoMap["Decel"].bytePos,dccel);
    }
    if(m_bytePos == -1) return;
    if(m_bitInfo.contains("Run"))
    {
        CoreGlobal::BaseAxisOperate::SetAxisRun(m_bitInfo["Run"].bit,m_bytePos);
    }
    return;*/
}

void AxisInfoUI::RunQuickFixPos()
{
//    int Trapos = dsb->value() * 1000;

//    uint Traspeed = cbb->currentText().toUInt()/200.0 *ConfigData::GetInstance()->iSpeed;
//    if(!ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap.contains(m_axisName))
//        return;
//    uint accel = ConfigData::GetInstance()->iAccel;
//    uint dccel = ConfigData::GetInstance()->iDccel;
//    int imodel = ConfigData::GetInstance()->xmlMap.hwConfigXml.hwConfigXmlOutputMap.hwSerOutputMap[m_axisName].modelType.toInt();
//    if(m_byteInfoMap.contains("Model"))
//    {
//        CoreGlobal::BaseAxisOperate::ChangeAxisModel(m_byteInfoMap["Model"].strType,m_byteInfoMap["Model"].byteNum,m_byteInfoMap["Model"].bytePos,imodel);
//    }
//    if(m_byteInfoMap.contains("Trapos"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisPos(m_byteInfoMap["Trapos"].strType,m_byteInfoMap["Trapos"].byteNum,m_byteInfoMap["Trapos"].bytePos,Trapos);
//    }
//    if(m_byteInfoMap.contains("Traspeed"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisSpeed(m_byteInfoMap["Traspeed"].strType,m_byteInfoMap["Traspeed"].byteNum,m_byteInfoMap["Traspeed"].bytePos,Traspeed);
//    }
//    if(m_byteInfoMap.contains("Accel"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisACC(m_byteInfoMap["Accel"].strType,m_byteInfoMap["Accel"].byteNum,m_byteInfoMap["Accel"].bytePos,accel);
//    }
//    if(m_byteInfoMap.contains("Decel"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisDCC(m_byteInfoMap["Decel"].strType,m_byteInfoMap["Decel"].byteNum,m_byteInfoMap["Decel"].bytePos,dccel);
//    }
//    if(m_bytePos == -1) return;
//    if(m_bitInfo.contains("Run"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisRun(m_bitInfo["Run"].bit,m_bytePos);
//    }
}

void AxisInfoUI::RunStop()
{
//    if(m_bytePos == -1) return;
//    if(m_bitInfo.contains("Stop"))
//    {
//        CoreGlobal::BaseAxisOperate::SetAxisRun(m_bitInfo["Stop"].bit,m_bytePos);
//    }
}
void AxisInfoUI::TimerStatus(bool isStop)
{
    if(isStop)
    {
        timer->stop();
    }
    else
        timer->start(300);
}
void AxisInfoUI::timerUpInputData()
{
//    if(m_stausBitInfo.contains("Fault"))
//    {
//        if(CoreGlobal::BaseAxisOperate::CheckAxisFault(m_stausBitInfo["Fault"].bit,2,m_stausBytePos))
//        {
//            if(m_byteInfoMap.contains("Errorcode"))
//            {
//                int ierror = CoreGlobal::BaseAxisOperate::GetAxisErrorCode(m_byteInfoMap["Errorcode"].strType,m_byteInfoMap["Errorcode"].byteNum,m_byteInfoMap["Errorcode"].bytePos);
                //btn[0]->setText(QString("%1").arg(ierror));
               // btn[0]->getIconPath(":/images/error");
//            }
//        }
//        else
//        {
//            if(m_byteInfoMap.contains("Curpos"))
//            {
//                int iCurpos = CoreGlobal::BaseAxisOperate::GetAxisErrorCode(m_byteInfoMap["Curpos"].strType,m_byteInfoMap["Curpos"].byteNum,m_byteInfoMap["Curpos"].bytePos);
//                curPos->setText(QString("%1").arg(iCurpos));
//            }
            //todo errorBtn is Ok
            btn[0]->getIconPath(":/images/ok");
            btn[0]->setText(QString(""));
//        }
//    }
}
