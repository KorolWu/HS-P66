#include "ioform.h"

IoForm::IoForm(QWidget *parent) :QWidget(parent)
{

   this->resize(parent->width(),parent->height());
   m_vbox = new QVBoxLayout();
   int car_1_id = 1;
   QStringList list_1;
   QStringList outAlisa;
   IoMonitor *car_1 = new IoMonitor(car_1_id,list_1,outAlisa);
   m_vbox->addWidget(car_1);

   int car_2_id = 2;
   QStringList list_2;
    QStringList outAlisa2;
   IoMonitor *car_2 = new IoMonitor(car_2_id,list_2,outAlisa2);
   m_vbox->addWidget(car_2);

   int car_3_id = 3;
   QStringList list_3;
    QStringList outAlisa3;
   IoMonitor *car_3 = new IoMonitor(car_3_id,list_3,outAlisa3);
   m_vbox->addWidget(car_3);
   m_vbox->addStretch();
   this->setLayout(m_vbox);
  // this->setStyleSheet("background-color:rgb(130,130,130)");
}
