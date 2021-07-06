#include "visionfrom.h"
#pragma execution_character_set("utf-8")
VisionFrom::VisionFrom(QWidget *parent):QWidget(parent)
{
    this->resize(parent->width()/3,parent->height()/5*4);
    m_width = parent->width()/3;
    m_height = parent->height()/5*4;
    initUI();
    //    m_timer = new QTimer(this);
    //    connect(m_timer,&QTimer::timeout,this,&VisionFrom::readFram);


    //test

    qDebug()<<transformation(90.75 , 72.75 );
    qDebug()<<transformation(246.75 , 72.75);
    qDebug()<<transformation(399.75 , 72.75 );
    qDebug()<<transformation(92.25 , 177.75);

    //end test
}

void VisionFrom::setDeviceObj(CameraDevice *obj)
{
    if(obj == nullptr)
        return;
    m_pDevice = obj;
    //获取当前显示的设备处理类对象
    m_pDevice->OpenDevice();
    connect(m_pDevice,&CameraDevice::readReady,this,&VisionFrom::resiveImageData);
    m_matWidth = m_pDevice->width;
    m_matHeight = m_pDevice->height;
    m_pGainEdit->setMaximum(m_pDevice->MaxGain);
    m_pGainEdit->setMinimum(m_pDevice->MinGain);
    m_pExpossureEdit->setMaximum(m_pDevice->MaxExposure);
    m_pExpossureEdit->setMinimum(m_pDevice->MinExposure);
    m_pExpossureEdit->setValue(m_pDevice->CurrentExposure);
    m_pGainEdit->setValue(m_pDevice->CurrentGain);
    qDebug()<<"info"<<m_matWidth<<"-"<<m_matHeight<<"m_width"<<m_width-50;
    int interval = (m_width-50)*0.7505791;
    m_vision_label->resize(m_width-50,interval);

}

void VisionFrom::setGrouboxTitle(QString title)
{
    m_pGroupBox->setTitle(title);
}

void VisionFrom::initUI()
{
    m_pGroupBox = new QGroupBox(this);
    m_pGroupBox->resize(m_width-20,m_height-150);
    m_pGroupBox->move(10,10);
    m_vision_label = new QLabel(m_pGroupBox);
    m_vision_label->resize(m_width-100,m_height/2);
    m_vision_label->move(10,30);
    m_vision_label->setStyleSheet("background-color:rgb(233,233,233)");

    int interval = 70;
    m_openBtn = new QPushButton("开启",m_pGroupBox);
    m_openBtn->resize(60,33);
    m_openBtn->move(320,m_height/2+72+interval);
    m_openBtn->setIcon(QIcon(":/src/Image/start.png"));
    connect(m_openBtn,&QPushButton::clicked,this,&VisionFrom::openCamera);

    m_pTriggerBtn = new QPushButton("单拍",m_pGroupBox);
    m_pTriggerBtn->setIcon(QIcon(":/src/Image/trigger.png"));
    m_pTriggerBtn->resize(60,33);
    m_pTriggerBtn->move(320,m_height/2+130+interval);
    connect(m_pTriggerBtn,&QPushButton::clicked,this,&VisionFrom::onTrigger);

    m_pSaveBtn = new QPushButton("保存",m_pGroupBox);
    m_pSaveBtn->setIcon(QIcon(":/src/Image/save.png"));
    m_pSaveBtn->resize(60,33);
    m_pSaveBtn->move(410,m_height/2+130+interval);
    connect(m_pSaveBtn,&QPushButton::clicked,this,&VisionFrom::save);

    m_closeBtn = new QPushButton("关闭",m_pGroupBox);
    m_closeBtn->setIcon(QIcon(":/src/Image/close.png"));
    m_closeBtn->resize(60,33);
    m_closeBtn->move(410,m_height/2+72+interval);
    connect(m_closeBtn,&QPushButton::clicked,this,&VisionFrom::closeCamera);

    m_pCheckerBoardBtn = new QPushButton("棋盘格",m_pGroupBox);
    m_pCheckerBoardBtn->resize(60,33);
    m_pCheckerBoardBtn->move(485,m_height/2+72+interval);
    connect(m_pCheckerBoardBtn,&QPushButton::clicked,this,&VisionFrom::onCheckerBoardClicked);

    QLabel *b = new QLabel("曝光：",m_pGroupBox);
    b->move(20,m_height/2+72+interval);
    m_pExpossureEdit = new QSpinBox(m_pGroupBox);
    m_pExpossureEdit->move(80,m_height/2+70+interval);
    m_pExpossureBtn = new QPushButton("设置",m_pGroupBox);
    m_pExpossureBtn->resize(50,33);
    connect(m_pExpossureBtn,&QPushButton::clicked,this,&VisionFrom::setExpossure);
    m_pExpossureBtn->move(230,m_height/2+72+interval);
    m_pExpossureBtn->resize(40,26);

    QLabel *gain = new QLabel("增益：",m_pGroupBox);
    gain->move(20,m_height/2+132+interval);
    m_pGainEdit = new QSpinBox(m_pGroupBox);
    m_pGainEdit->move(80,m_height/2+130+interval);
    m_pGainBtn = new QPushButton("设置",m_pGroupBox);
    m_pGainBtn->resize(50,33);
    connect(m_pGainBtn,&QPushButton::clicked,this,&VisionFrom::setGain);
    m_pGainBtn->move(230,m_height/2+132+interval);
    m_pGainBtn->resize(40,26);
    m_pGroupBox->setStyleSheet("QLabel{font: 20px;}QSpinBox{Padding-right:20px;Border:2px solid white;font:20px; Min-width:90px;Min-height:25px;border-radius:5px;}QGroupBox{border: 2px solid white;border-radius:8px;margin-top:6px;}QGroupBox:title{color:rgb(24,24,58);subcontrol-origin: margin;left: 10px;}QGroupBox{font: 22px;}");

}

