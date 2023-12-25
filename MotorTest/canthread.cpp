#include "canthread.h"
#include "ControlCAN.h"
#include "ui_motor.h"

#include <QTime>
#include <QCoreApplication>
#include <QMetaType>
#include <string.h>

#define ExtEndable 1

MotorStrut MotorCurrentdate[Motor_Num];

bool Motor_State[Motor_Num];

CANThread::CANThread()
{
    stopped = false;
    qRegisterMetaType<VCI_CAN_OBJ>("VCI_CAN_OBJ");
    qRegisterMetaType<unsigned int>("DWORD");
}

void CANThread::stop()
{
    stopped = true;
}

bool CANThread::openDevice()
{
        int nDeviceType = deviceType; /* USBCAN-2A或USBCAN-2C或CANalyst-II */
        int nDeviceInd = debicIndex; /* 第1个设备 */
        int nCANInd = debicCom; /* 第1个通道 */
        qDebug() << "Device Type: " << nDeviceType;
        qDebug() << "Device Index: " << nDeviceInd;
        qDebug() << "CAN Channel Index: " << nCANInd;

        DWORD dwRel;
        dwRel = VCI_OpenDevice(nDeviceType, nDeviceInd, nCANInd);
        if(dwRel != 1)
        {
            qDebug()<<"open fail";
            return false;
        }
        else
            qDebug()<<"open success";

            dwRel = VCI_ClearBuffer(nDeviceType, nDeviceInd, 0);
        dwRel = VCI_ClearBuffer(nDeviceType, nDeviceInd, 1);
        VCI_INIT_CONFIG vic;
        vic.AccCode=0x80000008;
        vic.AccMask=0xFFFFFFFF;
        vic.Filter=1;
        vic.Mode=0;
        switch (baundRate) {
        case 10:
            vic.Timing0=0x31;
            vic.Timing1=0x1c;
            break;
        case 20:
            vic.Timing0=0x18;
            vic.Timing1=0x1c;
            break;
        case 40:
            vic.Timing0=0x87;
            vic.Timing1=0xff;
            break;
        case 50:
            vic.Timing0=0x09;
            vic.Timing1=0x1c;
            break;
        case 80:
            vic.Timing0=0x83;
            vic.Timing1=0xff;
            break;
        case 100:
            vic.Timing0=0x04;
            vic.Timing1=0x1c;
            break;
        case 125:
            vic.Timing0=0x03;
            vic.Timing1=0x1c;
            break;
        case 200:
            vic.Timing0=0x81;
            vic.Timing1=0xfa;
            break;
        case 250:
            vic.Timing0=0x01;
            vic.Timing1=0x1c;
            break;
        case 400:
            vic.Timing0=0x80;
            vic.Timing1=0xfa;
            break;
        case 500:
            vic.Timing0=0x00;
            vic.Timing1=0x1c;
            break;
        case 666:
            vic.Timing0=0x80;
            vic.Timing1=0xb6;
            break;
        case 800:
            vic.Timing0=0x00;
            vic.Timing1=0x16;
            break;
        case 1000:
            vic.Timing0=0x00;
            vic.Timing1=0x14;
            break;
        case 33:
            vic.Timing0=0x09;
            vic.Timing1=0x6f;
            break;
        case 66:
            vic.Timing0=0x04;
            vic.Timing1=0x6f;
            break;
        case 83:
            vic.Timing0=0x03;
            vic.Timing1=0x6f;
            break;
        default:
            break;
        }
        dwRel = VCI_InitCAN(nDeviceType, nDeviceInd, 0, &vic);
        dwRel = VCI_InitCAN(nDeviceType, nDeviceInd, 1, &vic);
        if(dwRel !=1)
        {
            qDebug()<<"init fail";
            return false;
        }
        else
            qDebug()<<"init success";

        VCI_BOARD_INFO vbi;

            dwRel = VCI_ReadBoardInfo(nDeviceType, nDeviceInd, &vbi);
        if(dwRel != 1)
        {
            return false;
        }
        else
        {
            qDebug()<<"CAN通道数："<<vbi.can_Num;
            qDebug()<<"硬件版本号:"<<vbi.hw_Version;
            qDebug()<<"接口库版本号："<<vbi.in_Version;
            qDebug()<<"中断号"<<vbi.irq_Num;
            emit boardInfo(vbi);
        }

        if(VCI_StartCAN(nDeviceType, nDeviceInd, 0) !=1)
        {
            qDebug()<<"start 0 fail";
            return false;
        }
        else
            qDebug()<<"start 0 success";

        if(VCI_StartCAN(nDeviceType, nDeviceInd, 1) !=1)
        {
            qDebug()<<"start 1 fail";
            return false;
        }
        else
            qDebug()<<"start 1 success";

        return true;
}

//3.启动CAN
bool CANThread::startCAN()
{
    if(VCI_StartCAN(m_deviceType, m_debicIndex, 0) !=1)
    {
        qDebug()<<"start 0 fail.";
        return false;
    }
    else
        qDebug()<<"start 0 success.";
    if(VCI_StartCAN(m_deviceType, m_debicIndex, 1) !=1)
    {
        qDebug()<<"start 1 fail.";
        return false;
    }
    else
        qDebug()<<"start 1 success.";
    return true;
}

