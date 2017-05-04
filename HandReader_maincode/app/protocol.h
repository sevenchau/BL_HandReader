#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "includes.h"

/*�豸  ����*/
#define RESET             0      //  �豸 ��λ
#define HEART             1      //  �豸 ����
#define EQU_STATUES       2      //  �豸 ״̬��ѯ
#define QUERY_EN          3      //  �豸 ��ѯ����
#define QUERY_DIS         4      //  �豸 ��ѯ����

#define NEW_RESET         5      //  ��λ�豸(��Э��)
#define RESET_FACTORY     6      //  �ָ���������

#define DOWNTRAINS        10     //  �´�ת��
#define UPTRAINS          20     //  �ϴ�ת��

/*��������������*/
//#define SWITCH            30     //  ����������
#define OPEN_LF125_1      31     //  ��125K
#define CLOSE_LF125_1     32     //  �ر�125K
#define OPEN_LF125_2      33     //  ��125K
#define CLOSE_LF125_2     34     //  �ر�125K
#define OPEN_RF433_1      35     //  ��433M
#define CLOSE_RF433_1     36     //  �ر�433M
#define OPEN_RF433_2      37     //  ��433M
#define CLOSE_RF433_2     38     //  �ر�433M
#define CLOSE_ALL         39     //  �ر�����

#define OPEN_RESTORE      40     //  �ָ�Ĭ��
#define OPEN_RX_UART_1    41     //  �򿪴���1
#define CLOSE_RX_UART_1   42     //  �رմ���1
#define OPEN_RX_UART_2    43     //  �򿪴���2
#define CLOSE_RX_UART_2   44     //  �رմ���2
#define OPEN_RX_UART_3_1  45     //  �򿪴���3
#define CLOSE_RX_UART_3_1 46     //  �رմ���3
#define OPEN_RX_UART_3_2  47     //  �򿪴���3
#define CLOSE_RX_UART_3_2 48     //  �رմ���3
#define OPEN_BUZZER       49     //  ����������
#define CLOSE_BUZZER      50     //  �رշ�����

/*д�ն˲�����������*/
#define WRCONFIG          60     //  д������Ϣ
#define WR_ID             61     //  дID
#define WR_SPWR           62     //  ���÷��͹���
#define WR_SSPD           63     //  ���÷�������
#define WR_SFRE           64     //  ���÷���Ƶ��
#define WR_RSPD           65     //  ���ý�������
#define WR_RFRE           66     //  ���ý���Ƶ��
#define WR_HTIM           67     //  ��������ʱ����
#define WR_LTIM           68     //  ���ö�λʱ����
#define WR_BUAD           69     //  ���ô��ڲ�����
#define WRCFGOK           79     //  �������

/*���ն˲�����������*/
#define RDCONFIG          80     //  ��������Ϣ
#define RD_ID             81     //  ��ȡ����ID
#define RD_SPWR           82     //  ��ȡ���͹���
#define RD_SSPD           83     //  ��ȡ��������
#define RD_SSFRE          84     //  ��ȡ����Ƶ��
#define RD_RSPD           85     //  ��ȡ��������
#define RD_RSFRE          86     //  ��ȡ����Ƶ��
#define RD_HTIM           87     //  ��ȡ����ʱ��
#define RD_LTIM           88     //  ��ȡ��λʱ��
/*��ȡ������չָ��*/
#define RD_CFGMSG         100    //  ��ȡ�豸���ò�����Ϣ
#define RD_DEVMSG         101    //  ��ȡ�豸������Ϣ

/*************************************************************/
/**************************���ݽ���***************************/
/*************************************************************/
/*flash ���ݽ���*/
uierr flash_ProDataLearning(const INT8U* data_buf , const INT8U size);

/*flash ��Ϣ�洢���*/
uierr flashInit_DataPackage(INT8U* buf , INT8U buflen);
void flash_DataPackage(const INT8U* buf , INT8U* rebuf, INT8U buflen);

#endif