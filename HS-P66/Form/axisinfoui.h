#ifndef AXISINFOUI_H
#define AXISINFOUI_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "pushbutton.h"
#include <QLineEdit>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QTimer>

class AxisInfoUI : public QWidget
{
    Q_OBJECT
public:
    explicit AxisInfoUI(QWidget *parent = 0);
public:
    void SetAxisName(const QString strName);
    void SetAxisRanage(const double dstart,const double dend);
    QString GetAxisName();
    double GetTraPos();
    void SetTraPos(double d);
    uint  GetTraSpeed();
    void TimerStatus(bool isStop);
private:
    QFont font;
    QLabel *lable[3];
    PushButton *btn[8];
    QComboBox *cbb;
    QDoubleSpinBox *dsb;
    QVBoxLayout *vBox;
    QHBoxLayout *hBox[3];
    QLineEdit   *curPos;
    int m_bytePos;
    int m_stausBytePos;
    QString m_axisName;
    QTimer *timer;

private:
    void CreatAsixUI();
signals:

public slots:
    void RunORG();
    void RunSon();
    void RunReSet();
    void RunLeft();
    void RunRight();
    void RunQuickFixPos();
    void RunStop();
    void timerUpInputData();
};

#endif // AXISINFOUI_H
