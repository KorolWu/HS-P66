#ifndef XXYFORM_H
#define XXYFORM_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "Units/XXYConverter.h"

///
/// \brief The XXYForm class
/// 上载台xxy的操作页面，通过三轴的联动实现载台的前后左右和旋转
class XXYForm : public QWidget
{
public:
    XXYForm(QWidget *parent = nullptr);
private:
    QSpinBox *m_pAngle;
    QSpinBox *m_pDistance;
    QPushButton *m_btn[6];
    QSpinBox *m_pX1;
    QSpinBox *m_pX2;
    QSpinBox *m_pY1;
    QSpinBox *m_pA;
    QVBoxLayout *m_pVbox;
    void initUi();
private slots:
    void onBtnClicked();

};

#endif // XXYFORM_H
