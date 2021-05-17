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
    MyIniConfig f;
    f.Config();
    f.Set(QString("Axis%1").arg(m_axisId),"Vmax",m_vMax->value());
    f.Set(QString("Axis%1").arg(m_axisId),"Acc",m_acc->value());
    f.Set(QString("Axis%1").arg(m_axisId),"Dcc",m_dcc->value());
    f.Set(QString("Axis%1").arg(m_axisId),"HomeVmax",m_hVmax->value());
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
    m_groupBox->resize(m_width-10,100);
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
    QLabel *dcc = new QLabel("Dcc: ");
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
    m_groupBox->setLayout(m_hbox);
    this->setStyleSheet("QLabel{font: 24px;}QSpinBox{Padding-right:20px;Border:2px solid gray;font:20px; Min-width:90px;Min-height:25px;border-radius:5px;}QGroupBox{border: 1px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 28px;}");

}

QString AxisParameterSet::axisId2axisName(int id)
{
    switch (id) {
    case 0:
        return "上载台Y";
    case 1:
        return "上载台旋转Y2";
    default:
        return "UnKnow";
    }
}
