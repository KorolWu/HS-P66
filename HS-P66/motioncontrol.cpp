#include "motioncontrol.h"
#pragma execution_character_set("utf-8")
MotionControl::MotionControl()
{

}

bool MotionControl::isInitialed()
{
    return m_isInitialed;
}

///
/// \brief MotionControl::outPutDo
/// \param carNum   卡号
/// \param bit       位
/// \param value     值
/// \return
///
bool MotionControl::outPutDo(int carNum, long bit, int value)
{
    I32 currentData;
    APS_read_d_output(carNum,0,&currentData);
    if(value == 1)
       bit = (1 << bit) | currentData;
    else
        bit = (~(1 << bit)) & currentData;

    APS_write_d_output(carNum,0,bit);
    return true;
}

I32 MotionControl::getCarName()
{
    return m_carName;
}

int MotionControl::initBoard()
{
    int result = 1;
    I32 boardID_InBits = 0;
    I32 mode           = INIT_MANUAL_ID;
    I32 ret            = 0;
    I32 board_ID       = -1;
    I32 card_name;
    if(isInitialed() == true)
    {
        return result;
    }
    ret = APS_initial(&boardID_InBits,mode);
    if(ret == ERR_NoError)
    {
        for(int i = 0;i < 16; i++)
        {
            if((boardID_InBits >> i) & 1)
            {
                APS_get_card_name(i, &card_name);
                if(card_name == DEVICE_NAME_PCI_825458 || card_name == DEVICE_NAME_AMP_20408C)
                {
                    m_carName = card_name;
                    board_ID = i;
                    break;
                }
            }
        }
        if(board_ID == -1)
        {
            return ret;
        }
        return result;
    }
    else
    {
        qDebug()<<"init err Code:"<<ret;
        return ret;
    }
}

int MotionControl::getIoStatus(const int &carId, const int di_bit)
{
    I32 data = 0;
    int rec = APS_read_d_input(carId,0, &data);
    if(rec < 0)
        return rec;
     int a = (abs(data >> di_bit)) & 1;
     //qDebug()<<"data"<<data<<"di_big"<<di_bit<<"a="<<a;
     return a;
}

///
/// \brief MotionControl::airAction
/// \param carNum  轴号
/// \param output  输出点
/// \param mov     动点
///  output =  1 check mov = 1
/// \return
///
bool MotionControl::airActionOn(const int carNum, const int output, const int mov)
{
    struct timeval s,e;
    double timeUseWait = 0;
    gettimeofday(&s,nullptr);
    outPutDo(carNum,output,1);
    while (true) {
        if(getIoStatus(0,mov) == 1)
            return true;
        gettimeofday(&e,nullptr);
        delay_msc(50);
        timeUseWait = 1000 *(e.tv_sec - s.tv_sec) + 0.001*(e.tv_usec - s.tv_usec);
        if(timeUseWait >= 2000)
        {
            return false;
        }
    }
}
///
/// \brief MotionControl::airActionOff
/// \param carNum  轴号
/// \param output  输出点
/// \param org     原点
/// \return
///
bool MotionControl::airActionOff(int carNum, int output, int org)
{
    struct timeval s,e;
    double timeUseWait = 0;
    gettimeofday(&s,nullptr);
    outPutDo(carNum,output,0);
    while (true) {
        if(getIoStatus(0,org) == 1)
            return true;
        gettimeofday(&e,nullptr);
        delay_msc(10);
        timeUseWait = 1000 *(e.tv_sec - s.tv_sec) + 0.001*(e.tv_usec - s.tv_usec);
        if(timeUseWait >= 2000)
        {
            return false;
        }
    }
}

///
/// \brief MotionControl::absolutMove
/// \param axisId    轴ID
/// \param position  距离
/// \param v         速度
/// \return true =   执行成功
///
bool MotionControl::absolutMove(int axisId, int trapos, int v)
{
    //执行一个绝对运动。
    if( ((APS_motion_io_status(axisId) >> MIO_SVON ) & 1 ) == 0 )
    {
        APS_set_servo_on( axisId, 1 );
        QThread::msleep( 500 ); // Wait stable.
    }
    APS_absolute_move(axisId, trapos, v);
    return waitNormalStop(axisId);

}

bool MotionControl::relativeMove(int axisId, int interval, int v)
{
    //执行一个绝对运动。
    if( ((APS_motion_io_status(axisId) >> MIO_SVON ) & 1 ) == 0 )
    {
        APS_set_servo_on( axisId, 1 );
        QThread::msleep( 50 ); // Wait stable.
    }
    APS_relative_move(axisId,interval,v);
    return true;
}

void MotionControl::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}

