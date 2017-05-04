#ifndef __RFDRIVER_READER_H
#define __RFDRIVER_READER_H

#include "stm32f10x.h"
#include "device.h"

#define RF_ELEMENT    30//element

void RfModeInit(void);
void RfRxIntEnable(void);
void RfRxIntDisable(void);

INT8U RfEventEnqueue(INT8U* pdata);// ���ݽ��� �����
INT8U RfEventDelqueue(INT8U* pcmd,INT8U* prdata,INT8U* prlen);// ���� ������ ����

void RFSendMsgDataPackage(const INT8U* addr_domain,INT8U cmd,const INT8U* pdata,INT8U len,INT8U* prdata,INT8U* rlen);

#endif