void VisionFrom::readFram()
{
    //获取图像帧
    m_videoCapture>>frame;
    /*
        //将抓取到的帧,转换为QImage格式,QImage::Format_RGB888使用24位RGB格式（8-8-8）存储图像
        //此时没有使用rgbSwapped()交换所有像素的红色和蓝色分量的值，底色偏蓝
        QImage image = QImage((const uchar*)frame.data,frame.cols, frame.rows,QImage::Format_RGB888);
        //将图片显示到label上
        ui->label->setPixmap(QPixmap::fromImage(image));
        */
    //    Mat gray,therold;
    //    cvtColor(frame,gray,cv::COLOR_BGR2GRAY);
    //cv::threshold(gray,frame,0,255,ThresholdTypes::THRESH_BINARY);
    //将视频显示到label上

    line(frame,Point(frame.cols/2,0),Point(frame.cols/2,frame.rows),Scalar(0,255,0));
    line(frame,Point(0,frame.rows/2),Point(frame.cols,frame.rows/2),Scalar(0,255,0));
    QImage image = QImage((const uchar*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888).rgbSwapped();
    m_vision_label->setPixmap(QPixmap::fromImage(image));
}

void VisionFrom::openCamera()
{
    //    m_videoCapture.open(0);//打开摄像头
    m_pDevice->StartSnap();
}

void VisionFrom::closeCamera()
{
    //    m_timer->stop();//关闭定时器
    m_pDevice->StopSnap();
}

///
/// \brief VisionFrom::transformation pixP2rebootP
/// \param x pix x
/// \param y pix y
/// \return  rebootP
///
QMap<double, double> VisionFrom::transformation(double x, double y)
{

   double r_x = (-47.6486*x) + (1.95346e-13*y+ -6152.71);
   double r_y = (-1.65433e-15*x) + (47.6228*y+ 920198);
   QMap<double, double> p;
   p.insert(r_x,r_y);
   return p;
}

void VisionFrom::resiveImageData(unsigned char *data)
{
    QImage img(data, m_pDevice->width, m_pDevice->height, m_pDevice->width, QImage::Format_Grayscale8);
    QImage new_img = img.scaled( m_vision_label->width(),m_vision_label->height());
    QPixmap pixmap = QPixmap::fromImage(new_img);
    m_vision_label->setPixmap(pixmap);
    frame.create(m_matHeight,m_matWidth,CV_8UC1);
    memcpy(frame.data,data,m_matHeight*m_matWidth);
    //新图像采集标记
    m_trigger = true;
}

void VisionFrom::setExpossure()
{
    m_pDevice->SetExposure(m_pExpossureEdit->value());
}

void VisionFrom::setGain()
{
    //m_pDevice->SetGain(m_pGainEdit->value());
    if(point_camera.size() == point_rebot.size())
    {
        Mat warpMat = estimateAffinePartial2D(point_camera,point_rebot);
        qDebug()<<"A"<< warpMat.ptr<double>(0)[0];
        qDebug()<<"B"<< warpMat.ptr<double>(0)[1];
        qDebug()<<"C"<< warpMat.ptr<double>(0)[2];


        qDebug()<<"D"<< warpMat.ptr<double>(1)[0];
        qDebug()<<"E"<< warpMat.ptr<double>(1)[1];
        qDebug()<<"F"<< warpMat.ptr<double>(1)[2];
    }
    else
        qDebug()<<"camera size != reboot size";
}

void VisionFrom::onTrigger()
{
    m_pDevice->OnceSnap();
}

void VisionFrom::onCheckerBoardClicked()
{
    Mat image,img_gray;
    int rowCount = 8;
    int colCount = 11;
    int BOARDSIZE[2]{rowCount,colCount};//棋盘格每行每列角点个数
    vector<vector<Point3f>> objpoints_img;//保存棋盘格上角点的三维坐标
    vector<Point3f> obj_world_pts;//三维世界坐标
    vector<vector<Point2f>> images_points;//保存所有角点
    vector<Point2f> img_corner_points;//保存每张图检测到的角点
    vector<String> images_path;//创建容器存放读取图像路径

    //frame = imread("C:\\Users\\jian.shen\\Documents\\chessboard.png");
    if(frame.empty())
        return;
   qDebug()<<"channels = "<<frame.channels();
    //转世界坐标系
        for (int i = 0; i < BOARDSIZE[1]; i++)
        {
            for (int j = 0; j < BOARDSIZE[0]; j++)
            {
                obj_world_pts.push_back(Point3f(j, i, 0));
            }
        }


            //cvtColor(frame, img_gray, COLOR_BGR2GRAY);
            //检测角点
            bool found_success = findChessboardCorners(frame, Size(BOARDSIZE[0], BOARDSIZE[1]),
                img_corner_points,CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FAST_CHECK | CALIB_CB_NORMALIZE_IMAGE);

            //显示角点
            if (found_success)
            {
                 //迭代终止条件
                 TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.001);

                 //进一步提取亚像素角点
                 cornerSubPix(frame, img_corner_points, Size(11, 11),
                     Size(-1, -1), criteria);
                 cvtColor(frame,frame,COLOR_GRAY2BGR);

                 //绘制角点
                 drawChessboardCorners(frame, Size(BOARDSIZE[0], BOARDSIZE[1]),img_corner_points,
                     found_success);

                 objpoints_img.push_back(obj_world_pts);//从世界坐标系到相机坐标系
                 images_points.push_back(img_corner_points);
            }
            double y_t = 0;
            int count =0;
            for(int i = 0;i < img_corner_points.size();i++)
            {

                if((i+1)%rowCount != 0)
                {
                   // y_t += qAbs;
                    //求出两个角点之间的距离
                    double x = img_corner_points.at(i).x - img_corner_points.at(i+1).x;
                    double y = img_corner_points.at(i).y - img_corner_points.at(i+1).y;

                    double linePix = sqrt((x*x)+(y*y));
                    y_t += linePix;
                    qDebug()<<"linePix:"<<linePix;
                    count ++;
                }
//                qDebug()<<"x:"<<img_corner_points.at(i).x<<"y:"<<img_corner_points.at(i).y;
            }
              qDebug()<<"y_t = "<<y_t<< "counts ="<<count<< "count1="<<(rowCount-1)*colCount;
            //棋盘格单位长度
            double c = 0.5;
            if(y_t != 0)
            {
                double pix2mm = c/(y_t/((rowCount-1)*colCount*1.0));
                qDebug()<<"pix2mm"<<pix2mm;
                CheckerboardResuleSave("Camera_1",pix2mm);//这里应该是驱动指针的userName
            }
          imshow("output", frame);


}

