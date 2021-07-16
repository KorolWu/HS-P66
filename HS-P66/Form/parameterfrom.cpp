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

//    y = new AxisParameterSet(7,QSize(this->width()-35,this->height()));
//    if(ShareData::GetInstance()->m_axisMap.contains(7))
//    {
//        y->setParameter(ShareData::GetInstance()->m_axisMap[7]);
//    }
//     m_axisVec.push_back(y);
//    y->setMinimumSize(parent->width()-35,100);
//    m_vbox->addWidget(y);
//    z = new AxisParameterSet(2,QSize(this->width()-35,this->height()));
//    if(ShareData::GetInstance()->m_axisMap.contains(2))
//    {
//        qDebug()<<"is contains!";
//        z->setParameter(ShareData::GetInstance()->m_axisMap[2]);
//    }
//     m_axisVec.push_back(z);
//    z->setMinimumSize(parent->width()-35,100);
//    m_vbox->addWidget(z);
//    u = new AxisParameterSet(3,QSize(this->width()-35,this->height()));
//    if(ShareData::GetInstance()->m_axisMap.contains(3))
//    {
//        u->setParameter(ShareData::GetInstance()->m_axisMap[3]);
//    }
//     m_axisVec.push_back(u);
//    u->setMinimumSize(parent->width()-35,100);
//    m_vbox->addWidget(u);
//    e = new AxisParameterSet(4,QSize(this->width()-35,this->height()));
//    if(ShareData::GetInstance()->m_axisMap.contains(4))
//    {
//        e->setParameter(ShareData::GetInstance()->m_axisMap[4]);
//    }
//     m_axisVec.push_back(e);
//    e->setMinimumSize(parent->width()-35,100);
//    m_vbox->addWidget(e);

//    g = new AxisParameterSet(5,QSize(this->width()-35,this->height()));
//    if(ShareData::GetInstance()->m_axisMap.contains(5))
//    {
//        g->setParameter(ShareData::GetInstance()->m_axisMap[5]);
//    }
//     m_axisVec.push_back(g);
//    g->setMinimumSize(parent->width()-35,100);
//    m_vbox->addWidget(g);

//    h = new AxisParameterSet(6,QSize(this->width()-35,this->height()));
//    if(ShareData::GetInstance()->m_axisMap.contains(6))
//    {
//        h->setParameter(ShareData::GetInstance()->m_axisMap[6]);
//    }
//     m_axisVec.push_back(h);
//    h->setMinimumSize(parent->width()-35,100);
//    m_vbox->addWidget(h);

//    QHBoxLayout *hbox = new QHBoxLayout();
//    hbox->addStretch();
//    m_pReadBtn = new QPushButton("读取");
//    m_pReadBtn->setFixedSize(100,50);
//    hbox->addWidget(m_pReadBtn);
//    hbox->addStretch();
//    m_pSaveBtn = new QPushButton("保存");
//    connect(m_pSaveBtn,&QPushButton::clicked,this,&ParameterFrom::save);
//    hbox->addWidget(m_pSaveBtn);
//    m_pSaveBtn->setFixedSize(100,50);
//    m_vbox->addLayout(hbox);
//    hbox->addStretch();
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
