#ifndef SHAREDATA_H
#define SHAREDATA_H
#include <QString>
#include <QObject>

class ShareData
{
private:
    ShareData();
    static ShareData* Instance;

public:
    static ShareData* GetInstance();
    int m_width;
    int m_heitht;
};

#endif // SHAREDATA_H
