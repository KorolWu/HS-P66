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
   // ShareData::GetInstance()->m_stopFlag = false; //急停标志位 复位掉(急停后要回原点，应该在回原点的地方复位急停信号)
    if(status == "启动")
    {
        //执行启动逻辑
        m_start->setIcon(QIcon(":/src/Image/star2stop.png"));
        m_start->setText("停止");
        //开始前判断是否是起始位
        if(ShareData::GetInstance()->m_isHomePosition)
        {
            ShareData::GetInstance()->m_isRuning = true;
            QString errMsg = "NoErr";
            if(false == logical(errMsg))
            {
                  QLOG_INFO()<<errMsg;
                  m_start->setIcon(QIcon(":/src/Image/start"));
                  m_start->setText("启动");
                  ShareData::GetInstance()->m_isRuning = false;
                  return;
             }
        }
        else
        {
            QLOG_ERROR()<<"不在初始位置，请先回原点";
        }
        m_start->setIcon(QIcon(":/src/Image/start"));
        m_start->setText("启动");
        ShareData::GetInstance()->m_isRuning = false;
    }
    else
    {
        //执行停止逻辑
        emgStop();
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
        //getIniParameter(axisId);

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
       qDebug()<<"ABCDEF"<<visionStruct.A<<visionStruct.B<<visionStruct.C<<visionStruct.D<<visionStruct.E<<visionStruct.F;
   }
  //qDebug()<<ShareData::GetInstance()->m_position;

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
    Q_UNUSED(axisId)
    //m_ini.Config();
//    QString node = QString("Axis%1").arg(axisId);
//    AxisStruct axisInfo;
//    axisInfo.vMax = m_ini.Get(node,"vMax").toInt();
//    axisInfo.acc = m_ini.Get(node,"Acc").toInt();
//    axisInfo.dcc = m_ini.Get(node,"Dcc").toInt();
//    axisInfo.homeVmax = m_ini.Get(node,"HomeVmax").toInt();
//    if(ShareData::GetInstance()->m_axisMap.contains(axisId))
//        ShareData::GetInstance()->m_axisMap[axisId] = axisInfo;
//    else
//        ShareData::GetInstance()->m_axisMap.insert(axisId,axisInfo);
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
    m_pMainWidget->hide();

}

void MainWindow::initMainUI()
{
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect = screen->availableVirtualGeometry();
    ShareData::GetInstance()->m_width = 1900;//screenRect.width()-2;
    ShareData::GetInstance()->m_heitht = 968;// screenRect.height()-40;
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
    m_MainWidget->resize(ShareData::GetInstance()->m_width/6*5+25-200,ShareData::GetInstance()->m_heitht-10);
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

    m_pMainWidget = new MainWidget(m_MainWidget);

}

