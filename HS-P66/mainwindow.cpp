#include "mainwindow.h"
#include "ui_mainwindow.h"
#pragma execution_character_set("utf-8")
using namespace QsLogging;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //程序当前运行目录
    m_path = QCoreApplication::applicationDirPath();
   // initParameter();
    initSqlite();
    initMainUI();
    initLogInstance();
    initLWidget();
    QString fileName = "E:\\HS-P66\\ADLINK\\ADLINKBoard.xml";
    ShareData::GetInstance()->m_DriverIsInitialization  = initAdlinkDriver(fileName);
    QLOG_INFO() << "The program starts normally";
    if(ShareData::GetInstance()->m_DriverIsInitialization)
    {
        QLOG_INFO() << "板卡初始化成功";
    }
    else
        QLOG_ERROR()<<"板卡初始化失败！";
    QLOG_INFO()<<m_path;
}

MainWindow::~MainWindow()
{
    APS_close(); //关闭系统中所有的板卡
    delete ui;
}

void MainWindow::start()
{
    QString status = m_start->text();
    if(status == "启动")
    {
        //执行启动逻辑
        m_start->setIcon(QIcon(":/src/Image/star2stop.png"));
        m_start->setText("停止");
        //开始前判断是否是起始位
        if(ShareData::GetInstance()->m_isHomePosition)
        {
            //启动第一节流道和第二节 正向旋转
            beginIn(1);
            //直到载台末端感应到了，停止两个流道
            if(getGlass())
            {
               QLOG_INFO()<<"到达打印位置";
            }
            else
                QLOG_INFO()<<"到达打印位置途中失败";

            //载台气缸下压固定住物料
            //拍照得到补偿值
            //判断补偿值的可靠性，并作出响应

            //去打印位置
            //喷头到打印位置
            //p_visionForm->m_pVision_R->onTrigger();
            //开始打印
           if(printFlow())
           {
               QLOG_INFO()<<"打印完成";
           }
           delay_msc(500);
           QMap<int,int> p;
           MotionControl m;
           p.insert(0,0);
           m.runPosition(p);
           beginIn(0);
    //        MotionControl control;
    //        QMap<int,int> position;
    //        QMap<int,int> position1;
    //        position.insert(18,0);
    //        position.insert(19,0);
    //        position.insert(20,0);

    //        position1.insert(18,-20000);
    //        position1.insert(19,15000);
    //        position1.insert(20,1181);
    //        bool flag = true;
    //        for(int i = 0; i < 25; i++)
    //        {
    //            if(flag)
    //            {
    //                control.runPosition(position);
    //            }
    //            else
    //                control.runPosition(position1);
    //            flag = !flag;
    //        }
        }
        else
        {
            QLOG_ERROR()<<"不在初始位置，请先回原点";
        }
        m_start->setIcon(QIcon(":/src/Image/start"));
        m_start->setText("启动");
    }
    else
    {
        //执行停止逻辑
        m_start->setIcon(QIcon(":/src/Image/start"));
        m_start->setText("启动");
    }

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
    if(ShareData::GetInstance()->m_axisMap.size() != 18)
    {
        QLOG_ERROR()<<"读取配置文件失败，请检查文件是否存在或完整";
    }
}

bool MainWindow::initSqlite()
{
  bool result =  DataBaseManager::GetInstance()->OpenDb(m_path+"\\"+"position.db");
  QStringList names;
  QStringList values;
  QSqlQuery query = DataBaseManager::GetInstance()->ExcQueryDb("select * from t_axisInfo;");
  int axisId = 99;
  AxisStruct axisStruct;
  while (query.next()) {
     QString axisName = query.value("axis_name").toString();//axisName
     QStringList list = axisName.split("_");
     axisId = list[1].toInt();
     axisStruct.acc = query.value("acc").toInt();
     axisStruct.dcc = query.value("dec").toInt();
     axisStruct.vMax = query.value("v_max").toInt();
     axisStruct.homeVmax = query.value("home_vMax").toInt();
     ShareData::GetInstance()->m_axisMap.insert(axisId,axisStruct);
  }
  query = DataBaseManager::GetInstance()->ExcQueryDb("select * from t_point;");
  while(query.next())
  {
      QString pointName = query.value("point_name").toString();
      QString pointInfo = query.value("point_info").toString();
      QStringList list = pointInfo.split(";");
      QMap<int,int> subPos;
      subPos.clear();
      foreach (QString str, list) {
         QStringList p_list = str.split(":");
          if(p_list.size() == 2)
          {
              subPos.insert(p_list[0].toInt(),p_list[1].toInt());
          }
      }
      ShareData::GetInstance()->m_position.insert(pointName,subPos);
  }
  //读取相机准换信息
   query = DataBaseManager::GetInstance()->ExcQueryDb("select * from t_visionParameter;");
   VisionStu visionStruct;
   while(query.next())
   {
       QString cameraName = query.value("camera_name").toString();
       visionStruct.A = query.value("A").toDouble();
       visionStruct.B = query.value("B").toDouble();
       visionStruct.C = query.value("C").toDouble();
       visionStruct.D = query.value("D").toDouble();
       visionStruct.E = query.value("E").toDouble();
       visionStruct.F = query.value("F").toDouble();
       visionStruct.pix2mm = query.value("pix2mm").toDouble();
       ShareData::GetInstance()->m_visionMap.insert(cameraName,visionStruct);
   }
  qDebug()<<ShareData::GetInstance()->m_position;

  //读取喷头设置信息
  query = DataBaseManager::GetInstance()->ExcQueryDb("select * from t_nozzle;");

  NozzleStu nozzleStruct;
  while(query.next())
  {
       ShareData::GetInstance()->m_nozzleStu.name = query.value("nozzleName").toString();
       ShareData::GetInstance()->m_nozzleStu.dpiTimes = query.value("dpitimes").toInt();
       ShareData::GetInstance()->m_nozzleStu.startP = query.value("startPin").toInt();
       ShareData::GetInstance()->m_nozzleStu.endP = query.value("endPin").toInt();
       ShareData::GetInstance()->m_nozzleStu.filePath = query.value("imagePath").toString();
       ShareData::GetInstance()->m_nozzleStu.WavePath = query.value("wavePath").toString();
       ShareData::GetInstance()->m_nozzleStu.flashJetStatus = query.value("flashStatus").toInt();
       ShareData::GetInstance()->m_nozzleStu.cycle = query.value("cycle").toInt();
  }
   return result;
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
    p_xxy->hide();
    p_positionManager->hide();
    m_pNozzle->hide();

}

