#include "imageprocess.h"

ImageProcess::ImageProcess()
{

}


///
/// \brief ImageProcess::getMarkPoint 获取两条直线的交点
/// \param data  原始图像
/// \param point 两条直线的交点
/// \param lineStart 第一条直线信息 起点终点坐标
/// \param lineEnd   第二条直线信息
/// \return          没有找到返回false
///
bool ImageProcess::getMarkPoint(cv::Mat &data, QPoint &point, Vec4i &lineStart,Vec4i &lineEnd)
{
    cv::Mat blur,result;
    //::resize(frame,src,Size( m_vision_label->width(),m_vision_label->height()));
    cv::blur(data,data,Size(5,5));
    cv::Mat binaryImage,canny;
    cv::threshold(data,binaryImage,0,255, THRESH_OTSU | THRESH_BINARY);
    //    形态学开操作
    //    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    //    morphologyEx(binaryImage, binaryImage, MORPH_OPEN, kernel, Point(-1, -1));
    Canny(binaryImage,canny,0,255);
    imshow("canny",canny);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> effectiveContours;
    //寻找轮廓，只找外轮廓，记录轮廓上的所有点
    findContours(canny,contours,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    qDebug()<<"contours"<<contours.size();
    // 记录一些噪点导致的轮廓
    for(unsigned long ctn = 0; ctn < contours.size();ctn++)
    {
        qDebug()<<"contours count "<<ctn<<contours[ctn].size();
        if(contours[ctn].size() > 800)
        {
            effectiveContours.push_back(contours[ctn]);
        }
    }
    if(effectiveContours.size() == 2)
    {
        qDebug()<<"delete other lines affter"<<effectiveContours[0].size();
        qDebug()<<"delete other lines affter"<<effectiveContours[1].size();
        int cnt = 1;
        if(effectiveContours[0].at(0).x > effectiveContours[1].at(0).x)
            cnt = 0;
        //将内圈的轮廓涂黑
        std::vector<Point> points = effectiveContours[cnt];
        for (unsigned long i = 0;i < effectiveContours[cnt].size();i++) {
            canny.at<uchar>(points.at(i).y,points.at(i).x) = 0;
        }
        imshow("canny1",canny);
    }
    else if(effectiveContours.size() == 1)
    {
        qDebug()<<"select effective countours size = "<<effectiveContours.size();

    }
    else
        return false;
    vector<Vec4i> Lines;
    HoughLinesP(canny, Lines, 1, CV_PI / 360, 30, 50, 10);
    qDebug()<<"Hough find the lines count :"<<Lines.size();
    LineStand = Lines[0];
    // 斜率刚好=0 两条直线垂直
    bool normol = true;//正常斜率 !=0 情况
    bool findEndLine = false;//找到另一条边标志位
    Point2f crossPoint;
    if((LineStand[1] - LineStand[3] != 0) && (LineStand[0] - LineStand[2] != 0))
    {
        double ka = (double)(LineStand[3] - LineStand[1]) / (double)(LineStand[2] - LineStand[0]);
        double kb;
        for (unsigned long i = 1; i < Lines.size(); i++)
        {
            double ki = (double)(Lines[i][3] - Lines[i][1]) / (double)(Lines[i][2] - Lines[i][0]);
            if(qAbs((qAbs(gradientToAngle(ka)) - qAbs(gradientToAngle(ki)))) > 88) //(ki*ka <= 0)
            {
                LineAnother = Lines[i];
                kb = ki;
                qDebug()<<"ka = "<<ka<<" kb="<<kb<<LineAnother[0]<<LineAnother[1]<<LineAnother[2]<<LineAnother[3];
                 findEndLine = true;
                break;
            }
        }
    }
    else
    {
        qDebug()<<"xielv = 0";
        normol = false;
        // △y = 0   平行于x轴那条直线
        if(LineStand[1] - LineStand[3] == 0)//起始线条是垂直于y
        {
            crossPoint.y = LineStand[1];
            for (unsigned long i = 1; i < Lines.size(); i++)
            {
                double ki = Lines[i][1] - Lines[i][3];
                if (qAbs(ki) > 50)
                {
                    LineAnother = Lines[i];
                    crossPoint.x = LineAnother[0];
                    findEndLine = true;
                    break;
                }
            }
        }
        // △x = 0 垂直于x轴
        else if(LineStand[0] - LineStand[2] == 0)//起始线条是垂直于x
        {
            crossPoint.x = LineStand[0];
            for (unsigned long i = 1; i < Lines.size(); i++)
            {
                double ki = Lines[i][0] - Lines[i][2];
                if (qAbs(ki) > 50)
                {
                    LineAnother = Lines[i];
                    crossPoint.y = LineAnother[1];
                    findEndLine = true;
                    break;
                }
            }
        }
    }
    lineStart = LineStand;
    lineEnd = LineAnother;
    /*画出两条直线*/
    //result = data.clone();
    cvtColor(data,data,COLOR_GRAY2BGR);
    line(data,Point(LineStand[0], LineStand[1]),Point(LineStand[2], LineStand[3]),Scalar(0,0,255),2,8);
    line(data, Point(LineAnother[0], LineAnother[1]), Point(LineAnother[2], LineAnother[3]), Scalar(255,0,0), 2, 8);
    //        cout << "直线A过点(" << LineStand[0] << "," << LineStand[1] << ")以及点(" << LineStand[2]<<"，"<<LineStand[3] << ")；斜率为：" << ka;
    //        cout << "直线B过点(" << LineAnother[0] << "，" << LineAnother[1] << ")以及点(" << LineAnother[2] << "，" << LineAnother[3] << ")；斜率为：" <<kb;

    /*求交点并画点保存，result.jpg存储在工程目录下*/

    if(findEndLine == false)
    {
        qDebug()<<"Only Find one line!";
        return false;
    }

    if(true == normol)
        crossPoint = getCrossPoint(LineStand, LineAnother);
    circle(data, crossPoint, 3, Scalar( 0, 0,255),1);
    line(data,Point(crossPoint.x-5,crossPoint.y),Point(crossPoint.x+5,crossPoint.y),Scalar(0,255,0),1);
    line(data,Point(crossPoint.x,crossPoint.y-5),Point(crossPoint.x,crossPoint.y+5),Scalar(0,255,0),1);
    //imwrite("./result.jpg", result);
    imshow("result", data);
    point.setX(crossPoint.x);
    point.setY(crossPoint.y);
    qDebug()<<"THE CROSSPOINT :"<<point.x() <<","<<point.y();
    return true;
}

///
/// \brief ImageProcess::getCrossPoint 返回两条直线的交点
/// \param lineA
/// \param lineB
/// \return
///
Point2f ImageProcess::getCrossPoint(Vec4i lineA, Vec4i lineB)
{
    double ka, kb , y, x;
    Point2f crossPoint;
    ka = (double)(lineA[3] - lineA[1]) / (double)(lineA[2] - lineA[0]); //求出lineA斜率
    x = (double)(lineB[2] - lineB[0]);
    y = (double)(lineB[3] - lineB[1]);
    if(y == 0.0)// 第二条直线是平行于x轴
    {
        crossPoint.x = lineA[0];
        crossPoint.y = lineB[1];
    }
    else if(x == 0.0) //第二条直线是平行于 Y轴
    {
        crossPoint.x = lineB[0];
        crossPoint.y = lineA[1];
    }
    else
    {
        kb = y/x;
        qDebug()<<"Eka = "<<ka<<" Ekb="<<kb<<LineAnother[0]<<LineAnother[1]<<LineAnother[2]<<LineAnother[3];
        crossPoint.x = (ka*lineA[0] - lineA[1] - kb*lineB[0] + lineB[1]) / (ka - kb);
        crossPoint.y = (ka*kb*(lineA[0] - lineB[0]) + ka*lineB[1] - kb*lineA[1]) / (ka - kb);
    }
    return crossPoint;
}

///
/// \brief ImageProcess::gradientToAngle 将斜率转换为角度
/// \param gradient
/// \return
///
double ImageProcess::gradientToAngle(const double &gradient)
{
    double h = qAtan(gradient);
    return  h*180/3.1415926;
}
