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
#include <QDir>
#include "Form/positionmanager.h"
#include "sharedata.h"
#include "Form/axisinfoui.h"
#include "Form/ioform.h"
#include "Form/axischeck.h"
#include "Form/visionui.h"
#include "Form/parameterfrom.h"
#include "Form/nozzlefrom.h"
#include "databasemanager.h"
#include "Form/xxyform.h"
#include "Form/mainwidget.h"
#include "APS168.h"
#include "type_def.h"
#include "APS_Define.h"
#include "ErrorCodeDef.h"
#include "QsLog.h"
#include "QsLogDest.h"
#include "QsLogLevel.h"
#include <Form/iomonitor.h>
#include <QStandardItemModel>
#include <QPushButton>
#include <QGroupBox>
#include <QCoreApplication>
#include "logicalflow.h"

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
    void appendLog(const QString &message, int level);
    void home();
    void emgStop();
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
    QStandardItem *p_xxyItem;
    QStandardItem *p_positionItem;
    IoForm *p_ioForm;
    AxisCheck *p_axisCheck;
    VisionUi *p_visionForm;
    XXYForm *p_xxy;
    PositionManager *p_positionManager;
    ParameterFrom *p_parameter;
    NozzleFrom *m_pNozzle;
    MainWidget *m_pMainWidget;
    QTextEdit *m_pLogText;

     //MyIniConfig m_ini;
     QString m_path;
     LogicalFlow m_logical;
    void initParameter();
    bool initSqlite();
    void getIniParameter(const int axisId);
    void childrenFormHide();
    void initMainUI();
    void initLWidget();
    void initLogInstance();
    void onTreeviewClicked(const QModelIndex &index);
    int initAdlinkDriver(const QString &fileName);
    void delay_msc(int msc);
    void enableChildrenBtn(QWidget *child, const bool enable);
    void setChildrenBtnEnable(QWidget *widget);
    //flow

    bool airInit(); //气缸初始位
    bool runPosition(const QString &positionName); //去一个是示教过的位置

    bool logical(QString &msg);
};
#endif // MAINWINDOW_H
