#ifndef SHAREDATA_H
#define SHAREDATA_H
#include <QString>
#include <QObject>
#include <QMap>
#include "DataStruct.h"

class ShareData
{
private:
    ShareData();
    static ShareData* Instance;

public:
    static ShareData* GetInstance();
    int m_width;
    int m_heitht;
    //carNum, dIstatus
    QMap <int,DIInfostru> m_DI_Status;
};

#endif // SHAREDATA_H
