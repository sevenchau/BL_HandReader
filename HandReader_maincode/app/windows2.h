#ifndef __WINDOWS2_H
#define __WINDOWS2_H

#include "window_includes.h"

void MainSecondLevelUnselectEvent(void *para);/*δѡ�пؼ���������*/
void MainSecondLevelSelectEvent(void *para);/*ѡ�пؼ�*/

void MainSecondLevelControlEventTrigger(void* para);/*�ؼ���Ӧ*/

void CurSecondLevelInterfaceCreate(void* para);//������ǰ��Ϣ����

void SetStringNumberValue(char* string);       // ���ÿؼ���ʾֵ
char GetStringNumberValue(void);               // ��ȡ�ؼ���ʾֵ
void StorySecondLevelInterfaceCreate(void* para);//������ʷ��Ϣ����

void LocalSecondLevelInterfaceCreate(void* para);//����������Ϣ����

void CfgSecondLevelInterfaceCreate(void* para);// ����������Ϣ����

#endif 