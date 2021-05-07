#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    ShareData::GetInstance()->m_width = screenRect.width()-2;
    ShareData::GetInstance()->m_heitht = screenRect.height();
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
    m_LWidget->setStyleSheet("background-color:gray");

    m_start = new QPushButton("start",this);
    m_start->resize(ShareData::GetInstance()->m_width/15,ShareData::GetInstance()->m_heitht/12);
    m_start->move(ShareData::GetInstance()->m_width/10*9,10);

    m_reset = new QPushButton("rest",this);
    m_reset->resize(ShareData::GetInstance()->m_width/15,ShareData::GetInstance()->m_heitht/12);
    m_reset->move(ShareData::GetInstance()->m_width/10*8,10);

    m_emg = new QPushButton("emg",this);
    m_emg->resize(ShareData::GetInstance()->m_width/15,ShareData::GetInstance()->m_heitht/12);
    m_emg->move(ShareData::GetInstance()->m_width/10*7,10);

    m_MainWidget = new QWidget(this);
    m_MainWidget->move(ShareData::GetInstance()->m_width/7+3,ShareData::GetInstance()->m_heitht/10);
    m_MainWidget->resize(ShareData::GetInstance()->m_width/6*5-3,ShareData::GetInstance()->m_heitht);
    m_MainWidget->setStyleSheet("background-color:rgb(244,244,244)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

