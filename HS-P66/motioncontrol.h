﻿#ifndef MOTIONCONTROL_H
#define MOTIONCONTROL_H


#include "ADLINK/APS168.h"
#include "ADLINK/type_def.h"
#include "ADLINK/APS_Define.h"
#include "ADLINK/ErrorCodeDef.h"
#include <QEventLoop>
#include <QTimer>
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>
#include "sharedata.h"
#include <QObject>
#include <QThread>
#include <QDebug>

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
    I32 getCarName();
    bool isInitialed();
    bool outPutDo(int carNum, long bit, int value);
    int initBoard();
    int getIoStatus(const int &carId,const int di_bit);
    bool airActionOn(int carNum, int output, int mov);
    bool airActionOff(int carNum, int output, int org);
    bool absolutMove(int axisId, int trapos, int v = 10000);
    void delay_msc(int msc);
    bool loadBoardParameter(QString fileName);
    bool waitNormalStop(int axis_id,int timeout = 30000);
    bool goHome(const int axisId, int maxV, int mode = 0, int acc = 100000, int dir = 1, int curve = 0);
};

#endif // MOTIONCONTROL_H