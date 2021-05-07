//自定义按钮，实现Normal、Hover、Press
#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H
#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
class PushButton:public QPushButton
{
    Q_OBJECT
public:
    QString strParam;
    QString id;
    Qt::AlignmentFlag m_aligment;
private:
   enum ButtonStatus{NORMAL, HOVER, PRESS}; //枚举按钮的几种状态
   ButtonStatus status;
   QString icon_path;//路径名
   bool mouse_press; //按钮左键是否按下
   uchar m_uc;
   uchar m_ucSpacing;
public:
   explicit PushButton(QWidget *parent = nullptr);
   ~PushButton();
   void getIconPath(QString icon_path);//得到图片的路径名字，并且设置按钮为图片的大小
   void enterEvent(QEvent *);//进入事件
   void leaveEvent(QEvent *);//离开事件
   void mousePressEvent(QMouseEvent *event);  //鼠标按下事件
   void mouseReleaseEvent(QMouseEvent *event); //鼠标释放事件
   void paintEvent(QPaintEvent *);//按钮绘图事件
   void setStatusImageNum(uchar uc);
   void SetTextAlignment(Qt::AlignmentFlag alignment){m_aligment = alignment;}
   void setTextSpacing(uchar uc){m_ucSpacing = uc;}
signals:
    QString sendSignal(QString,QString);
public slots:
    void getClicked()
    {
        emit sendSignal(strParam,id);
    }
};
#endif // PUSHBUTTON_H