//4.发送数据
bool CANThread::sendData(qint32 ID, quint8 *ch, qint32 comNum)
{
    unsigned int dwRel;
    VCI_CAN_OBJ vco;

    vco.ID = ID ;
    vco.RemoteFlag = 0;
    vco.ExternFlag = ExtEndable;
    vco.DataLen = 8;
    for(UINT j = 0;j < 8;j++)
    {
        vco.Data[j] = ch[j];
        qDebug() << " vco.Data in hexadecimal:" << QString("0x%1").arg( vco.Data[j], 0, 16);
     }

    dwRel = VCI_Transmit(deviceType, debicIndex, comNum,&vco,1);
    if(dwRel>0)
    {
        qDebug()<<"send success";
        return true;
    }
    else
    {
        qDebug()<<"send fail";
        return false;
    }

}

//5.关闭设备
void CANThread::closeDevice()
{
    VCI_CloseDevice(deviceType, debicIndex);
}


//0.复位设备，复位后回到3
bool CANThread::reSetCAN()
{
    if(VCI_ResetCAN(m_deviceType, m_debicIndex, 0) !=1)
    {
        qDebug()<<"reset 0 fail.";
        return false;
    }
    else
        qDebug()<<"reset 0 success.";
    if(VCI_ResetCAN(m_deviceType, m_debicIndex, 1) !=1)
    {
        qDebug()<<"reset 1 fail.";
        return false;
    }
    else
        qDebug()<<"reset 1 success.";
    return true;
}

void CANThread::run()
{
    qDebug("canthread -->  run");

    while(!stopped)
    {
        unsigned int dwRel;
        VCI_CAN_OBJ vco[2500];
        dwRel = VCI_Receive(deviceType, debicIndex, 0, vco,2500,0);
        if(dwRel > 0)
        {
            for(qint32  i = 0;i<dwRel;i++)
            {
                dealDate(vco,i);

            }
            emit getProtocolData(vco,dwRel);
        }
        else if(dwRel == -1)
        {
            qDebug()<<"设备不存在或USB掉线";
        }
        sleep(30);
    }
    stopped = false;
}

void CANThread::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void CANThread::dischage_chage_send(uint ID, quint16* charge, bool state)
{

    qDebug() << "ID: " << ID;
    quint32 form = ID >> 16; //设备类型
//    quint32 formframe = (ID >> 8) & 0x000000FF; //设备帧序号
    quint32 formNum = ID & 0x000000FF; //设备序号
    qDebug() << "form: " << form;
    qDebug() << "formNum: " << formNum;
//    qDebug() << "formframe: " << formframe;

    if (formNum <= Motor_Num)
    {
        MotorCurrentdate[formNum].frame[3].date[0].date16 = date16change(charge[0]); //formNum电机/frame帧数/date 2xbyte 电机转速
        MotorCurrentdate[formNum].frame[3].date[1].date16 = date16change(charge[1]); //formNum电机/frame帧数/date 2xbyte 电机转速
        MotorCurrentdate[formNum].frame[3].date[2].date16 = date16change(charge[2]); //formNum电机/frame帧数/date 2xbyte 电机转速
        MotorCurrentdate[formNum].frame[3].date[3].date16 = date16change(charge[3]); //formNum电机/frame帧数/date 2xbyte 电机转速
        qDebug() << "MotorCurrentdate in hexadecimal:" << QString("0x%1").arg(MotorCurrentdate[formNum].frame[3].date[0].date16, 0, 16);
        qDebug() << "MotorCurrentdate in hexadecimal:" << QString("0x%1").arg(MotorCurrentdate[formNum].frame[3].date[1].date16, 0, 16);
        qDebug() << "MotorCurrentdate in hexadecimal:" << QString("0x%1").arg(MotorCurrentdate[formNum].frame[3].date[2].date16, 0, 16);
        qDebug() << "MotorCurrentdate in hexadecimal:" << QString("0x%1").arg(MotorCurrentdate[formNum].frame[3].date[3].date16, 0, 16);

        sendData(ID, MotorCurrentdate[formNum].frame[3].date8, debicCom);
            qDebug() << "SEND"<<MotorCurrentdate[0].frame[3].date8;
    }

}

int CANThread::dealDate(VCI_CAN_OBJ *vci,quint32 i)
{

    qDebug() << "ID: " << vci[i].ID;

    quint32 form=vci[i].ID>>16; //设备类型
    quint32 formNum=(vci[i].ID>>8)&0x000000FF; //设备序号
    quint32 formframe=vci[i].ID&0x000000FF; //设备帧序号

    if((formNum)>Motor_Num||formframe>Motor_frame_Num) return false;
    if((formNum)>0x10||formframe>Motor_frame_Num) return false;
    for (quint8 j=0;j<8;j++) {
        MotorCurrentdate[formNum].frame[formframe].date8[j]=vci[i].Data[j];
        qDebug() << vci[i].Data[j];
    }

    Motor_State[formNum]=true;
}