void MainWindow::initLWidget()
{
    p_treeView = new QTreeView(m_LWidget);
    p_treeView->setStyleSheet("QTreeView{border: 1px solid lightgray;background-color:rgb(245,245,240)}"
                              "QTreeView::item {height: 40px;border-radius: 2px;border: 1px solid transparent;background: transparent;color: black;}"
                              "QTreeView::item:has-children {border: none;border-bottom: 1px solid lightgray;}"
                              "QTreeView::item:hover {border: 1px solid rgb(170, 190, 230);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                              "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                              "QTreeView::item:selected {border: 1px solid rgb(230, 240, 250);background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(230, 240, 250),"
                              "stop: 0.5 rgb(220, 235, 255), stop: 1.0 rgb(210, 230, 255));}"
                              );
    p_treeView->header()->hide();
    connect(p_treeView,&QTreeView::clicked,this,&MainWindow::onTreeviewClicked);
    p_treeView->setFixedSize(ShareData::GetInstance()->m_width/7,ShareData::GetInstance()->m_heitht);
    p_treeStandarModel = new QStandardItemModel(p_treeView);
    p_treeView->setModel(p_treeStandarModel);
    p_treeView->setFont(QFont("宋体",14));
    //p_treeView->header()->hide();
    p_treeView->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    p_standarItem = new QStandardItem("运动控制");
    p_standarItem->setIcon(QIcon(":/src/Image/move.png"));
    p_ordersItem = new QStandardItem("参数设置");
    p_ordersItem->setIcon(QIcon(":/src/Image/seting.png"));
    p_loginroleItem = new  QStandardItem("IO监视");
    p_loginroleItem->setIcon(QIcon(":/src/Image/ioCheck.png"));
    p_singlAxisControl = new QStandardItem("单轴运动");
    p_singlAxisControl->setIcon(QIcon(":/src/Image/axisCheck.png"));
    p_xxyItem = new QStandardItem("XXY载台");
        p_xxyItem->setIcon(QIcon(":/src/Image/xxy.png"));
    p_positionItem = new QStandardItem("点位管理");
    p_positionItem->setIcon(QIcon(":/src/Image/position.png"));
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
    p_elevator->setIcon(QIcon(":/src/Image/camera.png"));
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
        setChildrenBtnEnable(p_axisCheck);
        p_axisCheck->show();
    }
    else if(row_name == "IO监视")
    {
         setChildrenBtnEnable(p_ioForm);
       p_ioForm->show();
    }
    else if(row_name == "参数设置")
    {
        setChildrenBtnEnable(p_parameter);
        p_parameter->show();
    }
    else if (row_name == "CCD_1")
    {
        setChildrenBtnEnable(p_visionForm);
        p_visionForm->show();
    }
    else if (row_name == "XXY载台")
    {
        setChildrenBtnEnable(p_xxy);
        p_xxy->show();
    }
    else if (row_name == "点位管理")
    {
        setChildrenBtnEnable(p_positionManager);
        p_positionManager->show();
    }
    else if (row_name == "喷头管理")
    {
        setChildrenBtnEnable(m_pNozzle);
        m_pNozzle->show();
    }
    else if(row_name == "运动控制")
    {
        m_pMainWidget->show();
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

bool MainWindow::airInit()
{
    MotionControl m;
    if(m.airActionOff(1,10,20)) //上升气缸原点
    {
        if(m.airActionOff(1,11,16)) //拍边原点
        {
            if(m.airActionOn(1,13,18))//阻挡动点
            {
                m.outPutDo(0,14,0); //平台破真空
                return true;
            }
            else
            {
                qDebug()<<13;
                return false;
            }

        }
        else
        {
            qDebug()<<11;
            return false;
        }

    }
    else
        return false;
}



bool MainWindow::runPosition(const QString &positionName)
{
    MotionControl m;
    QMap<int,int> pos;
    pos.clear();
    if(ShareData::GetInstance()->m_position.contains(positionName))
    {
        pos.clear();
        pos = ShareData::GetInstance()->m_position[positionName];
        if(!m.runPosition(pos))
        {
            QLOG_INFO()<<"位置:"<<positionName<<":移动中失败";
            return false;
        }
        else
            return true;
    }
    return false;
}

bool MainWindow::logical(QString &msg)
{
    m_logical.beginIn(1);//流道进料
    if(false == m_logical.runPosition("Zdown"))
    {
        msg = "流道放料到载台失败";
        return false;
    }
     m_logical.airVoid(true); //平台吸气
     if(false == m_logical.airAction())
     {
         msg = "拍边气缸固定流程执行失败";
         return false;
     }
     //去一个固定的拍照位置  这里先省略

     //拍照算出此时玻璃角点的位置，以及角度
     QPoint coner;double angle;QString errmsg;
     QMap<double,double> cornerPosition;//角点相对于xxy平台的坐标
     if(p_visionForm->m_pVision_R->trigger(coner,angle,errmsg,cornerPosition))
     {
           if(false == m_logical.runOffect(cornerPosition))
           {
                QLOG_INFO()<<"拍照补偿大于 1CM";
           }
     }
     else
     {
          msg = "拍照定位失败";
          QLOG_INFO()<<msg;
     }

    if(false == m_logical.getGlass())
    {
        msg = "玻璃刚到载台时流程执行失败";
        return false;
    }
    if(false == m_logical.printFlow())
    {
        msg = "喷头打印过程中发生错误";
        return false;
    }
    delay_msc(500);
    if(false == m_logical.glassBack())
    {
        msg = "打印出料时发生错误";
        return false;
    }
    m_logical.airVoid(false);//破真空
    if(false == m_logical.runPosition("Zup"))
    {
        msg = "将物料从载台升到流道时发生错误";
        return false;
    }
    if(false == m_logical.airOn(1,13,18))
    {
        msg = "挡料气缸复位异常";
        return false;
    }
     m_logical.beginIn(0);//流道进料
      QLOG_INFO()<<"打印完成";
    return true;

}

void MainWindow::delay_msc(int msc)
{
    QEventLoop loop;
    QTimer::singleShot(msc,&loop,SLOT(quit()));
    loop.exec();
}

void MainWindow::enableChildrenBtn(QWidget *child,const bool enable)
{
    if(child != nullptr)
    {
        QList<QPushButton*> btnList = child->findChildren<QPushButton*>();
        foreach(QPushButton *b,btnList)
        {
            b->setEnabled(enable);
        }
    }
}

void MainWindow::setChildrenBtnEnable(QWidget *widget)
{
    if(ShareData::GetInstance()->m_isRuning)
        enableChildrenBtn(widget,false);
    else
        enableChildrenBtn(widget,true);
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
    ShareData::GetInstance()->m_stopFlag = false; //急停标志位 复位掉
     m_home->setEnabled(false);
    //需要判断里面时候有料，如果有料不可以启动回原点流程
    QLOG_INFO()<<"回原点中，请稍后...";
    MotionControl control;
    QVector<int> axisVec;
    axisVec.append(16);//进料z
    //axisVec.append(20);//进料x
//    axisVec.append(6);//外侧相机
//    axisVec.append(7);//内侧相机
    axisVec.append(15);//喷头z
    axisVec.append(1);//上载台x
    axisVec.append(2);//上载台x
    axisVec.append(3);//上载台y
    if(control.goHomes(axisVec))
    {
//        QMap<int,int> pos;
//        pos.insert(1,6000);
//        pos.insert(2,-6000);
//        if(control.runPosition(pos))
//           QLOG_INFO()<<"回原点第一段成功";
//        else
//        {
//            QLOG_INFO()<<"回原点第一段失败";
//            return;
//        }
    }
    else
    {
        QLOG_INFO()<<"回原点第一段失败";
         m_home->setEnabled(true);
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
        m_home->setEnabled(true);
        return;
    }
    if(false == airInit())
    {
       QLOG_INFO()<<"气缸复位失败";
       m_home->setEnabled(true);
       return;
    }
    if(false == runPosition("Zup"))
    {
        QLOG_INFO()<<"进料z上升失败";
        m_home->setEnabled(true);
        return;
    }
    ShareData::GetInstance()->m_isHomePosition = true;
    m_home->setEnabled(false);
     QLOG_INFO()<<"回原点完成。";
}

void MainWindow::emgStop()
{
    ShareData::GetInstance()->m_stopFlag = true;//所有轴停止标志位
    ShareData::GetInstance()->m_isHomePosition = false;//已经不在原点了，需要从新回原点才能再次启动
    MotionControl control;
    QVector<int> axisVec;
    axisVec<<0<<1<<2<<3<<14<<15<<16<<18<<19;
    control.axisStop_v(axisVec);
    m_home->setEnabled(true);//回原点可见

}

