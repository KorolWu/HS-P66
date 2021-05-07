#include "sharedata.h"

ShareData *ShareData::Instance = new ShareData();
ShareData::ShareData()
{

}

ShareData *ShareData::GetInstance()
{
    return Instance;
}
