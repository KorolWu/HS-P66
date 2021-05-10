#include "axischeck.h"

AxisCheck::AxisCheck(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width(),parent->height());
    this->setStyleSheet("background-color:rgb(130,130,130)");
    AxisInfoUI *axis_x = new AxisInfoUI(21,this);
    axis_x->SetAxisName("X");
    axis_x->move(10,10);

    AxisInfoUI *axis_y = new AxisInfoUI(22,this);
    axis_y->SetAxisName("Y");
    axis_y->move(430,10);


    AxisInfoUI *axis_z = new AxisInfoUI(32,this);
    axis_z->SetAxisName("Z");
    axis_z->move(860,10);
}
