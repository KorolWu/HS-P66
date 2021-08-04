#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "cpiewidget.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

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
    QImage matToQImage(cv::Mat mtx);
public slots:
    void showMark(cv::Mat &src);
};

#endif // MAINWIDGET_H
