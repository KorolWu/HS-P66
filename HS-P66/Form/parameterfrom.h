#ifndef PARAMETERFROM_H
#define PARAMETERFROM_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include "sharedata.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "axisparameterset.h"

class ParameterFrom : public QWidget
{
    Q_OBJECT
public:
     ParameterFrom(QWidget *parent = nullptr);

private:
    QWidget* m_pcontainer;
    AxisParameterSet *m_axisParameter[8];
        AxisParameterSet *m_axisParameter2[10];
//    AxisParameterSet *m_A0;
//    AxisParameterSet *m_A1;
//    AxisParameterSet *m_A2;
//    AxisParameterSet *m_A3;
//    AxisParameterSet *m_A4;
//    AxisParameterSet *m_A5;
//    AxisParameterSet *m_A6;
//    AxisParameterSet *m_A7;
//    AxisParameterSet *m_A14;
//    AxisParameterSet *m_A15;
//    AxisParameterSet *m_A16;
//    AxisParameterSet *m_A17;
//    AxisParameterSet *m_A18;
//    AxisParameterSet *m_A19;
//    AxisParameterSet *m_A20;
//    AxisParameterSet *m_A21;
//    AxisParameterSet *m_A22;
//    AxisParameterSet *m_A23;
    QPushButton *m_pSaveBtn;
    QPushButton *m_pReadBtn;
    QVBoxLayout *m_vbox;
    QVector<AxisParameterSet*> m_axisVec;
signals:

public slots:
    void save();
};

#endif // PARAMETERFROM_H
