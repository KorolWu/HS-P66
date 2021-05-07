#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sharedata.h"
#include <QScreen>
#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *m_LWidget;
    QWidget *m_MainWidget;
    QLabel *m_hsLog;
    QLabel *m_hsLogTest;
    QPushButton *m_start;
    QPushButton *m_emg;
    QPushButton *m_reset;
};
#endif // MAINWINDOW_H
