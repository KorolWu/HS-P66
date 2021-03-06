#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <QString>
#include <QMap>
#include <QVector>
#include <QSize>
#include <QObject>
#include <QDebug>


typedef struct _AxisStrcut
{
    int vMax;
    int acc;
    int dcc;
    int homeVmax;
}AxisStruct;
//传感器状态信息
typedef union
{
    struct {
        uint32_t
        bit0:1,
            bit1:1,
            bit2:1,
            bit3:1,
            bit4:1,
            bit5:1,
            bit6:1,
            bit7:1,
            bit8:1,
            bit9:1,
            bit10:1,
            bit11:1,
            bit12:1,
            bit13:1,
            bit14:1,
            bit15:1,
            bit16:1,
            bit17:1,
            bit18:1,
            bit19:1,
            bit20:1,
            bit21:1,
            bit22:1,
            bit23:1,
            bit24:1,
            bit25:1,
            bit26:1,
            bit27:1,
            bit28:1,
            bit29:1,
            bit30:1,
            bit31:1;
    };
    uint32_t OutputValue = 0;
}DoInfostru;


//传感器状态信息
typedef union
{
    struct {
        uint32_t
        bit0:1,
            bit1:1,
            bit2:1,
            bit3:1,
            bit4:1,
            bit5:1,
            bit6:1,
            bit7:1,
            bit8:1,
            bit9:1,
            bit10:1,
            bit11:1,
            bit12:1,
            bit13:1,
            bit14:1,
            bit15:1,
            bit16:1,
            bit17:1,
            bit18:1,
            bit19:1,
            bit20:1,
            bit21:1,
            bit22:1,
            bit23:1,
            bit24:1,
            bit25:1,
            bit26:1,
            bit27:1,
            bit28:1,
            bit29:1,
            bit30:1,
            bit31:1;
        // bit32:16;
    };
    uint32_t InputValue = 0;
}DIInfostru;//小车货传感器货物信息
typedef struct _VisionStu
{
    double A;  //像素到脉冲的矩阵变换的参数abcdef
    double B;
    double C;
    double D;
    double E;
    double F;
    double pix2mm; //每个像素点对应的毫米
}VisionStu;
typedef struct _NozzleStu
{
    QString name;
    int dpiTimes;
    int startP;
    int endP;
    QString filePath;//图形地址
    QString WavePath;//波形地址
    int flashJetStatus;//0:单次闪喷1:连续闪喷2:持续闪喷
    int cycle;//闪喷周期
    int offect;//比较触发的偏差
}NozzleStu;
#endif // DATASTRUCT_H