void MotionControl::testTimeOut(int msc)
{
    struct timeval s,e;
    double timeUseWait = 0;
    gettimeofday(&s,nullptr);
    while (true) {
        gettimeofday(&e,nullptr);
        delay_msc(10);
        timeUseWait = 1000 *(e.tv_sec - s.tv_sec) + 0.001*(e.tv_usec - s.tv_usec);
        if(timeUseWait >= msc)
        {
            qDebug()<<"time is up";
            return;
        }
    }
}

bool MotionControl::loadBoardParameter(QString fileName)
{
    QByteArray buff = fileName.toLatin1();
    int ret = APS_load_param_from_file(buff.data());
    if(ret  != ERR_NoError)
    {
        qDebug()<<"load Board Parameter ErrCode:"<<ret;
        return false;
    }
    return true;

}

bool MotionControl::waitNormalStop(int axis_id, int timeout)
{
    int msts = 0;
    struct timeval ws,we;
    double timeUseWait = 0;
    gettimeofday(&ws,nullptr);
    while(true)
    {
        msts = ( APS_motion_status(axis_id) >> MTS_NSTP) & 1;// Get motion status
        if(msts == 1)
            break;
        gettimeofday(&we,nullptr);
        delay_msc(10);
        timeUseWait = 1000 *(we.tv_sec - ws.tv_sec) + 0.001*(we.tv_usec - ws.tv_usec);
        if(timeUseWait >= timeout)
        {
            return false;
        }
    }
    return true;
}
///
/// \brief MotionControl::goHome
/// \param maxV 最大速度
/// \param mode 回原点模式
/// \param acc  加速度
/// \param dcc  减速度
/// \param dir  方向
/// \param curve 加速曲线
/// \return
///
bool MotionControl::goHome(const int axisId,int maxV, int mode, int acc, int dir, int curve)
{
    I32 return_code;
    I32 msts;
    // 1. Select home mode and config home parameters
    APS_set_axis_param( axisId, PRA_HOME_MODE, mode ); //Set home mode
//    if(axisId == 14)//喷头的x
//        APS_set_axis_param( axisId, PRA_HOME_DIR, 0); //Set home direction
//    else
    APS_set_axis_param( axisId, PRA_HOME_DIR, dir ); //Set home direction
    APS_set_axis_param( axisId, PRA_HOME_CURVE, curve ); // Set acceleration pattern (T-curve)
    APS_set_axis_param( axisId, PRA_HOME_ACC, acc ); // Set homing acceleration rate
    APS_set_axis_param( axisId, PRA_HOME_VM, maxV ); // Set homing maximum velocity.
    APS_set_axis_param( axisId, PRA_HOME_VO, 50000 ); // Set homing
    APS_set_axis_param( axisId, PRA_HOME_EZA, 0 ); // Set homing
    APS_set_axis_param( axisId, PRA_HOME_SHIFT, 0 ); // Set homing
    APS_set_axis_param( axisId, PRA_HOME_POS, 0 ); // Set homing
    // 2. Start home move
    return_code = APS_home_move(axisId); //Start homing
    if( return_code != ERR_NoError )
    {
        /* Error handling */
        qDebug()<<"home move failed";
        return false;
    }
    // 3. Wait for home move done,
    int checkTimes = 0;
    do{
        if(checkTimes > 150)
        {
             qDebug()<<"axisID:"<<axisId<<"home move timeout > 20s";
            return false;
        }
        delay_msc(200);
        msts = APS_motion_status( axisId );// Get motion status
        msts = ( msts >> MTS_HMV ) & 1; // Get motion done bit
        checkTimes ++;
    }while( msts != 0 );
    // 4. Check home move success or not
    msts = APS_motion_status( axisId ); // Get motion status
    msts = ( msts >> MTS_ASTP ) & 1; // Get abnormal stop bit
    if( msts != 0 )
    {
        // Error handling ...
        I32 stop_code;
        APS_get_stop_code( axisId, &stop_code );
        qDebug()<<"home move abnormal stop";
        return false;
    }else
    {
        // Homing success.
        qDebug()<<"home move success";
        return  true;
    }
}

