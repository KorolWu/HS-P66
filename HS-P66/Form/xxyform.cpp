#include "xxyform.h"
#pragma execution_character_set("utf-8")

XXYForm::XXYForm(QWidget *parent):QWidget(parent)
{
    initUi();
}

void XXYForm::initUi()
{
    QGroupBox *groupUp = new QGroupBox(this);
    groupUp->resize(500,230);
    groupUp->setTitle("Move");
    QLabel *angle = new QLabel("角度：",groupUp);
    angle->move(20,100);
    m_pAngle = new QSpinBox(groupUp);
    m_pAngle->setAlignment(Qt::AlignCenter);// 设置居中
    m_pAngle->move(93,95);
    for (int i = 0 ;i < 6;i++) {
        m_btn[i] = new QPushButton(groupUp);
        m_btn[i]->resize(65,35);
        m_btn[i]->setObjectName(QString("btn_%1").arg(i));
        connect(m_btn[i],&QPushButton::clicked,this,&XXYForm::onBtnClicked);
    }
    m_btn[0]->move(90,140);//旋转按钮
    m_btn[0]->setText("旋转");

    m_btn[1]->move(320,60);//Y+
    m_btn[1]->setText("Y+");
    m_pDistance= new QSpinBox(groupUp);
    m_pDistance->setAlignment(Qt::AlignCenter);// 设置居中
    m_pDistance->move(320,110);
    QLabel *l =new QLabel("mm",groupUp);
    l->move(377,112);
    m_btn[2]->move(320,150);//Y-
    m_btn[2]->setText("Y-");
    m_btn[3]->move(220,110);//X+
    m_btn[3]->setText("X+");
    m_btn[4]->move(420,110);//X-
    m_btn[4]->setText("X-");
    m_btn[5]->setText("Home");//home
    m_btn[5]->move(20,140);

    QGroupBox *groupDown = new QGroupBox(this);
    groupDown->resize(500,200);
    groupDown->move(0,250);
    groupDown->setTitle("Monitor");
    QHBoxLayout *hbox = new QHBoxLayout();
    QLabel *x1 = new QLabel("X1:",groupDown);
    m_pX1 = new QSpinBox(groupDown);
    hbox->addWidget(x1);
    hbox->addWidget(m_pX1);
    hbox->addStretch();
    m_pVbox = new QVBoxLayout();
    m_pVbox->addLayout(hbox);
    QLabel *y1 = new QLabel("Y1:",groupDown);
    m_pY1 = new QSpinBox(groupDown);
    hbox->addWidget(y1);
    hbox->addWidget(m_pY1);

    QLabel *x2 = new QLabel("X2:",groupDown);
    m_pX2 = new QSpinBox(groupDown);
    hbox = new QHBoxLayout();
    hbox->addWidget(x2);
    hbox->addWidget(m_pX2);
    hbox->addStretch();
    QLabel *a = new QLabel("Angle:",groupDown);
    m_pA = new QSpinBox(groupDown);
    hbox->addWidget(a);
    hbox->addWidget(m_pA);

    m_pVbox->addLayout(hbox);
    groupDown->setLayout(m_pVbox);
    groupUp->setStyleSheet("QLabel{font: 20px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:18px; Min-width:27px;Min-height:25px;border-radius:5px;}QSpinBox::up-button,QSpinBox::down-button{ width:0px;}QGroupBox{border: 2px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 22px;}");
    groupDown->setStyleSheet("QLabel{font: 20px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Min-width:70px;Min-height:25px;border-radius:5px;}QSpinBox::up-button,QSpinBox::down-button{ width:0px;}QGroupBox{border: 2px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 22px;}");

}

void XXYForm::onBtnClicked()
{
    QString btnName = sender()->objectName();
    if(btnName == "btn_3")//x+
    {

    }
    else if(btnName == "btn_0")//旋转
    {
        XxyCalc c;
        double x1,x2,y1;
        c.AFDegConvert(-1,0,&x1,&x2,&y1);
        qDebug()<<x1<<x2<<y1;
    }

}
