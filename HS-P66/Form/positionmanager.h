#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "positionfrom.h"
#include "sharedata.h"
#include "axisinfoui.h"

///
/// \brief The PositionManager class 点位示教页面
///
class PositionManager : public QWidget
{
    Q_OBJECT
public:
    explicit PositionManager(QWidget *parent = nullptr);

signals:
private:
    int m_width,m_height;
    void initUi();
    AxisInfoUI* m_pX;
    AxisInfoUI* m_pY;
    AxisInfoUI* m_pZ;
public slots:
};

#endif // POSITIONMANAGER_H
