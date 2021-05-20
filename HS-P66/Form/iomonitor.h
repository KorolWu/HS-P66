#ifndef IOMONITOR_H
#define IOMONITOR_H

#include <QLabel>
#include <QTimer>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "DataStruct.h"
#include "sharedata.h"
#include "APS168.h"
#include "type_def.h"
#include "APS_Define.h"
#include "ErrorCodeDef.h"
#include <QDebug>
#include "motioncontrol.h"

///
/// \brief The IoMonitor class
/// IO 监视页面 通过传入板卡ID和 io表示的别名生成监视页面
///
class IoMonitor : public QWidget
{
public:
    IoMonitor(int carNum, QStringList alisaList, QStringList outAlisaList, QWidget *parent = nullptr);
private:
    void initUi();
    int m_carNum;
    QStringList m_alsaList;
    QStringList m_outAlisaList;
    const int DI_NUMBER = 16;
    const int DO_NUMBER = 16;
    QLabel* m_io_light[16];
    QLabel* m_io_name[16];
    QPushButton* m_btn[16];
    QLabel* m_do_light[16];
    QHBoxLayout *m_hbox;
    QVBoxLayout *m_vbox;
    QTimer *m_timer;
private slots:
    void updateIo();
    void onDoClicked();
};

#endif // IOMONITOR_H
