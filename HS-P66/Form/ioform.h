#ifndef IOFORM_H
#define IOFORM_H

#include <QObject>
#include <QWidget>
#include "iomonitor.h"
#include <QVBoxLayout>

class IoForm : public QWidget
{
public:
    IoForm(QWidget* parent = nullptr);
private:
    QVBoxLayout* m_vbox;
};

#endif // IOFORM_H
