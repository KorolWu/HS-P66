#ifndef POSITIONFROM_H
#define POSITIONFROM_H

#include "APS168.h"
#include "type_def.h"
#include "APS_Define.h"
#include "ErrorCodeDef.h"
#include <QObject>
#include <QWidget>
#include <QSpinBox>
#include <QVector>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include "databasemanager.h"

class PositionFrom : public QWidget
{
    Q_OBJECT
public:
    explicit PositionFrom(const QString &posName,const QVector<int> &axisVec,QWidget *parent = nullptr);
    void setParameter(const QMap<int,int> &posMap);
    bool saveParameter();
signals:

public slots:
    void onSaveBtnCliked();
private:
    QVector<QSpinBox*> m_spinBoxVec;
    QHBoxLayout *hbox;
     QLabel *m_paxisId;
     QPushButton *m_pSaveBtn;
     QString m_pointName;
     QString axisId2axisName(const int &id);

};

#endif // POSITIONFROM_H
