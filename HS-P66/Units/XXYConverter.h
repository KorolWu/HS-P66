﻿#pragma once

/*********************A&F角度装换公式****************/
class XxyCalc
{
public:
    XxyCalc();
    //将制定角度转换成三轴运动距离

    //deltaDeg ： 需要偏移的角度（顺时针为负，逆时针为正）
    //deltaX1 ：X1轴需要行走的距离mm
    //deltaX2 ：X2轴需要行走的距离mm
    //deltaY ：Y轴需要行走的距离mm
    bool AFDegConvert(double deltaDeg, double curDeg, double * deltaX1, double * deltaX2, double * deltaY);

    //deltaRad ： 需要偏移的弧度（顺时针为负，逆时针为正）
    //其余同上
    bool AFRadConvert(double deltaRad, double curRad, double * deltaX1, double * deltaX2, double * deltaY);


    bool AFConvert2Deg(double * deltaDeg, double deltaX1, double deltaX2, double deltaY);
};
