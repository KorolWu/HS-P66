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
    explicit ParameterFrom(QWidget *parent = nullptr);

private:
    QWidget* m_pcontainer;
    AxisParameterSet *s;
    AxisParameterSet *y;
    AxisParameterSet *z;
    AxisParameterSet *u;
    AxisParameterSet *e;
    AxisParameterSet *g;
    AxisParameterSet *h;
    QPushButton *m_pSaveBtn;
    QPushButton *m_pReadBtn;
    QVBoxLayout *m_vbox;
    QVector<AxisParameterSet*> m_axisVec;
signals:

public slots:
    void save();
};

#endif // PARAMETERFROM_H
