#include "parameterfrom.h"
#pragma execution_character_set("utf-8")
ParameterFrom::ParameterFrom(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->width(),parent->height());

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->resize(parent->width()-10,parent->height()-70);
    scrollArea->setFrameStyle(0);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    m_pcontainer = new QWidget(scrollArea);
   // m_pcontainer->resize(parent->width()-20,parent->height());
    scrollArea->setWidget(m_pcontainer);


    m_vbox = new QVBoxLayout();
    for(int i = 0; i < 8; i++)
    {
        if(i== 4 || i == 5 || i== 6 || i == 7)
            continue;
        m_axisParameter[i] = new AxisParameterSet(i,QSize(this->width()-35,this->height()));
        if(ShareData::GetInstance()->m_axisMap.contains(i))
        {
             m_axisParameter[i]->setParameter(ShareData::GetInstance()->m_axisMap[i]);
        }
        m_axisVec.push_back( m_axisParameter[i]);
         m_axisParameter[i]->setMinimumSize(parent->width()-35,90);
        m_vbox->addWidget( m_axisParameter[i]);
    }

    for(int i = 0; i < 10; i++)
    {
        if(i+14 == 17 || i+14 == 21 || i+14 == 22|| i+14 == 23)
            continue;
        m_axisParameter2[i] = new AxisParameterSet(i+14,QSize(this->width()-35,this->height()));
        if(ShareData::GetInstance()->m_axisMap.contains(i+14))
        {
             m_axisParameter2[i]->setParameter(ShareData::GetInstance()->m_axisMap[i+14]);
        }
        m_axisVec.push_back( m_axisParameter2[i]);
         m_axisParameter2[i]->setMinimumSize(parent->width()-35,90);
        m_vbox->addWidget( m_axisParameter2[i]);
    }
    m_axisU = new AxisParameterSet(27,QSize(this->width()-35,this->height()));
    if(ShareData::GetInstance()->m_axisMap.contains(27))
    {
         m_axisU->setParameter(ShareData::GetInstance()->m_axisMap[27]);
    }
    m_axisVec.push_back(m_axisU);
     m_axisU->setMinimumSize(parent->width()-35,90);
    m_vbox->addWidget(m_axisU);
    m_vbox->addStretch(0);
    m_pcontainer->setLayout(m_vbox);
    m_pcontainer->setStyleSheet("QPushButton:{background-color:rgb(130,130,130)}");
}

void ParameterFrom::save()
{
    for (int i = 0; i< m_axisVec.size();i++)
    {
        m_axisVec.at(i)->saveParameter();
    }
}