///
/// \brief VisionFrom::CheckerboardResuleSave 将棋盘格校准后的pix2mm结果保存在数据库
/// \param cameraName 相机的名称
/// \param pix2mm 转换后每像素对应的毫米值
/// \return  true = save successful
///
bool VisionFrom::CheckerboardResuleSave(const QString &cameraName,const double &pix2mm)
{
    qDebug()<<"in";
    QString sql = QString("update t_visionParameter set pix2mm = '%1' where camera_name = '%2'").arg(pix2mm).arg(cameraName);
    QSqlDatabase dataBase = DataBaseManager::GetInstance()->GetDataBase();
    qDebug()<<"2";
    QSqlQuery query(dataBase);

            bool result = query.exec(sql);
            qDebug()<<sql << "result "<<result;
            return result;

}

///
/// \brief VisionFrom::saveVisionParmeter 保存矩阵变换后的abcdef
/// \param a
/// \param b
/// \param c
/// \param d
/// \param e
/// \param f
/// \param pix2mm
/// \return
///
bool VisionFrom::saveVisionParmeter(const double &a, const double &b, const double &c, const double &d, const double &e, const double &f, const double &pix2mm)
{
    QStringList names,values;
    names<<"camera_name"<<"A"<<"B"<<"C"<<"E"<<"F"<<"G";
    QString cameraName = QString::fromStdString(m_pDevice->userName);
    values <<cameraName<<QString::number(a)<<QString::number(b)<<QString::number(c)<<QString::number(d)<<QString::number(e)<<QString::number(f);
    if(false ==DataBaseManager::GetInstance()->ExcInsertDb("t_visionParmeter",names,values))
    {
        names.clear();
         names<<"A"<<"B"<<"C"<<"E"<<"F"<<"G";
         values<<QString::number(a)<<QString::number(b)<<QString::number(c)<<QString::number(d)<<QString::number(e)<<QString::number(f);
        values.clear();
        QString expression = QString("camera_name = '%1'").arg(cameraName);
        return DataBaseManager::GetInstance()->ExcUpdateDb("t_visionParmeter",names,values,expression);
    }
    return true;
}