void MainWindow::initMainUI()
{
    //QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect(0,0,1800,1000); //=  screen->availableVirtualGeometry();
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
    connect(m_emg,&QPushButton::clicked,this,&MainWindow::emgStop);
    m_emg->resize(ShareData::GetInstance()->m_width/20,ShareData::GetInstance()->m_heitht/17);
    m_emg->move(ShareData::GetInstance()->m_width/10*7+offect+160,15);
    m_emg->setIcon(QIcon(":/src/Image/emg"));

    m_home= new QPushButton("原点",this);
    connect(m_home,&QPushButton::clicked,this,&MainWindow::home);
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
    m_pLogText->move(3,m_MainWidget->height()/5*3+100);
    m_pLogText->resize(m_MainWidget->width()-15,m_MainWidget->height()/5-15);
    m_pLogText->setStyleSheet("font-family:Times; font:17px;background:transparent;border-width: 1px;border-color:rgb(150,150,150); border-style: solid;border-radius:10px;");

    p_positionManager = new PositionManager(m_MainWidget);
    p_positionManager->hide();

    p_ioForm = new IoForm(m_MainWidget);
    p_ioForm->setObjectName("p_ioForm");
   // p_ioForm->setStyleSheet("#p_ioForm{background-color:rgb(130,130,130)}");
    p_ioForm->hide();

    p_axisCheck = new AxisCheck(m_MainWidget);
    p_axisCheck->hide();

    p_visionForm = new VisionUi(m_MainWidget);
    p_visionForm->hide();

    p_parameter = new ParameterFrom(m_MainWidget);
    p_parameter->hide();

    p_xxy = new XXYForm(m_MainWidget);
    p_xxy->hide();

    m_pNozzle = new NozzleFrom(m_MainWidget);
    m_pNozzle->setParameter(ShareData::GetInstance()->m_nozzleStu);
    m_pNozzle->hide();
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
    p_xxyItem = new QStandardItem("XXY载台");
    p_positionItem = new QStandardItem("点位管理");

    p_standarItem->appendRow(p_ordersItem);
    p_standarItem->appendRow(p_loginroleItem);
    p_standarItem->appendRow(p_singlAxisControl);
    p_standarItem->appendRow(p_xxyItem);
    p_standarItem->appendRow(p_positionItem);

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

    p_standarItem = new QStandardItem("喷头管理");
    p_standarItem->setIcon(QIcon(":/src/Image/log.png"));
    p_treeStandarModel->appendRow(p_standarItem);
}

void MainWindow::initLogInstance()
{
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

//  添加文件为目的地
    const QString sLogPath(QDir(QApplication::applicationDirPath()).filePath("log.txt"));
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
                                       sLogPath, EnableLogRotation, MaxSizeBytes(512*1024), MaxOldLogCount(5)));
    logger.addDestination(fileDestination);


    // 添加stdout为目的地
//       DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
//       logger.addDestination(debugDestination);


       //添加到textEdit
       DestinationPtr objectDestination(DestinationFactory::MakeFunctorDestination(this, SLOT(appendLog(QString,int))));
       logger.addDestination(objectDestination);

    // 打印日志
