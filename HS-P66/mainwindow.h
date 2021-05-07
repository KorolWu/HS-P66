#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QLabel>
#include <QScreen>
#include <QWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QMainWindow>
#include "sharedata.h"
#include "Form/axisinfoui.h"
#include <QStandardItemModel>
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
    QLabel *m_hsLog;
    QWidget *m_LWidget;
    QPushButton *m_emg;
    QTreeView* p_treeView;
    QStandardItemModel* p_treeStandarModel;
    QLabel *m_hsLogTest;
    QPushButton *m_start;
    QPushButton *m_reset;
    QPushButton *m_home;
    QWidget *m_MainWidget;
    QStandardItem *p_standarItem;
    QStandardItem *p_ordersItem;
    QStandardItem *p_agvItem;
    QStandardItem *p_loginroleItem;
    QStandardItem *p_elevator;
    QStandardItem *p_runer;
    void initMainUI();
    void initLWidget();
    void onTreeviewClicked(const QModelIndex &index);
};
#endif // MAINWINDOW_H