/// \brief VisionFrom::trigger 外部触发图像采集并处理图像
/// \param point 返回mark点的位置
/// \return false = 处理失败；
///
bool VisionFrom::trigger(QPoint &point, QString &msg)
{
    //触发前标志位
    m_trigger = false;
    //触发图像采集
    onTrigger();

//    while(true)
//    {

//    }
    if(m_trigger == false)
    {
        msg = "Can`t get the image;";
        return false;
    }
    ImageProcess ImProcess;
    return ImProcess.getMarkPoint(frame,point);


}

void VisionFrom::save()
{
    Mat src,gray;
    src = frame;
    //cv::resize(frame,src,Size( m_vision_label->width(),m_vision_label->height()));
    //cvtColor(src,gray,COLOR_BGR2GRAY);

    std::vector<cv::Vec3f> cricles;
    medianBlur(src,src,3);
    HoughCircles(src,cricles,cv::HOUGH_GRADIENT,1.5,10,160,50,0,30);
    if(cricles.size() !=0)
    {
        cvtColor(src,src,COLOR_GRAY2BGR);
        for(int i = 0;i < cricles.size();i++)
        {
             cv::circle(src,cv::Point(cricles[i][0],cricles[i][1]),cricles[i][2],cv::Scalar(0,0,255),2);
             //qDebug()<<"redio :"<<cricles[i][2];
             //测试pix2mm的精度
             //qDebug()<<cricles[i][2]*ShareData::GetInstance()->m_visionMap["Camera_1"].pix2mm;
             if(i!=0)
             qDebug()<<sqrt(((cricles[i][0]-cricles[i-1][0])*(cricles[i][0]-cricles[i-1][0]))+((cricles[i][1]-cricles[i-1][1])*(cricles[i][1]-cricles[i-1][1])))*ShareData::GetInstance()->m_visionMap["Camera_1"].pix2mm;
        }
        Point2f p_c(cricles[0][0],cricles[0][1]);
        point_camera.push_back(p_c);
        Point2f p_r(ShareData::GetInstance()->m_axisPositonMap[7],ShareData::GetInstance()->m_axisPositonMap[0]);
        point_rebot.push_back(p_r);
        //qDebug()<<"find circle count :"<<cricles.size();
        qDebug()<<"center:"<<cricles[0][0]<<","<<cricles[0][1]<<endl;
        qDebug()<<"axis:"<< ShareData::GetInstance()->m_axisPositonMap[7]<<","<<ShareData::GetInstance()->m_axisPositonMap[0];
        QMap<double, double> map = transformation(cricles[0][0] , cricles[0][1]);
        auto it = map.begin();
        qDebug()<< "x 差值: "<<it.key() - ShareData::GetInstance()->m_axisPositonMap[7]<<"y 差值："<<it.value()-ShareData::GetInstance()->m_axisPositonMap[0];
        int interval = 171 - cricles[0][1]  ;
        if( -125 <= interval && interval <= 152 )
        {
            int offect = interval * 50;

 //           qDebug()<<"offect = "<< offect;

//            MotionControl  m;
//            m.relativeMove(0,offect);
        }
    }
    imshow("src",src);
}