///
/// \brief MotionControl::goHomes 多轴同时回原点 没有考虑励磁  当有错误发生时其他轴要不要停止
/// \param axisVec 轴ID集合
/// \return
///
bool MotionControl::goHomes(const QVector<int> &axisVec)
{
    int return_code = -1;
    int msts;
    for(int i = 0;i < axisVec.size();i++)
    {
        int axisId = axisVec.at(i);
        APS_set_axis_param( axisId, PRA_HOME_MODE, 0 ); //Set home mode
        APS_set_axis_param( axisId, PRA_HOME_DIR, 1 ); //Set home direction
        APS_set_axis_param( axisId, PRA_HOME_CURVE, 0 ); // Set acceleration pattern (T-curve)
        APS_set_axis_param( axisId, PRA_HOME_VO, 50000 ); // Set homing
        APS_set_axis_param( axisId, PRA_HOME_EZA, 0 ); // Set homing
        APS_set_axis_param( axisId, PRA_HOME_SHIFT, 0 ); // Set homing
        APS_set_axis_param( axisId, PRA_HOME_POS, 0 ); // Set homing
        if(ShareData::GetInstance()->m_axisMap.contains(axisId))
        {
            APS_set_axis_param( axisId, PRA_HOME_ACC, ShareData::GetInstance()->m_axisMap[axisId].acc); // Set homing acceleration rate
            APS_set_axis_param( axisId, PRA_HOME_VM, ShareData::GetInstance()->m_axisMap[axisId].homeVmax ); // Set homing maximum velocity.
        }
        // 1. servo ON
        if(servoOn(axisId) == false)
        {
            QLOG_ERROR()<<"轴 "<<axisId<<"励磁失败";
            axisStop_v(axisVec);
            return false;
        }
        // 2. Start home move
        return_code = APS_home_move(axisId); //Start homing
        if( return_code != ERR_NoError )
        {
            /* Error handling */
            axisStop_v(axisVec);
            QLOG_ERROR()<<"轴 "<<axisId<<"执行回原点指令是失败";
            return false;
        }
    }
    // 检测vec里面的轴 是否都回原点成功
    QMap<int,bool> axisOrgState;
    struct timeval ws,we;
    double timeUseWait = 0;
    gettimeofday(&ws,nullptr);
    do{
        for(int i = 0;i < axisVec.size();i++)
        {
            int axisId = axisVec.at(i);
            msts = APS_motion_status( axisId );// Get motion status
            delay_msc(150);
            msts = ( msts >> MTS_HMV ) & 1; // Get motion done bit
            if(msts == 0 ) //回原点动作结束
            {
                if(axisOrgState.contains(axisId))
                {
                    axisOrgState[axisId] = true;
                    //QLOG_INFO()<<"axis"<<axisId<<"= true;"<<axisOrgState.size()<<" vec Size ="<<axisVec.size();
                }
                else
                {
                    axisOrgState.insert(axisId,true);
                    //QLOG_INFO()<<"axis"<<axisId<<"insert Map"<<axisOrgState.size()<<" vec Size ="<<axisVec.size();
                }
            }
        }
        gettimeofday(&we,nullptr);
        delay_msc(10);
        timeUseWait = 1000 *(we.tv_sec - ws.tv_sec) + 0.001*(we.tv_usec - ws.tv_usec);
        if(timeUseWait >= 60000)
        {
            QLOG_ERROR()<<"回原点超时";
            axisStop_v(axisVec);
            return false;
        }
       //QLOG_INFO()<<"insert Map="<<axisOrgState.size()<<" vec Size ="<<axisVec.size();
    }while( axisVec.size() != axisOrgState.size());
    // 检测vec里面的轴 是否都是正常停止的
    for(int i = 0;i < axisVec.size();i++)
    {
        int axisId = axisVec.at(i);
        delay_msc(100);
        msts = APS_motion_status( axisId );// Get motion status
        msts = ( msts >> MTS_ASTP ) & 1; // Get motion done bit
        if(msts != 0 )
        {
            I32 stop_code;
            APS_get_stop_code( axisId, &stop_code );
            QLOG_ERROR()<<"轴"<<axisId<<"回原点失败 错误代码："<<stop_code;
            return false;
        }
    }
    return true;

}

///
/// \brief MotionControl::axisStop_v 多轴停止
/// \param axisVec 轴集合
/// \return
///
bool MotionControl::axisStop_v(const QVector<int> &axisVec)
{
    for(int i = 0;i < axisVec.size();i ++)
    {
        int axisId = axisVec.at(i);
        APS_emg_stop(axisId);
        delay_msc(30);
    }
    return true;
}

