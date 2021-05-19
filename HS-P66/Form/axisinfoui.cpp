#include "axisinfoui.h"
#pragma execution_character_set("utf-8")

AxisInfoUI::AxisInfoUI(int axisID, QWidget *parent) : QWidget(parent)
{
    m_axisId = axisID;
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
    wg->setFixedSize(395,200);
    connect(btn[1],&QPushButton::clicked,this,&AxisInfoUI::RunORG);
    connect(btn[2],&QPushButton::clicked,this,&AxisInfoUI::RunSon);
    connect(btn[3],&QPushButton::clicked,this,&AxisInfoUI::RunReSet);
    connect(btn[4],&QPushButton::pressed,this,&AxisInfoUI::RunLeft);
    connect(btn[4],&QPushButton::released,this,&AxisInfoUI::RunStop);
    connect(btn[5],&QPushButton::pressed,this,&AxisInfoUI::RunRight);
    connect(btn[5],&QPushButton::released,this,&AxisInfoUI::RunStop);
    connect(btn[6],&QPushButton::clicked,this,&AxisInfoUI::RunQuickFixPos);
    connect(btn[7],&QPushButton::clicked,this,&AxisInfoUI::EmgStop);
    TimerStatus(false);
}
void AxisInfoUI::CreatAsixUI()
{
    vBox->addWidget(lable[0]);
    for(int i = 0;i < 4;++i)
    {
        hBox[0]->addWidget(btn[i]);
    }
    //btn[0]->setText("run ok");
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

void AxisInfoUI::checkIsServoON()
{
    if( !( ( APS_motion_io_status( m_axisId ) >> MIO_SVON ) & 1 ) )
    {
        APS_set_servo_on( m_axisId, 1 );
        QThread::msleep( 500 ); // Wait stable.
    }
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
    MotionControl m;
    int vMax = 10000;
    int acc = 1000;
    if(ShareData::GetInstance()->m_axisMap.contains(m_axisId))
    {
        acc = ShareData::GetInstance()->m_axisMap[m_axisId].acc;
        vMax = ShareData::GetInstance()->m_axisMap[m_axisId].homeVmax;
    }

    m.goHome(m_axisId,vMax,0,acc,1,0);
    //    //This example shows how home move operates
    //    I32 return_code;
    //    I32 msts;
    //    // 1. Select home mode and config home parameters
    //    APS_set_axis_param( m_axisId, PRA_HOME_MODE, 0 ); //Set home mode
    //    APS_set_axis_param( m_axisId, PRA_HOME_DIR, 1 ); //Set home direction
    //    APS_set_axis_param( m_axisId, PRA_HOME_CURVE, 0 ); // Set acceleration pattern (T-curve)
    //    APS_set_axis_param( m_axisId, PRA_HOME_ACC, 1000 ); // Set homing acceleration rate
    //    APS_set_axis_param( m_axisId, PRA_HOME_VM, 5000 ); // Set homing maximum velocity.
    //    APS_set_axis_param( m_axisId, PRA_HOME_VO, 200 ); // Set homing
    //    APS_set_axis_param( m_axisId, PRA_HOME_EZA, 0 ); // Set homing
    //    APS_set_axis_param( m_axisId, PRA_HOME_SHIFT, 0 ); // Set homing
    //    APS_set_axis_param( m_axisId, PRA_HOME_POS, 0 ); // Set homing
    //    // 2. Start home move
    //    return_code = APS_home_move(m_axisId); //Start homing
    //    if( return_code != ERR_NoError )
    //    {
    //        /* Error handling */
    //        qDebug()<<"home move failed";
    //        return;
    //    }
    //    // 3. Wait for home move do ne,
    //    do{
    //        QThread::msleep(100);
    //        msts = APS_motion_status( m_axisId );// Get motion status
    //        msts = ( msts >> MTS_HMV ) & 1; // Get motion done bit
    //    }while( msts != 0 );
    //    // 4. Check home move success or not
    //    msts = APS_motion_status( m_axisId ); // Get motion status
    //    msts = ( msts >> MTS_ASTP ) & 1; // Get abnormal stop bit
    //    if( msts != 0 )
    //    {
    //        // Error handling ...
    //        I32 stop_code;
    //        APS_get_stop_code( m_axisId, &stop_code );
    //        qDebug()<<"home move abnormal stop";
    //    }else
    //    {
    //        // Homing success.
    //        qDebug()<<"home move success";
    //    }
}

void AxisInfoUI::RunSon()
{
    //Check servo on or not
    I32 ret = APS_motion_io_status(m_axisId);
    if( 1 != ((ret >> MIO_SVON ) & 1) )
    {
        ret = APS_set_servo_on( m_axisId, 1 );
        if(ret != ERR_NoError)
        {
            qDebug()<<"Servo on fail rec = "<<ret;
        }
        else
        {
            qDebug()<<"servo on rec = "<<ret;
            btn[2]->getIconPath(":/src/Image/son_off.png");
        }
        QThread::msleep( 500 ); // Wait stable.
    }
    else
    {
        ret = APS_set_servo_on( m_axisId, 0 );
        if(ret != ERR_NoError)
        {
            qDebug()<<"Servo_off fail rec = "<<ret;
        }
        else
        {
            qDebug()<<"else servo on rec = "<<ret;
            btn[2]->getIconPath(":/src/Image/son");
        }
        QThread::msleep( 500 ); // Wait stable.
    }

}

void AxisInfoUI::RunReSet()
{
    int rse = APS_reset_sscnet_servo_alarm(m_axisId);
    if(rse == ERR_NoError)
    {
        btn[0]->getIconPath(":/images/ok");
    }
}

void AxisInfoUI::RunLeft()
{
    APS_jog_mode_switch(m_axisId, 1 ); //打开点动模式。
    APS_set_axis_param(m_axisId,PRA_JG_MODE,0);
    APS_set_axis_param(m_axisId,PRA_JG_DIR,0);
    if(ShareData::GetInstance()->m_axisMap.contains(m_axisId))
    {
        qDebug()<<"<<vmax="<<ShareData::GetInstance()->m_axisMap[m_axisId].vMax<<"0.? = "<<GetTraSpeed()*0.01;
        qDebug()<<"<<vmax="<<ShareData::GetInstance()->m_axisMap[m_axisId].acc<<"0.? = "<<GetTraSpeed()*0.01;
        qDebug()<<"<<vmax="<<ShareData::GetInstance()->m_axisMap[m_axisId].dcc<<"0.? = "<<GetTraSpeed()*0.01;
        APS_set_axis_param(m_axisId,PRA_JG_ACC,ShareData::GetInstance()->m_axisMap[m_axisId].acc);
        APS_set_axis_param(m_axisId,PRA_JG_DEC,ShareData::GetInstance()->m_axisMap[m_axisId].dcc);
        APS_set_axis_param(m_axisId,PRA_JG_VM,ShareData::GetInstance()->m_axisMap[m_axisId].vMax*(GetTraSpeed()*0.01));
    }
    else
    {
        APS_set_axis_param(m_axisId,PRA_JG_ACC,10000);
        APS_set_axis_param(m_axisId,PRA_JG_VM,1000);
    }
    //APS_set_axis_param(m_axisId,PRA_JG_STOP,10000);
    checkIsServoON();
    APS_jog_start(m_axisId,0);// jog_start
    APS_jog_start(m_axisId,1);// jog_start
}

void AxisInfoUI::RunRight()
{
    APS_jog_mode_switch(m_axisId, 1 ); //打开点动模式。
    APS_set_axis_param(m_axisId,PRA_JG_MODE,0); //连续模式
    APS_set_axis_param(m_axisId,PRA_JG_DIR,1);
    if(ShareData::GetInstance()->m_axisMap.contains(m_axisId))
    {
        qDebug()<<"<<vmax="<<ShareData::GetInstance()->m_axisMap[m_axisId].vMax<<"0.? = "<<GetTraSpeed()*0.01;
        qDebug()<<"<<vmax="<<ShareData::GetInstance()->m_axisMap[m_axisId].acc<<"0.? = "<<GetTraSpeed()*0.01;
        qDebug()<<"<<vmax="<<ShareData::GetInstance()->m_axisMap[m_axisId].dcc<<"0.? = "<<GetTraSpeed()*0.01;
        APS_set_axis_param(m_axisId,PRA_JG_ACC,ShareData::GetInstance()->m_axisMap[m_axisId].acc);
        APS_set_axis_param(m_axisId,PRA_JG_DEC,ShareData::GetInstance()->m_axisMap[m_axisId].dcc);
        APS_set_axis_param(m_axisId,PRA_JG_VM,ShareData::GetInstance()->m_axisMap[m_axisId].vMax*(GetTraSpeed()*0.01));
    }
    else
    {
        APS_set_axis_param(m_axisId,PRA_JG_ACC,10000);
        APS_set_axis_param(m_axisId,PRA_JG_VM,1000);
    }
    //APS_set_axis_param(m_axisId,PRA_JG_STOP,10000);
    checkIsServoON();
    APS_jog_start(m_axisId,0);// jog_start
    APS_jog_start(m_axisId,1);// jog_start
    qDebug()<<"run right";
}

void AxisInfoUI::RunQuickFixPos()
{
    APS_set_axis_param(m_axisId, PRA_ACC, 10000 ); //设置加速度
    APS_set_axis_param(m_axisId, PRA_DEC, 10000 ); //设置减速度
    int Trapos = dsb->value();
    //执行一个绝对运动。
    if( 0 == ((APS_motion_io_status( m_axisId ) >> MIO_SVON ) & 1 ))
    {
        APS_set_servo_on( m_axisId, 1 );
        QThread::msleep( 500 ); // Wait stable.
    }
    APS_absolute_move( m_axisId, Trapos, 10000 );
    int msts = 0;
    do{
        QThread::msleep(20);
        msts = ( APS_motion_status(m_axisId) >> MTS_NSTP) & 1;// Get motion status
    }while( !msts );
}

void AxisInfoUI::RunStop()
{
    APS_jog_start(m_axisId,1);// jog_start
    APS_jog_start(m_axisId,0);// jog_start
    APS_jog_mode_switch(m_axisId, 0 ); //关闭点动模式。
}

void AxisInfoUI::EmgStop()
{
    APS_emg_stop(m_axisId);
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
    int msts = 0;
    msts = APS_motion_status( m_axisId );// Get motion status
    int isErr = ( msts >> MTS_ASTP ) & 1; // Get abnormal stop bit
    if(isErr == 1 )
    {
        btn[0]->getIconPath(":/src/Image/err.png");

    }
    else
    {
        btn[0]->getIconPath(":src/Image/ok.png");

    }
    long int position = 0;
    APS_get_position(m_axisId,&position);
    curPos->setText(QString("%1").arg(position));
}
