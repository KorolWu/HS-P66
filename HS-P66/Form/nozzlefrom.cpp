#include "nozzlefrom.h"
#pragma execution_character_set("utf-8")
///
/// \brief NozzleFrom::NozzleFrom 喷嘴设置界面
/// \param parent
///
NozzleFrom::NozzleFrom(QWidget *parent) : QWidget(parent)
{
    this->resize(parent->width()-5,parent->height()-5);
    //this->setStyleSheet("background-color:grb(102,139,139)");
    m_width = parent->width();
    m_height = parent->height();
    initUi();
}

void NozzleFrom::initUi()
{
    m_pDpiSetGroubox = new QGroupBox(this);
    m_pDpiSetGroubox->setFixedSize(m_width*0.8,m_height*0.15);
    QString stylesheet = "QLabel{font: 18px; Max-width:90px;}QPushButton{Max-width:90px;;Min-width:85px;Min-height:35px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Max-width:90px;Min-height:25px;border-radius:5px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Max-width:90px;Min-height:25px;border-radius:5px;}QLineEdit{border: 2px solid white;border-radius:8px;margin-top:6px;Max-height:125px;Max-width:360px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 22px;}";
    m_pDpiSetGroubox->setStyleSheet(stylesheet);

    m_pDpiSetGroubox->setTitle("DPI设置");
    QHBoxLayout *h = new QHBoxLayout();
    QLabel *e = new QLabel("精度倍数",m_pDpiSetGroubox);
    h->addWidget(e);
    h->addStretch(1);
    m_pDpiTimes = new QSpinBox(m_pDpiSetGroubox);
    m_pDpiTimes->setRange(0,10);
    h->addWidget(m_pDpiTimes);
    h->addStretch(1);
    m_pDpiSetBtn = new QPushButton("设置",m_pDpiSetGroubox);
    connect(m_pDpiSetBtn,&QPushButton::clicked,this,&NozzleFrom::onDpiSetBtnClicked);
    h->addWidget(m_pDpiSetBtn);
    h->addStretch(8);
    h->addStretch();
    m_pDpiSetGroubox->setLayout(h);


    m_pNozzleGroubox = new QGroupBox("喷头设置",this);
    m_pNozzleGroubox->setFixedSize(m_width*0.8,m_height*0.25);
    m_pNozzleGroubox->setStyleSheet(stylesheet);

    QLabel *start = new QLabel("起始位置 ",m_pNozzleGroubox);
    m_pStartP = new QSpinBox(m_pNozzleGroubox);
    m_pStartP->setRange(0,2000);
    QLabel *end = new QLabel("终止位置 ",m_pNozzleGroubox);
    m_pEndP = new QSpinBox(m_pNozzleGroubox);
    m_pEndP->setRange(0,2000);
    m_pPSetBtn = new QPushButton("设置",m_pNozzleGroubox);
    connect(m_pPSetBtn,&QPushButton::clicked,this,&NozzleFrom::onSetBtnClicked);
    QHBoxLayout *pHbox = new QHBoxLayout();
    m_pVbox = new QVBoxLayout();
    pHbox->addWidget(start);
    pHbox->addStretch(1);
    pHbox->addWidget(m_pStartP);
    pHbox->addStretch(1);
    pHbox->addWidget(end);
    pHbox->addStretch(1);
    pHbox->addWidget(m_pEndP);
    pHbox->addStretch(1);
    pHbox->addWidget(m_pPSetBtn);
    pHbox->addStretch(6);
    m_pVbox->addLayout(pHbox);
    pHbox = new QHBoxLayout();
    QLabel *filePath = new QLabel("图形地址:",m_pNozzleGroubox);
    m_pFilePath = new QLineEdit(m_pNozzleGroubox);
    m_pfilePathSetBtn = new QPushButton("设置",m_pNozzleGroubox);
    m_pfilePathSetBtn->setObjectName("imageFile");
     connect(m_pfilePathSetBtn,&QPushButton::clicked,this,&NozzleFrom::onFileBtnClicked);
    pHbox->addWidget(filePath);
    pHbox->addWidget(m_pFilePath);
    pHbox->addWidget(m_pfilePathSetBtn);
    m_pVbox->addLayout(pHbox);
    QLabel *wavePath = new QLabel("波形地址:",m_pNozzleGroubox);
    m_pWavePath = new QLineEdit(m_pNozzleGroubox);
    m_pWavePathSetBtn = new QPushButton("设置",m_pNozzleGroubox);
    m_pWavePathSetBtn->setObjectName("wavePath");
     connect(m_pWavePathSetBtn,&QPushButton::clicked,this,&NozzleFrom::onFileBtnClicked);
    pHbox->addWidget(wavePath);
    pHbox->addWidget(m_pWavePath);
    pHbox->addWidget(m_pWavePathSetBtn);
    m_pVbox->addLayout(pHbox);
    m_pNozzleGroubox->setLayout(m_pVbox);

    m_pNozzleSetGroubox = new QGroupBox("闪喷设置",this);
    m_pNozzleSetGroubox->setFixedSize(m_width*0.8,m_height*0.15);
    m_pNozzleSetGroubox->setStyleSheet(stylesheet);

    pHbox = new QHBoxLayout();
    for (int i = 0;i < 3 ;i++) {
        m_pCheckBox[i] = new QRadioButton(m_pNozzleSetGroubox);
        pHbox->addWidget(m_pCheckBox[i]);
    }
    m_pCheckBox[0]->setText("单次闪喷");
    m_pCheckBox[1]->setText("持续闪喷");
    m_pCheckBox[2]->setText("连续闪喷");
    m_pCycle = new QSpinBox(m_pNozzleSetGroubox);
    m_pCycle->setRange(0,2000);
    pHbox->addWidget(m_pCycle);
    m_pFlashJetSet = new QPushButton("设置",m_pNozzleSetGroubox);
    connect(m_pFlashJetSet,&QPushButton::clicked,this,&NozzleFrom::onFlashJetSetClicked);
    pHbox->addWidget(m_pFlashJetSet);
    m_pNozzleSetGroubox->setLayout(pHbox);


    vbox = new QVBoxLayout();
    vbox->addWidget(m_pDpiSetGroubox);
    vbox->addWidget(m_pNozzleGroubox);
    vbox->addWidget(m_pNozzleSetGroubox);
    vbox->addStretch();
    this->setLayout(vbox);

}