///
/// \brief MotionControl::runPosition pp模式 多轴同时运动
/// \param posMap <axisID,position>
/// \return true = success
///
bool MotionControl::runPosition(const QMap<int, int> &posMap)
{
    QVector<int> axisVec;
    for(auto it = posMap.begin();it != posMap.end();it++)
    {
        axisVec<<it.key();
    }
    for(auto it = posMap.begin();it != posMap.end();it++)
    {
         int axisId  = it.key();
         int trapos = it.value();
         int v = 5000;
         if( ((APS_motion_io_status(axisId) >> MIO_SVON ) & 1 ) == 0 )
         {
             APS_set_servo_on( axisId, 1 );
             QThread::msleep( 50 ); // Wait stable.
         }
         if(ShareData::GetInstance()->m_axisMap.contains(axisId))
         {
             APS_set_axis_param(axisId, PRA_ACC, ShareData::GetInstance()->m_axisMap[axisId].acc ); //设置加速度
             APS_set_axis_param(axisId, PRA_DEC, ShareData::GetInstance()->m_axisMap[axisId].dcc ); //设置减速度
             v = ShareData::GetInstance()->m_axisMap[axisId].vMax;
         }
        I32 ret = APS_absolute_move(axisId, trapos, v);
        if(ret != ERR_NoError)
        {
            //执行相对运动时出现故障
            axisStop_v(axisVec);
            QLOG_ERROR()<<"在多轴执行绝对运动时发生故障";
            return false;
        }
    }
    QMap<int,bool> stopState;
    stopState.clear();
    struct timeval ws,we;
    double timeUseWait = 0;
    gettimeofday(&ws,nullptr);
    while(true)
    {
        int msts = 0;
        for(auto it = posMap.begin();it != posMap.end();it++)
        {
            if(false == stopState.contains(it.key()))
            {
                msts = ( APS_motion_status(it.key()) >> MTS_NSTP) & 1;// Get motion status
                if(msts == 1)
                {
                    if(stopState.contains(it.key()))
                    {
                        stopState[it.key()] = true;
                    }
                    else
                        stopState.insert(it.key(),true);
                }
            }
            if(stopState.size() == posMap.size())
                return true;
            delay_msc(50);
        }
        gettimeofday(&we,nullptr);
        delay_msc(50);
        timeUseWait = 1000 *(we.tv_sec - ws.tv_sec) + 0.001*(we.tv_usec - ws.tv_usec);
        if(timeUseWait >= 60000)
        {
            axisStop_v(axisVec);
            QLOG_ERROR()<<"在多轴执行绝对运动时超时";
            return false;
        }
    }

}

bool MotionControl::servoOn(int axisId)
{
    I32 ret = APS_motion_io_status(axisId);
    if( 1 != ((ret >> MIO_SVON ) & 1) )
    {
        ret = APS_set_servo_on( axisId, 1 );
        if(ret != ERR_NoError)
        {
            return false;
        }
        else
        {
           return true;
        }
       delay_msc(150); // Wait stable.
    }
    else
        return true;
}

bool MotionControl::getCurrentPos(const int &axisId, I32 &currentPosition)
{
    if(APS_get_position(axisId,&currentPosition) == ERR_NoError)
        return true;
    else
        return false;
}

bool MotionControl::runJog(const int &axisId,const int &dir)
{
    APS_jog_mode_switch(axisId, 1 ); //打开点动模式。
    APS_set_axis_param(axisId,PRA_JG_MODE,0);
    APS_set_axis_param(axisId,PRA_JG_DIR,dir);
    if(ShareData::GetInstance()->m_axisMap.contains(axisId))
    {
        APS_set_axis_param(axisId,PRA_JG_ACC,ShareData::GetInstance()->m_axisMap[axisId].acc);
        APS_set_axis_param(axisId,PRA_JG_DEC,ShareData::GetInstance()->m_axisMap[axisId].dcc);
        APS_set_axis_param(axisId,PRA_JG_VM,ShareData::GetInstance()->m_axisMap[axisId].vMax*0.3);
    }
    else
    {
        APS_set_axis_param(axisId,PRA_JG_ACC,10000);
        APS_set_axis_param(axisId,PRA_JG_VM,1000);
    }
    //是否需要检查励磁
    servoOn(axisId);
    APS_jog_start(axisId,0);// jog_start
    APS_jog_start(axisId,1);// jog_start
    return true;
}

bool MotionControl::stopJog(const int &axisId)
{
    APS_jog_start(axisId,1);// jog_start
    APS_jog_start(axisId,0);// jog_start
    APS_jog_mode_switch(axisId, 0 ); //关闭点动模式。
    return true;
}

///
/// \brief MotionControl::setLinearTriggerPos 设置x(14)轴的线性比较触发
/// \param board_ID  板卡号
/// \param LCmpCh    线性比较触发通道 0-3
/// \param StartPoint 触发位置
/// \return
///
bool MotionControl::setLinearTriggerPos(const int &board_ID, const int &LCmpCh, const int &StartPoint)
{
    bool r = false;
    APS_set_trigger_param(board_ID,1,14);
   I32 ret = APS_set_trigger_linear(board_ID,LCmpCh,StartPoint,1,1);
   //APS_set_trigger_param(board_ID,4,1); //enable
   ret == ERR_NoError ? r = true : r = false;
   return r;
}

int MotionControl::gettimeofday(struct timeval *tp, void *tzp)
{
    Q_UNUSED(tzp)
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year   = wtm.wYear - 1900;
    tm.tm_mon   = wtm.wMonth - 1;
    tm.tm_mday   = wtm.wDay;
    tm.tm_hour   = wtm.wHour;
    tm.tm_min   = wtm.wMinute;
    tm.tm_sec   = wtm.wSecond;
    tm. tm_isdst  = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}
