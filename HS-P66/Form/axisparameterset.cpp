#include "axisparameterset.h"
#pragma execution_character_set("utf-8")
AxisParameterSet::AxisParameterSet(int axisId, QSize size, QWidget *parent) : QWidget(parent)
{
    m_width = size.width();
    m_height = size.height();
    m_axisId = axisId;
    this->resize(size);
    initUI();
}
///
/// \brief AxisParameterSet::saveParameter
///
/// 根据轴号保存该轴的加减速和回原点最大速度
void AxisParameterSet::saveParameter()
{
//    MyIniConfig f;
//    f.Config();
//    f.Set(QString("Axis%1").arg(m_axisId),"Vmax",m_vMax->value());
//    f.Set(QString("Axis%1").arg(m_axisId),"Acc",m_acc->value());
//    f.Set(QString("Axis%1").arg(m_axisId),"Dcc",m_dcc->value());
//    f.Set(QString("Axis%1").arg(m_axisId),"HomeVmax",m_hVmax->value());

    //save sqlit
    QString axisId = QString("Axis_%1").arg(m_axisId);
    QStringList names;
    names<<"acc"<<"dec"<<"v_max"<<"home_vMax";
    QStringList values;
    values<<QString::number(m_acc->value())<<QString::number(m_dcc->value())<<QString::number(m_vMax->value())<<QString::number(m_hVmax->value());
    QString ex = QString("axis_name = '%1'").arg(axisId);
    DataBaseManager::GetInstance()->ExcUpdateDb("t_axisInfo",names,values,ex);
}
///
/// \brief AxisParameterSet::setParameter
/// \param axisStruct
///
void AxisParameterSet::setParameter(const AxisStruct &axisStruct)
{
   m_vMax->setValue(axisStruct.vMax);
   m_acc->setValue(axisStruct.acc);
   m_dcc->setValue(axisStruct.dcc);
   m_hVmax->setValue(axisStruct.homeVmax);
}

void AxisParameterSet::initUI()
{
    m_groupBox = new QGroupBox(this);
    m_groupBox->setTitle(axisId2axisName(m_axisId));
    //    m_groupBox->setMinimumHeight(100);
    m_groupBox->resize(m_width-10,80);
    m_hbox = new QHBoxLayout();
    QLabel *max_v = new QLabel("MaxV: ");
    m_vMax = new QSpinBox();
    m_vMax->setMaximum(9000000);
    m_hbox->addWidget(max_v);
    m_hbox->addWidget(m_vMax);
    m_hbox->addStretch();
    QLabel *acc = new QLabel("Acc: ");
    m_acc = new QSpinBox();
    m_acc->setMaximum(9000000);
    m_hbox->addWidget(acc);
    m_hbox->addWidget(m_acc);
    m_hbox->addStretch();
    QLabel *dcc = new QLabel("Dec: ");
    m_dcc = new QSpinBox();
    m_dcc->setMaximum(9000000);
    m_hbox->addWidget(dcc);
    m_hbox->addWidget(m_dcc);
    m_hbox->addStretch();
    QLabel *max_hove_v = new QLabel("HomeV: ");
    m_hVmax = new QSpinBox();
    m_hVmax->setMaximum(9000000);
    m_hbox->addWidget(max_hove_v);
    m_hbox->addWidget(m_hVmax);
    m_hbox->addStretch();
    m_saveBtn = new QPushButton("Save");
    m_saveBtn->setIcon(QIcon(":/src/Image/save.png"));
    m_saveBtn->setFixedSize(66,35);
    connect(m_saveBtn,&QPushButton::clicked,this,&AxisParameterSet::saveParameter);
    m_hbox->addWidget(m_saveBtn);

    m_groupBox->setLayout(m_hbox);
    this->setStyleSheet("QLabel{font: 18px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Min-width:90px;Min-height:25px;border-radius:5px;}QGroupBox{border: 2px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 20px;}");

}

QString AxisParameterSet::axisId2axisName(int id)
{
    switch (id) {
    case 0:
        return "上载台Y";
    case 1:
        return "上载台旋转X2";
    case 2:
        return "上载台旋转X1";
    case 3:
        return "上载台旋转Y";
    case 4:
        return "上载台内卡边";
    case 5:
        return "上载台外卡边";
    case 6:
        return "左CCD";
    case 7:
        return "右CCD";
    case 14:
        return "喷头X";
    case 15:
        return "喷头Z";
    case 16:
        return "进料Z";
    case 17:
        return "出料Z";
    case 18:
        return "进料Y1";
    case 19:
        return "进料Y2";
    case 20:
        return "进料X";
    case 21:
        return "出料X";
    case 22:
        return "出料Y1";
    case 23:
        return "出料Y2";
    default:
        return "UnKnow";
    }
}
