#include "axischeck.h"
#pragma execution_character_set("utf-8")
AxisCheck::AxisCheck(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width(),parent->height()+10);
    this->setStyleSheet("background-color:rgb(130,130,130)");

    int f_height = 230;


    //旋转平台x2靠喷头方向
    AxisInfoUI *axis_upX1 = new AxisInfoUI(1,this);
    axis_upX1->SetAxisName("旋转X2");
    axis_upX1->move(405,f_height+10);

    //旋转平台x1靠进料方向
    AxisInfoUI *axis_upX2 = new AxisInfoUI(2,this);
    axis_upX2->SetAxisName("旋转X1");
    axis_upX2->move(3,f_height+10);

    //旋转平台y
    AxisInfoUI *axis_upY = new AxisInfoUI(3,this);
    axis_upY->SetAxisName("旋转Y");
    axis_upY->move(806,f_height+10);

    //    //内卡边电机
    //    AxisInfoUI *axis_upL = new AxisInfoUI(4,this);
    //    axis_upL->SetAxisName("内卡边");
    //    axis_upL->move(3,f_height+10);

    //    //外卡边电机
    //    AxisInfoUI *axis_upR = new AxisInfoUI(5,this);
    //    axis_upR->SetAxisName("外卡边");
    //    axis_upR->move(405,f_height+10);


    //    //内CCD
    //    AxisInfoUI *axis_ccdL = new AxisInfoUI(6,this);
    //    axis_ccdL->SetAxisName("左CCD");
    //    axis_ccdL->move(806,f_height+10);

    //    //外CCD
    //    AxisInfoUI *axis_ccdR = new AxisInfoUI(7,this);
    //    axis_ccdR->SetAxisName("右CCD");
    //    axis_ccdR->move(1206,f_height+10);

    AxisInfoUI *axis_X = new AxisInfoUI(14,this);
    axis_X->SetAxisName("喷头X");
    axis_X->move(3,(f_height+10)*2);

    AxisInfoUI *axis_y = new AxisInfoUI(0,this);
    axis_y->SetAxisName("上载台Y");
    axis_y->move(405,(f_height+10)*2);

    AxisInfoUI *axis_Z = new AxisInfoUI(15,this);
    axis_Z->SetAxisName("喷头Z");
    axis_Z->move(806,(f_height+10)*2);



    //    //出料升降电机
    //    AxisInfoUI *axis_outZ = new AxisInfoUI(17,this);
    //    axis_outZ->SetAxisName("出料Z");
    //    axis_outZ->move(1206,(f_height+10)*2);

    //进料调整电机X
    //    AxisInfoUI *axis_inX = new AxisInfoUI(20,this);
    //    axis_inX->SetAxisName("进料X");
    //    axis_inX->move(3,10);
    //进料y
    AxisInfoUI *axis_inY1 = new AxisInfoUI(18,this);
    axis_inY1->SetAxisName("进料Y1");
    axis_inY1->move(3,10);

    //进料y2
    AxisInfoUI *axis_inY2 = new AxisInfoUI(19,this);
    axis_inY2->SetAxisName("进料Y2");
    axis_inY2->move(405,10);

    //进料升降电机
    AxisInfoUI *axis_inZ = new AxisInfoUI(16,this);
    axis_inZ->SetAxisName("进料Z");
    axis_inZ->move(806,10);
    //    //出料调整电机Y
    //    AxisInfoUI *axis_outX = new AxisInfoUI(21,this);
    //    axis_outX->SetAxisName("出料X");
    //    axis_outX->move(1206,(f_height+5)*3);

    //喷头的旋转轴
    AxisInfoUI *axis_U = new AxisInfoUI(27,this);
    axis_U->SetAxisName("喷头旋转");
    axis_U->move(3,(f_height)*3);


}
