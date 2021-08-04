#ifndef NOZZLEFROM_H
#define NOZZLEFROM_H

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QDebug>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "sharedata.h"
#include "DataStruct.h"
#include "databasemanager.h"

class NozzleFrom : public QWidget
{
    Q_OBJECT
public:
    explicit NozzleFrom(QWidget *parent = nullptr);

signals:
private:
    void initUi();
    bool updateNozzleParameter();
    int m_width,m_height;
    QGroupBox *m_pDpiSetGroubox;//精度设置
    QSpinBox *m_pDpiTimes;//图形dpi精度的倍数
    QPushButton *m_pDpiSetBtn;
    QGroupBox *m_pNozzleGroubox;//喷头设置，起始喷孔，终止喷孔，打印位置，写入的波形
    QVBoxLayout *m_pVbox;
    QHBoxLayout *m_pHbox;
    QSpinBox *m_pStartP,*m_pEndP,*m_pOffect;
    QPushButton *m_pPSetBtn;//起始喷孔和终止喷孔设置
    QLineEdit *m_pFilePath;
    QLineEdit *m_pWavePath;
    QPushButton *m_pfilePathSetBtn;
    QPushButton *m_pWavePathSetBtn;
    QGroupBox *m_pNozzleSetGroubox;//闪喷模式的设置
    QRadioButton *m_pCheckBox[3];//单次闪喷 持续闪喷 连续闪喷
    QSpinBox *m_pCycle; //闪喷周期
    QPushButton *m_pFlashJetSet;//闪喷设置
    QVBoxLayout *vbox;

public slots:
   void onSetBtnClicked();
   void onDpiSetBtnClicked();
   void onFileBtnClicked();
   void onFlashJetSetClicked();
public:
   int m_flashStatus = 0;
   void setParameter(NozzleStu nozzleStruct);
};

#endif // NOZZLEFROM_H
