#include "logicalflow.h"
#include "QsLog.h"
#pragma execution_character_set("utf-8")
LogicalFlow::LogicalFlow()
{

}
///
/// \brief LogicalFlow::beginIn
/// \param dir 流道旋转的方向 1 = 进料 0=出料
/// \return
///
bool LogicalFlow::beginIn(const int &dir)
{
    if(false == ckeckEmgSignal())
        return false;
    MotionControl m;
    m.runJog(18,dir);
    m.runJog(19,dir);
    delay_msc(5000);
    m.stopJog(18);
    m.stopJog(19);
    QLOG_INFO()<<"进料完成";
    return true;
}

///
/// \brief LogicalFlow::getGlass 玻璃从流道到载台上
/// \return
///
bool LogicalFlow::getGlass()
{
    if(false == ckeckEmgSignal())
        return false;
    //等待玻璃到载台上
    MotionControl m;
    m.outPutDo(0,8,1);
    m.outPutDo(0,9,1);
    delay_msc(500);
    m.outPutDo(0,8,0);
    m.outPutDo(0,9,0);
    if(ShareData::GetInstance()->m_position.contains("PointS"))
    {
        QMap<int,int> pos = ShareData::GetInstance()->m_position["PointS"];
        return m.runPosition(pos);
    }
    return false;
}

///
/// \brief LogicalFlow::printX 喷头的x方向的来回移动
/// \return
///
bool LogicalFlow::printX()
{
    if(false == ckeckEmgSignal())
        return false;
    MotionControl m;
    QMap<int,int> pos;
    pos.clear();
    if(ShareData::GetInstance()->m_position.contains("BeginE"))
    {
        pos.clear();
        pos = ShareData::GetInstance()->m_position["BeginE"];
        if(!m.runPosition(pos))
        {
            QLOG_INFO()<<"print flow failed;";
            return false;
        }
    }
    if(false == ckeckEmgSignal())
        return false;
    delay_msc(500);
    if(ShareData::GetInstance()->m_position.contains("BeginS"))
    {
        pos.clear();
        pos = ShareData::GetInstance()->m_position["BeginS"];
        if(!m.runPosition(pos))
        {
            QLOG_INFO()<<"print flow failed;";
            return false;
        }
    }
    return true;
}

///
/// \brief LogicalFlow::printFlow 一个整体的打印流程
/// \return
///
bool LogicalFlow::printFlow()
{
    if(ShareData::GetInstance()->m_position.contains("PointS"))
    {
        if(false == printX())
        {
            QLOG_INFO()<<"打印中出现异常";
            return false;
        }
        delay_msc(800);
        int begin_y = 0;
        QMap<int,int> pos = ShareData::GetInstance()->m_position["PointS"];
        if(pos.contains(0))
        {
            begin_y = pos[0];
            for(int i = 1 ; i < 4; i++)
            {
                if(false == ckeckEmgSignal())
                    return false;
                begin_y =  begin_y + (i*20000);
                QMap<int,int> p;
                p.clear();
                p.insert(0,begin_y);
                MotionControl m;
                m.runPosition(p);
                delay_msc(800);
                if(false == printX())
                {
                    QLOG_INFO()<<"打印中出现异常";
                    return false;
                }
                delay_msc(800);
            }
        }

    }
    return true;
}

///
/// \brief LogicalFlow::airInit 设备开始前 气缸应该在的初始位置
/// \return
///
bool LogicalFlow::airInit()
{
    MotionControl m;
    if(m.airActionOff(1,10,20)) //上升气缸原点
    {
        if(m.airActionOff(1,11,16)) //拍边原点
        {
            if(m.airActionOn(1,13,18))//阻挡动点
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

///
/// \brief LogicalFlow::airAction 玻璃到达载台后气缸固定拍边等 固定的流程
/// \return
///
bool LogicalFlow::airAction()
{
    MotionControl m;
    if(m.airActionOn(1,10,21)) //上升气缸原点
    {
        delay_msc(200);
        if(m.airActionOn(1,11,17)) //拍边原点
        {
            delay_msc(200);
            if(m.airActionOff(1,13,19))//阻挡动点
            {
                delay_msc(200);
                if(m.airActionOff(1,11,16)) //拍边气缸复位
                {
                    delay_msc(200);
                    if(m.airActionOff(1,10,20))//上升气缸复位
                    {
                        return true;
                    }
                    else
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

///
/// \brief LogicalFlow::glassBack 打印完成后将玻璃送到流道口，默认位置在Y=0 xxy载台复位，默认在xxy=0
/// \return
///
bool LogicalFlow::glassBack()
{
    if(false == ckeckEmgSignal())
        return false;
    MotionControl m;
    QMap<int,int> p;
    p.insert(0,0);
    p.insert(1,0);
    p.insert(2,0);
    p.insert(3,0);
    return m.runPosition(p);//回到接料的位置
}

///
/// \brief LogicalFlow::runPosition 运动到某个点位
/// \param positionName 点位的名称
/// \return
///
bool LogicalFlow::runPosition(const QString &positionName)
{
    if(false == ckeckEmgSignal())
        return false;
    MotionControl m;
    QMap<int,int> pos;
    pos.clear();
    if(ShareData::GetInstance()->m_position.contains(positionName))
    {
        pos.clear();
        pos = ShareData::GetInstance()->m_position[positionName];
        if(!m.runPosition(pos))
        {
            QLOG_INFO()<<"位置:"<<positionName<<":移动中失败";
            return false;
        }
        else
            return true;
    }
    return false;
}

///
/// \brief LogicalFlow::airVoid
/// \param isVoid true = 吸  false = 破
///
void LogicalFlow::airVoid(const bool isVoid)
{
    MotionControl m;
    if(true == isVoid)
    {
        m.outPutDo(0,14,1); //平台吸气
    }
    else
        m.outPutDo(0,14,0); //平台吸气
}

bool LogicalFlow::airOn(const int &car, const int &out, const int &checkId)
{
    MotionControl m;
    return m.airActionOn(car,out,checkId);
}

///
/// \brief LogicalFlow::runOffect 根据相机给的角点坐标 进行补偿
/// \param cornerPosition  角点的坐标
/// \return
///
bool LogicalFlow::runOffect(QMap<double, double> &cornerPosition)
{
    if(false == ckeckEmgSignal())
        return false;
    auto it = cornerPosition.begin();
    QMap<int,int> mark = ShareData::GetInstance()->m_position["markPosition"];
    MotionControl  m;
    if((it.key()-mark[2])/2000 > 10 ||  (it.key()-mark[2])/2000 > 10)
    {
        return false;
    }
    m.relativeMove(2,(it.key()-mark[2]));
    m.relativeMove(1,-1*(it.key()-mark[2]));
    m.relativeMove(3,-1*(it.value()-mark[3]));
    return true;
}

void LogicalFlow::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}

bool LogicalFlow::ckeckEmgSignal()
{
    if(ShareData::GetInstance()->m_stopFlag == true)
    {
        QLOG_WARN()<<"在运动的时检测到用户按下急停信号";
        return false;
    }
    return true;

}