//    QLOG_TRACE() << "1-trace msg";
//    QLOG_DEBUG() << "2-debug msg";
//    QLOG_INFO() << "3-info msg";
//    QLOG_WARN() << "4-warn msg";
//    QLOG_ERROR() << "5-error msg";
     QLOG_ERROR() << "5-error Qlog 日志记录模块启动";

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
    else if (row_name == "XXY载台")
    {
        p_xxy->show();
    }
    else if (row_name == "点位管理")
    {
        p_positionManager->show();
    }
    else if (row_name == "喷头管理")
    {
        m_pNozzle->show();
    }
}

int MainWindow::initAdlinkDriver(const QString &fileName)
{
    MotionControl control;
    int initResult = control.initBoard();
    qDebug()<<"init reuslt "<<initResult;
    if(initResult != 1)
        return 0;
    return control.loadBoardParameter(fileName);
}
///
/// \brief MainWindow::beginIn
/// \return
///
bool MainWindow::beginIn(const int &dir)
{
   MotionControl m;
   m.runJog(18,dir);
   m.runJog(19,dir);
   delay_msc(6000);
   m.stopJog(18);
   m.stopJog(19);
   QLOG_INFO()<<"进料完成";
   return true;
}

bool MainWindow::getGlass()
{
    //等待玻璃到载台上
    MotionControl m;
    m.outPutDo(0,8,1);
    m.outPutDo(0,9,1);
    delay_msc(200);
    m.outPutDo(0,8,0);
    m.outPutDo(0,9,0);
    if(ShareData::GetInstance()->m_position.contains("PointS"))
    {
        QMap<int,int> pos = ShareData::GetInstance()->m_position["PointS"];
       return m.runPosition(pos);
    }
    return false;
}

bool MainWindow::printX()
{
     MotionControl m;
     QMap<int,int> pos;
     pos.clear();
     if(ShareData::GetInstance()->m_position.contains("BeginE"))
     {
         pos.clear();
         pos = ShareData::GetInstance()->m_position["BeginE"];
         if(!m.runPosition(pos))
         {
             QLOG_INFO()<<"print flow failed;";
             return false;
         }
     }
     delay_msc(500);
    if(ShareData::GetInstance()->m_position.contains("BeginS"))
    {
        pos.clear();
       pos = ShareData::GetInstance()->m_position["BeginS"];
       if(!m.runPosition(pos))
       {
           QLOG_INFO()<<"print flow failed;";
           return false;
       }
    }
    return true;
}

bool MainWindow::printFlow()
{
    if(ShareData::GetInstance()->m_position.contains("PointS"))
    {
        if(false == printX())
        {
            QLOG_INFO()<<"打印中出现异常";
            return false;
        }
        delay_msc(800);
        int begin_y = 0;
        QMap<int,int> pos = ShareData::GetInstance()->m_position["PointS"];
        if(pos.contains(0))
        {
           begin_y = pos[0];
           for(int i = 1 ; i < 4; i++)
           {
               begin_y =  begin_y + (i*10000);
               QMap<int,int> p;
               p.clear();
               p.insert(0,begin_y);
                MotionControl m;
                m.runPosition(p);
               delay_msc(800);
               if(false == printX())
               {
                   QLOG_INFO()<<"打印中出现异常";
                   return false;
               }
                delay_msc(800);
           }
        }

    }
    return true;
}

void MainWindow::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}


void MainWindow::appendLog(const QString &message, int level)
{
    m_pLogText->append(message + " " + QString::number(level));
}

///
/// \brief MainWindow::home
///
void MainWindow::home()
{
    //需要判断里面时候有料，如果有料不可以启动回原点流程

    MotionControl control;
    QVector<int> axisVec;
    axisVec.append(16);//进料z
    axisVec.append(20);//进料x
    axisVec.append(6);//外侧相机
    axisVec.append(7);//内侧相机
    axisVec.append(15);//喷头z
    axisVec.append(1);//喷头z 600避让位
    axisVec.append(2);//喷头z -600避让位
    axisVec.append(3);//喷头z
    if(control.goHomes(axisVec))
    {
        QMap<int,int> pos;
        pos.insert(1,6000);
        pos.insert(2,-6000);
        if(control.runPosition(pos))
           QLOG_INFO()<<"回原点第一段成功";
        else
        {
            QLOG_INFO()<<"回原点第一段失败";
            return;
        }
    }
    else
    {
        QLOG_INFO()<<"回原点第一段失败";
        return;
    }
     QVector<int> axisVec2;

     axisVec2.append(14);//喷头x
     axisVec2.append(0);//上载台Y
    if(control.goHomes(axisVec2))
    {
         QLOG_INFO()<<"回原点第二段成功";
    }
    else
    {
        QLOG_INFO()<<"回原点第二段失败";
        return;
    }
    ShareData::GetInstance()->m_isHomePosition = true;
    m_home->setEnabled(false);
}

void MainWindow::emgStop()
{
    MotionControl control;
    QVector<int> axisVec;
    axisVec<<0<<1<<2<<3<<4<<5<<6<<7<<14<<15<<16<<17<<18<<19<<20<<21;
    control.axisStop_v(axisVec);

}

