#ifndef SHAREDATA_H
#define SHAREDATA_H
#include <QString>
#include <QObject>
#include <QMap>
#include "QsLog.h"
#include "QsLogDest.h"
#include "QsLogLevel.h"
#include "DataStruct.h"

class ShareData
{
private:
    ShareData();
    static ShareData* Instance;

public:
    static ShareData* GetInstance();
    int m_width;
    int m_heitht;
    //板卡是否初始化
    bool m_DriverIsInitialization = false;
    //是否满足开始条件，是否在初始位置
    bool m_isHomePosition = false;
    //carNum, dIstatus
    QMap <int,DIInfostru> m_DI_Status;
    //carNum, axisStruct
    QMap <int,AxisStruct> m_axisMap;

    //axis,curPosition
    QMap <int,long int> m_axisPositonMap;
    //用来保存所有的点位，<点位名称，点位信息>
    QMap<QString,QMap<int,int>> m_position;
};

#endif // SHAREDATA_H
