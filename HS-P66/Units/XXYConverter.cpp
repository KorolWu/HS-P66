#include <math.h>
#include "XXYConverter.h"



#define PI 3.1415926535898
#define DEG2RAD(x) (x * PI / 180)


//650系列参数
#define PARAM_R 388.91  //mm

//度
#define PARAM_X1 315
#define PARAM_X2 135
#define PARAM_Y 225


#define RAD_X1 DEG2RAD(PARAM_X1)
#define RAD_X2 DEG2RAD(PARAM_X2)
#define RAD_Y DEG2RAD(PARAM_Y)


bool XxyCalc::AFRadConvert(double deltaRad, double curRad, double * deltaX1, double * deltaX2, double * deltaY)
{
	if (deltaX1 == nullptr || deltaX2 == nullptr || deltaY == nullptr)
		return false;

	//判断是否接近0度
    if (::fabs(deltaRad * 10000) < 1)
	{
		*deltaX1 = 0;
		*deltaX2 = 0;
		*deltaY = 0;
	}
	else
	{
        *deltaX1 = PARAM_R * cos(deltaRad + curRad + RAD_X1) - PARAM_R * cos(RAD_X1 + curRad);
        *deltaX2 = -1 * (PARAM_R * cos(deltaRad + curRad + RAD_X2) - PARAM_R * cos(RAD_X2 + curRad));

        *deltaY = -1 * (PARAM_R * sin(deltaRad + curRad + RAD_Y) - PARAM_R * sin(RAD_Y + curRad));
	}

	return true;
}


bool XxyCalc::AFDegConvert(double deltaDeg, double curDeg, double * deltaX1, double * deltaX2, double * deltaY)
{
    return AFRadConvert(DEG2RAD(deltaDeg), DEG2RAD(curDeg), deltaX1, deltaX2, deltaY);
}
XxyCalc::XxyCalc()
{

}
