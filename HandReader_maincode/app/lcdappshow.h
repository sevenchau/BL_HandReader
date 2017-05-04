#ifndef __LCD_APP_SHOW_H
#define __LCD_APP_SHOW_H

#include "window_includes.h"

INT8U* GetTargetAddress(void);   // ��ȡĿ���ַ
void SetTargetAddress(INT8U* addr); // ����Ŀ���ַ

void LCDKS0108_Initialize(void);  // ��ʼ��
void LcdLightOff(void);
void LcdLightOn(void);

void GLCD_ShowLoGo(void);       //��������
void MainInterfaceCreate(void*);//������

char GetActiveWindow(void);// ��ȡ�����

void EventResponseHander(unsigned int key_value);// �¼���Ӧ

INT8U LcdEventEnqueue(BUT_TypeDef* tigger_event); // �������
INT8U LcdEventDelqueue(unsigned char* pwindow_name,char* pbutton_name,int* pvalue_buf,unsigned char* pbuf_len);//���ݳ���

#endif