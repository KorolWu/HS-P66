#include "imageprocess.h"

ImageProcess::ImageProcess()
{

}

bool ImageProcess::getMarkPoint(const cv::Mat &data, QPoint &point)
{
    //

    cv::Mat blur,gray;
    //::resize(frame,src,Size( m_vision_label->width(),m_vision_label->height()));
    //cvtColor(src,gray,COLOR_BGR2GRAY);

    std::vector<cv::Vec3f> cricles;
    medianBlur(data,blur,3);
    return true;
}
