#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QLabel>
#include <QScreen>
#include <QWidget>
#include <QTreeView>
#include <QTreeWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QDateTime>
#include "sharedata.h"
#include "Form/axisinfoui.h"
#include "Form/ioform.h"
#include "Form/axischeck.h"
#include "Form/visionfrom.h"
#include "Form/parameterfrom.h"
#include "ADLINK/APS168.h"
#include "ADLINK/type_def.h"
#include "ADLINK/APS_Define.h"
#include "ADLINK/ErrorCodeDef.h"
#include <Form/iomonitor.h>
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

public slots:
    void start();
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
    QStandardItem *p_singlAxisControl;
    QStandardItem *p_elevator;
    QStandardItem *p_runer;
    IoForm *p_ioForm;
    AxisCheck *p_axisCheck;
    VisionFrom *p_visionForm;
    ParameterFrom *p_parameter;
    QTextEdit *m_pLogText;
     MyIniConfig m_ini;
    void initParameter();
    void getIniParameter(const int axisId);
    void childrenFormHide();
    void initMainUI();
    void initLWidget();
    void onTreeviewClicked(const QModelIndex &index);
    int initAdlinkDriver(const QString &fileName);
    void appendLog(const QString log);
};
#endif // MAINWINDOW_H
