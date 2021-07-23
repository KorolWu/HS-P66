#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "cpiewidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:
private:
    int m_width;
    int m_height;
    QLabel *m_camerLab;
    QWidget *parent;
    CPieWidget *m_perrwidget;
        QList<QColor> m_colorlist;
    void initUI();
    void SetErrwidgetInfo();
    void initCheckInfoUI();
public slots:
};

#endif // MAINWIDGET_H
