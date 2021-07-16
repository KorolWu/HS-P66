#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H


#include "APS168.h"
#include "type_def.h"
#include "APS_Define.h"
#include "ErrorCodeDef.h"
#include <QEventLoop>
#include <QTimer>
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>
#include "sharedata.h"
#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMap>
#include <QVector>

///
/// \brief The MotionControl class
/// 对轴api的简单封装
///
class MotionControl
{
private:
    int gettimeofday(struct timeval *tp, void *tzp);
    bool m_isInitialed = false;
    I32 m_carName = 88;
public:
    MotionControl();
    int  initBoard();
    I32  getCarName();
    bool isInitialed();
    void delay_msc(int msc);
    void testTimeOut(int msc);
    bool loadBoardParameter(QString fileName);
    bool outPutDo(int carNum, long bit, int value);
    int getIoStatus(const int &carId,const int di_bit);
    bool airActionOn(int carNum, int output, int mov);
    bool airActionOff(int carNum, int output, int org);
    bool absolutMove(int axisId, int trapos, int v = 10000);
    bool relativeMove(int axisId, int interval,int v= 10000);
    bool waitNormalStop(int axis_id,int timeout = 30000);
    bool goHome(const int axisId, int maxV, int mode = 0, int acc = 100000, int dir = 1, int curve = 0);
    bool goHomes(const QVector<int> &axisVec);
    bool axisStop_v(const QVector<int> &axisVec);
    bool runPosition(const QMap<int,int> &posMap);
    //bool emgStop();
    bool servoOn(int axisId);
    bool getCurrentPos(const int &axisId, I32 &currentPosition);
    bool runJog(const int &axisId, const int &dir);
    bool stopJog(const int &axisId);
};

#endif // MOTIONCONTROL_H
