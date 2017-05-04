#ifndef __TIMERDRIVER_H_
#define __TIMERDRIVER_H_

#include "includes.h"
#include "stm32f10x.h"

#define CNTLEN            5    //�����ʱ��������������<15��

#define TIME_MODE_ONCE    0x01 //����һ��ģʽ
#define TIME_MODE_CYCLE   0x02 //ѭ������ģʽ

#define FLAGSETBIT(x)     (1<<x)
#define FLAGRESETBIT(x)   (~FLAGSETBIT(x))

typedef void(*timefuc)(void* para);

extern void TIMER2_TimerInit(void);
/*
- ��������:  �����ʱ������
- ��ڲ���:  time_out ���ʱ��,prio_timnum���ص�ǰ��ʱ����
             time_fuction �ص�����  para�ص�����  time_mode��ʱ����ģʽ
- ���ڲ���:  ��
- ��ע    �� ��mainʹ��
*/
void TimeAStartSet(INT32U time_out,INT8U* prio_timnum,timefuc time_fuction,
                   void* para,INT8U time_mode);
/*
-��������:  GetTimeOutFlag ��ȡ��ʱ�����־
-��ڲ���:  ��ǰ�����ʱ����
-���ڲ���:  1�������͹���� 0����δ�������
- ��ע    �� ��mainʹ��
*/
INT8U GetTimeOutFlag(INT8U prio_timenum);

INT32U GetTimeSet(INT8U prio_timenum);

INT32U GetProTime(INT8U prio_timenum);

/*ʧ�ܵ�ǰ��ʱ������*/
void TimexDis(INT8U prio_timenum);
/*ʹ�ܵ�ǰ��ʱ������*/
void TimexEn(INT8U prio_timenum , INT32U time_set);
void TimexTimeSet(INT8U prio_timenum , INT32U time_set);
/*
- ��������:  �����ʱ���ж�,��ɸ������ʱ���Ķ�ʱ���̼��ص�����
- ��ע    �� ��interruptʹ��
*/
void IntTimeACnt(INT32U* timeout_flag);

#endif