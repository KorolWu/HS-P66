#ifndef AXISPARAMETERSET_H
#define AXISPARAMETERSET_H

#include <QObject>
#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QDebug>
#include "DataStruct.h"
#include "databasemanager.h"
#include <Units/myIniconfig.h>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>

class AxisParameterSet : public QWidget
{
    Q_OBJECT
public:
    explicit AxisParameterSet(int axisId, QSize size, QWidget *parent = nullptr);
    void saveParameter();
    void setParameter(const AxisStruct &axisStruct);
signals:
private:
    int m_width;
    int m_height;
    int m_axisId;
    QHBoxLayout *m_hbox;
    QGroupBox *m_groupBox;
    QSpinBox *m_vMax;
    QSpinBox *m_dcc;
    QSpinBox *m_acc;
    QSpinBox *m_hVmax;
    QPushButton *m_saveBtn;
    void initUI();
    QString axisId2axisName(int id);
public slots:
};

#endif // AXISPARAMETERSET_H
