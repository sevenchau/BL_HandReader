#ifndef __WINDOWS1_H
#define __WINDOWS1_H

#include "window_includes.h"

void AppCursorGlink(void);/*�����˸*/
void GLCD_ClearScreen(void);// ����
void GLCD_ShowLoGo(void);/*��ʾ��˾logo*/

void MainControlEventTrigger(void* para);/*������ؼ��¼�*/
void MainInterfaceCreate(void* para);/*����������*/

void StorUserName(INT8U* pvalue,INT8U len);
void ChangeInfomationFromInput(void); // ˢ�´�����ʾֵ
void SendMsgControlEventTrigger(void* para);/*�ؼ���Ӧ*/
void SendMsgWindowCreate(void* para);/*����������*/
void GetSendMsgWindowData(char* puser_name,char* ppass_word,char* pdata_mark,char* pdata,char* pdlen);

#endif 