#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QPoint>
#include "opencv2/opencv.hpp"

class ImageProcess
{
public:
    ImageProcess();
    bool getMarkPoint(const cv::Mat &data, QPoint &point);

};

#endif // IMAGEPROCESS_H
