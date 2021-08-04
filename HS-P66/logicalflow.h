#ifndef LOGICALFLOW_H
#define LOGICALFLOW_H
#include <QString>
#include "sharedata.h"
#include "motioncontrol.h"
#include "Units/XXYConverter.h"

///
/// \brief The LogicalFlow class
///
class LogicalFlow
{
public:
    LogicalFlow();
    bool beginIn(const int &dir);
    bool getGlass();
    bool printX();
    bool printFlow();
    bool airInit(); //气缸初始位
    bool airAction();//气缸卡边动作
    bool glassBack();//打印完成后 将玻璃送出到流道口
    bool runPosition(const QString &positionName); //去一个是示教过的位置
    void airVoid(const bool isVoid);//平台吸真空
    bool airOn(const int &car,const int &out, const int &checkId);
    bool runOffect(QMap<double,double> &cornerPosition);
    bool runAngleOffect(double &angle);
private:
    void delay_msc(int msc);
    bool ckeckEmgSignal();//检查急停信号是否按下，是返回true
};

#endif // LOGICALFLOW_H
