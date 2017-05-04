#ifndef __TIMERDRIVER_H_
#define __TIMERDRIVER_H_

#include "stm32f10x.h"

#define CNTLEN            5    //�����ʱ��������������<15��

#define TIME_MODE_ONCE    0x01 //����һ��ģʽ
#define TIME_MODE_CYCLE   0x02 //ѭ������ģʽ

#define FLAGSETBIT(x)     (1<<x)
#define FLAGRESETBIT(x)   (~FLAGSETBIT(x))

typedef void(*timefuc)(void* para);

//extern void TIMER2_TimerInit(void);
extern void SysTickConfiguration(void);
/*
- ��������:  �����ʱ������
- ��ڲ���:  time_out ���ʱ��,prio_timnum���ص�ǰ��ʱ����
             time_fuction �ص�����  para�ص�����  time_mode��ʱ����ģʽ
- ���ڲ���:  ��
- ��ע    �� ��mainʹ��
*/
void TimeAStartSet(uint32_t time_out,uint8_t* prio_timnum,timefuc time_fuction,
                   void* para,uint8_t time_mode);
/*
-��������:  GetTimeOutFlag ��ȡ��ʱ�����־
-��ڲ���:  ��ǰ�����ʱ����
-���ڲ���:  1�������͹���� 0����δ�������
- ��ע    �� ��mainʹ��
*/
uint8_t GetTimeOutFlag(uint8_t prio_timenum);

uint32_t GetTimeSet(uint8_t prio_timenum);

uint32_t GetProTime(uint8_t prio_timenum);

/*ʧ�ܵ�ǰ��ʱ������*/
void TimexDis(uint8_t prio_timenum);
/*ʹ�ܵ�ǰ��ʱ������*/
void TimexEn(uint8_t prio_timenum , uint32_t time_set);
void TimexTimeSet(uint8_t prio_timenum , uint32_t time_set);
/*
- ��������:  �����ʱ���ж�,��ɸ������ʱ���Ķ�ʱ���̼��ص�����
- ��ע    �� ��interruptʹ��
*/
void IntTimeACnt(uint32_t* timeout_flag);

#endif