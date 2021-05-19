#include "motioncontrol.h"

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
    return (abs(data << di_bit)) & 1;
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
        if(getIoStatus(carNum,mov) == 1)
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
        if(getIoStatus(carNum,org) == 1)
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
    // 3. Wait for home move do ne,
    do{
        delay_msc(100);
        msts = APS_motion_status( axisId );// Get motion status
        msts = ( msts >> MTS_HMV ) & 1; // Get motion done bit
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
