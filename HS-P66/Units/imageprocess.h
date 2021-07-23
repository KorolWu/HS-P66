#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QPoint>
#include <QDebug>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

class ImageProcess
{
public:
    ImageProcess();
    bool getMarkPoint(const cv::Mat &data, QPoint &point, Vec4i &lineStart, Vec4i &lineEnd);
private:
    Vec4i LineStand;
    Vec4i LineAnother;
    Point2f getCrossPoint(Vec4i lineA,Vec4i lineB);

};

#endif // IMAGEPROCESS_H
