#ifndef __WINDOWS3_H
#define __WINDOWS3_H

#include "window_includes.h"

extern unsigned char  OK_Status ;
unsigned char GetOKStatus(void);           // ��ȡOK״̬
void EnterMsgThirdControEventTrigger(void* para);// ���봰���¼���Ӧ

void EnterMsgThirdLevelCreate(void* para);// �����������(����)

void AutoGetTargetAddrControEventTrigger(void* para);// �Զ���ȡĿ���ַ��Ӧ�¼�
void AutoGetTargetAddrCreate(void* para);// �����Զ���ȡĿ���ַ(����)

#endif 