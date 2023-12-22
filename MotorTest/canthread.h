#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QThread>
#include "ControlCAN.h"
#include <QDebug>
#include "QElapsedTimer"

//设备数量
#define Motor_Num 10 //电机数量

//数据帧数
#define Motor_frame_Num 5//电机帧数量
#define SEM_frame_Num 2 //控制帧数量

struct Statedate{quint8 state1:1;quint8 state2:1;quint8 state3:1;quint8 state4:1;quint8 state5:1;quint8 state6:1;quint8 state7:1;quint8 state8:1;};


struct Alertdate{quint8 Alert1:2;quint8 Alert2:2;quint8 Alert3:2;quint8 Alert4:2;};

union q8_q2x4_q1x8{Statedate statedate1;Alertdate Alertdate2;quint8 quint8;};

union q16_q8x2{q8_q2x4_q1x8 date8[2];quint16 date16;};

#define date16change(data)    ((data<<8)&0xff00)|((data>>8)&0x00ff)  //高低互换
#define setCharBit(a,n)  (a | (1<<n))  //某位设1
#define clrCharBit(a,n)  (a & ~(1<<n)) //某位设0

#define SetStatebit(a,n,b)  a=(b==1)?setCharBit(a,n):clrCharBit(a,n)   //设置a第n位 为b

//设备数据结构

union Motorframe1{q16_q8x2 date[4];quint8 date8[8];Alertdate alertdate[8]; Statedate statedate[8];};
struct MotorStrut{Motorframe1 frame[Motor_frame_Num];};

class CANThread:public QThread
{
    Q_OBJECT
public:
    CANThread();

    void stop();

    //1.打开设备
//    bool openDevice(UINT deviceType,UINT debicIndex,UINT baundRate);
    bool openDevice();
    //2.初始化CAN
    bool initCAN();

    //3.启动CAN
    bool startCAN();

    //4.发送数据
    bool sendData(qint32 ID, quint8 *ch, qint32 comNum);

    //5.关闭设备
    void closeDevice();

    //0.复位设备，  复位后回到3
    bool reSetCAN();

    //Motor发送
    void dischage_chage_send(uint ID, quint16* charge, bool state);

    //Motor接受
    int dealDate(VCI_CAN_OBJ *vci,quint32 i);

    UINT m_deviceType;
    UINT m_debicIndex;
    UINT m_baundRate;
    UINT m_debicCom;

    int deviceType;
    int debicIndex;
    int baundRate;
    int debicCom;

    bool stopped;

signals:
    void getProtocolData(VCI_CAN_OBJ *vci,unsigned int dwRel);
    void boardInfo(VCI_BOARD_INFO vbi);

private:
    void run();
    void sleep(int msec);

};

#endif // CANTHREAD_H
