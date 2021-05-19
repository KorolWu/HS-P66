#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initParameter();
    initMainUI();
    initLWidget();
    QString fileName = "E:\\HS-P66\\ADLINK\\ADLINKBoard.xml";
    ShareData::GetInstance()->m_DriverIsInitialization  = initAdlinkDriver(fileName);
    ShareData::GetInstance()->m_DriverIsInitialization ? appendLog("板卡初始化成功") : appendLog("板卡初始化失败！");

}

MainWindow::~MainWindow()
{
    APS_close(); //关闭系统中所有的板卡
    delete ui;
}

void MainWindow::start()
{
//    MotionControl control;
//    control.testTimeOut(2000);
}
///
/// \brief MainWindow::initParameter
/// 从ini 文件里面读取各轴的速度参数
///
void MainWindow::initParameter()
{
    for (int i = 0;i < 18; i++ ) {
        int axisId = 0;
        if(i >7)
            axisId = i + 6;
        else
            axisId = i;
        getIniParameter(axisId);

    }
    qDebug()<<ShareData::GetInstance()->m_axisMap.size();
}

void MainWindow::getIniParameter(const int axisId)
{
    m_ini.Config();
    QString node = QString("Axis%1").arg(axisId);
    AxisStruct axisInfo;
    axisInfo.vMax = m_ini.Get(node,"vMax").toInt();
    axisInfo.acc = m_ini.Get(node,"Acc").toInt();
    axisInfo.dcc = m_ini.Get(node,"Dcc").toInt();
    axisInfo.homeVmax = m_ini.Get(node,"HomeVmax").toInt();
    if(ShareData::GetInstance()->m_axisMap.contains(axisId))
        ShareData::GetInstance()->m_axisMap[axisId] = axisInfo;
    else
        ShareData::GetInstance()->m_axisMap.insert(axisId,axisInfo);
}

void MainWindow::childrenFormHide()
{
    p_ioForm->hide();
    p_axisCheck->hide();
    p_visionForm->hide();
    p_parameter->hide();

}

void MainWindow::initMainUI()
{
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    ShareData::GetInstance()->m_width = screenRect.width()-2;
    ShareData::GetInstance()->m_heitht = screenRect.height()-40;
    this->resize(ShareData::GetInstance()->m_width,ShareData::GetInstance()->m_heitht);
    this->setWindowTitle("HS_P66");
    m_hsLog = new QLabel(this);
    m_hsLog->resize(ShareData::GetInstance()->m_width/6,ShareData::GetInstance()->m_heitht/10 -2);
    m_hsLogTest = new QLabel(this);
    m_hsLogTest->setText("HS-P66");
    m_hsLogTest->setMinimumWidth(200);
    m_hsLogTest->move(ShareData::GetInstance()->m_width/6-40,70);
    m_hsLogTest->setStyleSheet("font:Times;font-size:40px; color: rgb(135, 206, 250);");
    QPixmap pix = QPixmap(":/src/Image/hs.png");
    pix.scaled(QSize(ShareData::GetInstance()->m_width/6,ShareData::GetInstance()->m_heitht/10 -2),Qt::KeepAspectRatio);
    m_hsLog->setPixmap(pix);
    m_LWidget =new QWidget(this);
    m_LWidget->move(0,ShareData::GetInstance()->m_heitht/10);
    m_LWidget->resize(ShareData::GetInstance()->m_width/7,ShareData::GetInstance()->m_heitht);
    m_LWidget->setStyleSheet("background-color:rgb(205, 205, 180)");

    int offect = 30;
    m_start = new QPushButton("启动",this);
    m_start->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_start->move(ShareData::GetInstance()->m_width/10*9+offect,15);
    m_start->setIcon(QIcon(":/src/Image/start"));
    connect(m_start,&QPushButton::clicked,this,&MainWindow::start);

    m_reset = new QPushButton("复位",this);
    m_reset->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_reset->move(ShareData::GetInstance()->m_width/10*8+offect+80,15);
    m_reset->setIcon(QIcon(":/src/Image/reset_o"));

    m_emg = new QPushButton("急停",this);
    m_emg->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_emg->move(ShareData::GetInstance()->m_width/10*7+offect+160,15);
    m_emg->setIcon(QIcon(":/src/Image/emg"));

    m_home= new QPushButton("原点",this);
    m_home->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_home->move(ShareData::GetInstance()->m_width/10*6+offect+230,15);
    m_home->setIcon(QIcon(":/src/Image/home"));
    this->setStyleSheet("QPushButton{background-color:rgb(190,190,190);border-radius: 5px;font:18px;}"\
                        "QPushButton:hover{background-color:rgb(210,210,210);}"\
                        "QPushButton:pressed{background-color:rgb(160,160,160);}");

    m_MainWidget = new QWidget(this);
    m_MainWidget->move(ShareData::GetInstance()->m_width/7+3,ShareData::GetInstance()->m_heitht/10);
    m_MainWidget->resize(ShareData::GetInstance()->m_width/6*5+25,ShareData::GetInstance()->m_heitht-10);
    m_pLogText = new QTextEdit(m_MainWidget);
    m_pLogText->move(3,m_MainWidget->height()/5*4);
    m_pLogText->resize(m_MainWidget->width()-15,m_MainWidget->height()/5-15);
    m_pLogText->setStyleSheet("font-family:Times; font:17px;background:transparent;border-width: 1px;border-color:rgb(150,150,150); border-style: solid;border-radius:10px;");

   // m_MainWidget->setStyleSheet("background-color:rgb(130,130,130)");

    p_ioForm = new IoForm(m_MainWidget);
    p_ioForm->setObjectName("p_ioForm");
   // p_ioForm->setStyleSheet("#p_ioForm{background-color:rgb(130,130,130)}");
    p_ioForm->hide();

    p_axisCheck = new AxisCheck(m_MainWidget);
    p_axisCheck->hide();

    p_visionForm = new VisionFrom(m_MainWidget);
    p_visionForm->hide();

    p_parameter = new ParameterFrom(m_MainWidget);
    p_parameter->hide();

}

