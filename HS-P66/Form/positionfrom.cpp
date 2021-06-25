#include "positionfrom.h"
#pragma execution_character_set("utf-8")
PositionFrom::PositionFrom(const QString &posName, const QVector<int> &axisVec, QWidget *parent) : QWidget(parent)
{
    this->resize(1100,50);
    m_pointName = posName;
    QLabel *posNameLabel = new QLabel(posName);
    posNameLabel->setMinimumWidth(70);
    QFont font("Times", 14);
    posNameLabel->setFont(font);
    posNameLabel->setStyleSheet("background-color:rgb(10,20,30);color:white;border-radius:5px;");
    hbox = new QHBoxLayout();
    hbox->addWidget(posNameLabel);
    QFont font_name("Helvetica",9, QFont::Normal);
    for (int i = 0;i < axisVec.size();i++) {
        m_paxisId = new QLabel(axisId2axisName(axisVec.at(i)));
        m_paxisId->setMinimumWidth(80);
        m_paxisId->setFont(font_name);
        QSpinBox *pos = new QSpinBox();
        pos->setMaximum(999999999);
        pos->setObjectName(QString::number(axisVec.at(i)));//spinbox objName = axis id
        m_spinBoxVec.push_back(pos);
        hbox->addWidget(m_paxisId);
        hbox->addWidget(pos);
        hbox->addStretch();
    }
    m_pSaveBtn = new QPushButton("Save");
    connect(m_pSaveBtn,&QPushButton::clicked,this,&PositionFrom::onSaveBtnCliked);
    hbox->addWidget(m_pSaveBtn);
    this->setLayout(hbox);
    this->setObjectName("PositionFrom");
    this->setAutoFillBackground(true);
    setPalette(QPalette(QColor(201,201,201)));
    this->setStyleSheet("QPushButton{ background-color:rgb(70,70,70);Min-width:57px;Min-height:35px;color:white}QPushButton:hover{background-color:rgb(110,210,110)}QPushButton:pressed{background-color:rgb(160,160,160)}QSpinBox{Padding-right:20px;Border:2px solid white;font:18px; Min-width:67px;Min-height:25px;border-radius:5px;}QSpinBox::up-button,QSpinBox::down-button{ width:0px;}");

}
///
/// \brief PositionFrom::setParameter
/// \param posMap axisId,position
///
void PositionFrom::setParameter(const QMap<int, int> &posMap)
{
    foreach (QSpinBox *p, m_spinBoxVec)
    {
        if(posMap.contains(p->objectName().toInt()))
        {
            p->setValue(posMap[p->objectName().toInt()]);
            //qDebug()<<"setvalue :"<<posMap[p->objectName().toInt()];
        }
    }
}

void PositionFrom::onSaveBtnCliked()
{
    QStringList names;
    names<<"point_name"<<"point_info";
    QStringList values;
    QString posInfo = "";
    for(int i = 0; i< m_spinBoxVec.size();i++)
    {
        int axisId = m_spinBoxVec.at(i)->objectName().toInt();
        long int position = 0;
        int ret = APS_get_position(axisId,&position);
        if(ret == ERR_NoError)
        {
            m_spinBoxVec.at(i)->setValue(position);
        }

        posInfo += m_spinBoxVec.at(i)->objectName();
        posInfo += ":";
        posInfo += QString::number(m_spinBoxVec.at(i)->value());
        if(i != m_spinBoxVec.size()-1)
            posInfo += ";";
    }
    values<<m_pointName<<posInfo;
   if(false == DataBaseManager::GetInstance()->ExcInsertDb("t_point",names,values))
   {
       names.clear();
       values.clear();
       names<<"point_info";
       values<<posInfo;
       QString ex = QString("point_name = '%1'").arg(m_pointName);
       DataBaseManager::GetInstance()->ExcUpdateDb("t_point",names,values,ex);
   }
}

QString PositionFrom::axisId2axisName(const int &id)
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
