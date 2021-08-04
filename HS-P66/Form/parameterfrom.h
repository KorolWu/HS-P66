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
    AxisParameterSet *m_axisU;

    QVBoxLayout *m_vbox;
    QVector<AxisParameterSet*> m_axisVec;
signals:

public slots:
    void save();
};

#endif // PARAMETERFROM_H