///
/// \brief NozzleFrom::updateNozzleParameter 将喷头的参数全部写入数据库
/// \return
///
bool NozzleFrom::updateNozzleParameter()
{
    QStringList names,values;
    names<<"dpitimes"<<"startPin"<<"endPin"<<"imagePath"<<"wavePath"<<"flashStatus"<<"cycle";
    values<<QString::number(m_pDpiTimes->value())<<QString::number(m_pStartP->value())<<QString::number(m_pEndP->value())<<m_pFilePath->text()<<m_pWavePath->text()<<QString::number(m_flashStatus)<<QString::number(m_pCycle->value());
    QString expression =  QString("nozzleName = 'frist'");
   return DataBaseManager::GetInstance()->ExcUpdateDb("t_nozzle",names,values,expression);
}

///
/// \brief NozzleFrom::onSetBtnClicked 设置喷头的起始位置和终止位置
///
void NozzleFrom::onSetBtnClicked()
{
    int startPin = m_pStartP->value();
    int endPin = m_pEndP->value();

    ShareData::GetInstance()->m_nozzleStu.startP = startPin;
    ShareData::GetInstance()->m_nozzleStu.endP = endPin;
    if(updateNozzleParameter() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("保存失败");
        msgBox.exec();
    }
}

///
/// \brief NozzleFrom::onDpiSetBtnClicked 设置图形dpi与喷孔npi之间的倍数关系
///
void NozzleFrom::onDpiSetBtnClicked()
{
    int times = m_pDpiTimes->value();
    ShareData::GetInstance()->m_nozzleStu.dpiTimes = times;
    if(updateNozzleParameter() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("保存失败");
        msgBox.exec();
    }
}

///
/// \brief NozzleFrom::onFileBtnClicked 打开文件获取文件地址
///
void NozzleFrom::onFileBtnClicked()
{
    QString objName = sender()->objectName();
    QString fileName;
    if(objName == "imageFile")
    {
       fileName = QFileDialog::getOpenFileName(this,tr("选择打印图片"), " ",tr("图片文件(*.jpg)"));
       m_pFilePath->setText(fileName);
       ShareData::GetInstance()->m_nozzleStu.filePath = fileName;
    }
    else
    {
        fileName = QFileDialog::getOpenFileName(this,tr("选择波形文件"), " ",tr("图片文件(*.txt)"));
        m_pWavePath->setText(fileName);
        ShareData::GetInstance()->m_nozzleStu.WavePath = fileName;
    }
    if(updateNozzleParameter() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("保存失败");
        msgBox.exec();
    }
}

///
/// \brief NozzleFrom::onFlashJetSetClicked 闪喷设置
///
void NozzleFrom::onFlashJetSetClicked()
{
    int c = 3;
    int cycle = m_pCycle->value();
    for (int i = 0;i < 3 ;i++) {
        if(m_pCheckBox[i]->isChecked())
        {
            c = i;
            m_flashStatus = i;
            break;
        }
    }
    if(c == 3)
        return;
    //保存到内存
    ShareData::GetInstance()->m_nozzleStu.flashJetStatus = c;
    ShareData::GetInstance()->m_nozzleStu.cycle = cycle;
    switch (c)
    {
    case 0:
        //单次
        break;
    case 1:
        //连续
        break;
    case 2:
        //持续
        break;
    default:
        return;
    }
    if(updateNozzleParameter() == false)
    {
        QMessageBox msgBox;
        msgBox.setText("保存失败");
        msgBox.exec();
    }
}

///
/// \brief NozzleFrom::setParameter 设置此窗体的参数
/// \param nozzleStruct
///
void NozzleFrom::setParameter(NozzleStu nozzleStruct)
{
    m_pDpiTimes->setValue(nozzleStruct.dpiTimes);
    m_pStartP->setValue(nozzleStruct.startP);
    m_pEndP->setValue(nozzleStruct.endP);
    m_pFilePath->setText(nozzleStruct.filePath);
    m_pWavePath->setText(nozzleStruct.WavePath);
    m_pCycle->setValue(nozzleStruct.cycle);
    switch (nozzleStruct.flashJetStatus) {
    case 0:
        m_pCheckBox[0]->setChecked(true); //单次
        break;
    case 1:
        m_pCheckBox[1]->setChecked(true);//连续
        break;
    case 2:
        m_pCheckBox[2]->setChecked(true);//持续
        break;
    default:
        return;
    }

}