void MainWindow::initLWidget()
{
    p_treeView = new QTreeView(m_LWidget);
    p_treeView->setStyleSheet("QTreeView{border: 1px solid lightgray;}"
                              "QTreeView::item {height: 40px;border-radius: 2px;border: 1px solid transparent;background: transparent;color: black;}"
                              "QTreeView::item:has-children {border: none;border-bottom: 1px solid lightgray;}"
                              "QTreeView::item:hover {border: 1px solid rgb(170, 190, 230);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                              "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                              "QTreeView::item:selected {border: 1px solid rgb(230, 240, 250);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                              "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                              );
    connect(p_treeView,&QTreeView::clicked,this,&MainWindow::onTreeviewClicked);
    p_treeView->setFixedSize(ShareData::GetInstance()->m_width/7,ShareData::GetInstance()->m_heitht);
    p_treeStandarModel = new QStandardItemModel(p_treeView);
    p_treeView->setModel(p_treeStandarModel);
    p_treeView->setFont(QFont("宋体",12));
    //p_treeView->header()->hide();
    p_treeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    p_standarItem = new QStandardItem("运动控制");
    p_standarItem->setIcon(QIcon(":/src/Image/move.png"));
    p_ordersItem = new QStandardItem("参数设置");
    p_ordersItem->setIcon(QIcon(":/src/Image/seting.png"));
    p_loginroleItem = new  QStandardItem("IO监视");

    p_singlAxisControl = new QStandardItem("单轴运动");


    p_standarItem->appendRow(p_ordersItem);
    p_standarItem->appendRow(p_loginroleItem);
    p_standarItem->appendRow(p_singlAxisControl);

    p_treeStandarModel->appendRow(p_standarItem);
    p_standarItem = new QStandardItem("视觉管理");
    p_standarItem->setIcon(QIcon(":/src/Image/vision.png"));
    p_agvItem = new QStandardItem("参数设置");
    p_agvItem->setIcon(QIcon(":/src/Image/seting.png"));
    p_standarItem->appendRow(p_agvItem);
    p_elevator = new QStandardItem("CCD_1");
    p_elevator->setIcon(QIcon(":/resouse/Image/elevator.png"));
    p_standarItem->appendRow(p_elevator);
    p_runer = new QStandardItem("CCD_2");
    p_runer->setIcon(QIcon(":/resouse/Image/elevator.png"));
    p_standarItem->appendRow(p_runer);
    p_treeStandarModel->appendRow(p_standarItem);

    p_standarItem = new QStandardItem("日志管理");
    p_standarItem->setIcon(QIcon(":/src/Image/log.png"));
    p_treeStandarModel->appendRow(p_standarItem);
}

void MainWindow::onTreeviewClicked(const QModelIndex &index)
{
    childrenFormHide();
    QString row_name = index.data().toString();
    if(row_name == "单轴运动")
    {
        //qDebug()<<"handle 权限管理...";
        p_axisCheck->show();
    }
    else if(row_name == "IO监视")
    {
       p_ioForm->show();
    }
    else if(row_name == "参数设置")
    {
        p_parameter->show();
    }
    else if (row_name == "CCD_1")
    {
        p_visionForm->show();
    }
}

int MainWindow::initAdlinkDriver(const QString &fileName)
{
    MotionControl control;
    int initResult = control.initBoard();
    qDebug()<<"init reuslt "<<initResult;
    if(initResult != 1)
        return -1;
    return control.loadBoardParameter(fileName);
}

void MainWindow::appendLog(const QString log)
{
    m_pLogText->append(QString(">%1  :"+log).arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
}

