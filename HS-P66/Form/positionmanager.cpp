#include "positionmanager.h"

PositionManager::PositionManager(QWidget *parent) : QWidget(parent)
{
   this->resize(parent->width()-5,parent->height()-5);
   //this->setStyleSheet("background-color:grb(102,139,139)");
    m_width = parent->width();
    m_height = parent->height();
    initUi();
}

void PositionManager::initUi()
{
    QGroupBox *group = new QGroupBox(this);
    QVBoxLayout *vbox = new QVBoxLayout();

    QVector<int> vec;
    vec.push_back(0);
    vec.push_back(14);
    PositionFrom *test = new PositionFrom("PointS",vec);
    test->setParameter(ShareData::GetInstance()->m_position["PointS"]);
    vbox->addWidget(test);
    vec.clear();
    vec.push_back(14);
    PositionFrom *test1 = new PositionFrom("BeginS",vec);
     test1->setParameter(ShareData::GetInstance()->m_position["BeginS"]);
    test1->move(0,80);
    vec.clear();
    vec.push_back(14);
    vbox->addWidget(test1);
    PositionFrom *test2 = new PositionFrom("BeginE",vec);
    test2->setParameter(ShareData::GetInstance()->m_position["BeginE"]);
    test2->move(0,210);
    vbox->addWidget(test2);
    vec.clear();
    vec.push_back(16);
    PositionFrom *test3 = new PositionFrom("Zup",vec);
    test3->move(0,280);
    vbox->addWidget(test3);
    test3->setParameter(ShareData::GetInstance()->m_position["Zup"]);
    //----
    vec.clear();
    vec.push_back(16);
    PositionFrom *test4 = new PositionFrom("Zdown",vec);
    vbox->addWidget(test4);
    test4->setParameter(ShareData::GetInstance()->m_position["Zdown"]);
    vec.clear();
    vec.push_back(15);
    PositionFrom *test5 = new PositionFrom("NozzleUp",vec);
    vbox->addWidget(test5);
    test5->setParameter(ShareData::GetInstance()->m_position["NozzleUp"]);

    PositionFrom *test6 = new PositionFrom("NozzleDown",vec);
    vbox->addWidget(test6);
    test6->setParameter(ShareData::GetInstance()->m_position["NozzleDown"]);

    vec.clear();
    vec.push_back(1);
     vec.push_back(2);
      vec.push_back(3);
    PositionFrom *test7 = new PositionFrom("Camera_R",vec);
    vbox->addWidget(test7);
    test7->setParameter(ShareData::GetInstance()->m_position["Camera_R"]);

    PositionFrom *camera_l = new PositionFrom("Camera_L",vec);
    vbox->addWidget(camera_l);
    test7->setParameter(ShareData::GetInstance()->m_position["Camera_L"]);

            PositionFrom *markPosition = new PositionFrom("markPosition",vec);
            vbox->addWidget(markPosition);
            test7->setParameter(ShareData::GetInstance()->m_position["markPosition"]);
    //----
    group->setLayout(vbox);
    m_pX = new AxisInfoUI(14,this);
    m_pX->SetAxisName("X");
    m_pX->move(m_width - 405, 10);
    m_pY = new AxisInfoUI(10,this);
    m_pY->SetAxisName("Y");
    m_pY->move(m_width - 405, 220);
    m_pZ = new AxisInfoUI(15,this);
    m_pZ->SetAxisName("Z");
    m_pZ->move(m_width - 405, 430);
}
