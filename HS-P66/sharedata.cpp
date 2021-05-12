#include "sharedata.h"

ShareData *ShareData::Instance = new ShareData();
ShareData::ShareData()
{
    m_DI_Status.clear();
}

ShareData *ShareData::GetInstance()
{
    return Instance;
}
