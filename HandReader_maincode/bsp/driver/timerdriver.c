#include "timerdriver.h"
#include "string.h"

#if CNTLEN > 31
#error "CNTLEN  ��������31!"
#endif

//#define uint8  INT8U     
//#define uint16 INT32U    

typedef INT32U strFlag;
typedef struct __TIME_CNT
{
  INT32U  TimeOut;         //��ʱʱ��
  INT32U  TimeCnt;         //������
  INT8U   TimeMode;        //��ʱģʽ
  strFlag TimeOutFlag;     //��־λ
  timefuc TimeFuction;     //�ص�
  void*   Para;            //����
}strTime;
static strTime TimeACnt[CNTLEN];
static INT8U UseTimeMaxNum;       //��ǰ�Լ�ʹ�ö�ʱ�������

void TIMER2_TimerInit(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  TIM_DeInit(TIM2);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  TIM_TimeBaseStructure.TIM_Period = 20;                          // ������ֵ,�����趨�ķ�Ƶ�� 0.001s  
  TIM_TimeBaseStructure.TIM_Prescaler = 3600-1;                  // ��Ƶ3600
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;         // ʱ�ӷָ�  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     // �����������ϼ���
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_SetAutoreload(TIM2, 20);        
  TIM_ARRPreloadConfig(TIM2, ENABLE); 
  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  
  TIM_Cmd(TIM2, ENABLE);
  
  BSP_IntVectSet(BSP_INT_ID_TIM2, BSP_IntHandlerTIM2); 
  BSP_IntPrioSet(BSP_INT_ID_TIM2,1);
  BSP_IntEn(BSP_INT_ID_TIM2);
}

static INT8U GetTimeANum(void);
/*
- ��������:  ��ȡһ����ʱ��
- ��ڲ���:  ��
- ���ڲ���:  ��ʱ����
- ��ע    �� ���ļ��ڲ�ʹ��
*/
static INT8U GetTimeANum(void)
{
  static INT8U init_flag = 0;
  static INT8U time_num = 0;
  
  if(!init_flag)
  {
    init_flag = 1;
    return time_num;
  }
  
  TimeACnt[time_num].TimeOut     = 0;
  TimeACnt[time_num].TimeCnt     = 0;
  TimeACnt[time_num].TimeMode    = 0;
  TimeACnt[time_num].TimeOutFlag = 0;
  TimeACnt[time_num].TimeFuction = (void*)0;
  TimeACnt[time_num].Para        = (void*)0;
  time_num ++;

  return time_num;
}

/*
- ��������:  �����ʱ������
- ��ڲ���:  time_out ���ʱ��,prio_timnum���ص�ǰ��ʱ����
             time_fuction �ص�����  para�ص�����  time_mode��ʱ����ģʽ
- ���ڲ���:  ��
- ��ע    �� ��mainʹ��
*/
void TimeAStartSet(INT32U time_out,INT8U* prio_timnum,timefuc time_fuction,void* para,INT8U time_mode)
{
  static int initcnt = 0;
  
  if(!initcnt)
  {
    initcnt = 1;
    memset(TimeACnt,0,CNTLEN);
  }
  *prio_timnum = GetTimeANum();
  UseTimeMaxNum = *prio_timnum ;
  TimeACnt[*prio_timnum].TimeOut     = time_out;
  TimeACnt[*prio_timnum].TimeCnt     = time_out;
  TimeACnt[*prio_timnum].TimeMode    = time_mode;
  TimeACnt[*prio_timnum].TimeFuction = time_fuction;
  TimeACnt[*prio_timnum].Para        = para;
}

/*
-��������:  GetTimeOutFlag ��ȡ��ʱ�����־
-��ڲ���:  ��ǰ�����ʱ����
-���ڲ���:  1�������͹���� 0����δ�������
- ��ע    �� ��mainʹ��
*/
INT8U GetTimeOutFlag(INT8U prio_timenum)
{
  
  __disable_irq();
  if(TimeACnt[prio_timenum].TimeOutFlag&FLAGSETBIT(prio_timenum))
  {
    TimeACnt[prio_timenum].TimeOutFlag &= FLAGRESETBIT(prio_timenum);
    __enable_irq();
    return 1;
  }
  __enable_irq();
  return 0;
}

/*
-��������:  GetTimeOutSet ��ȡ��ʱʱ��
-��ڲ���:  ��ǰ�����ʱ����
-���ڲ���:  ��ʱʱ��
- ��ע    �� ��mainʹ��
*/
INT32U GetTimeSet(INT8U prio_timenum)
{
  return TimeACnt[prio_timenum].TimeOut;
}

/*
-��������:  GetProTime ��ȡ��ǰʱ��
-��ڲ���:  ��ǰ�����ʱ����
-���ڲ���:  ��ǰʱ��
- ��ע    �� ��mainʹ��
*/
INT32U GetProTime(INT8U prio_timenum)
{
  return TimeACnt[prio_timenum].TimeCnt;
}

/*���ö�ʱʱ��*/
void TimexTimeSet(INT8U prio_timenum , INT32U time_set)
{
  __disable_irq();
  TimeACnt[prio_timenum].TimeOut = time_set;
  TimeACnt[prio_timenum].TimeCnt = 0;
  __enable_irq();
}

/*ʧ�ܵ�ǰ��ʱ������*/
void TimexDis(INT8U prio_timenum)
{
  __disable_irq();
  TimeACnt[prio_timenum].TimeCnt = 0;
  __enable_irq();
}
/*ʹ�ܵ�ǰ��ʱ������*/
void TimexEn(INT8U prio_timenum , INT32U time_set)
{
  __disable_irq();
  if(time_set)
    TimeACnt[prio_timenum].TimeCnt = time_set;
  else
    TimeACnt[prio_timenum].TimeCnt = TimeACnt[prio_timenum].TimeOut;
  __enable_irq();
}

/*
- ��������:  �����ʱ���ж�,��ɸ������ʱ���Ķ�ʱ���̼��ص�����
- ��ڲ���:  ��ʱ���������־(��1λ)+�����ʱ�����(��31λ)
- ���ڲ���:  ��
- ��ע    �� ��interruptʹ��
*/
void IntTimeACnt(INT32U* timeout_flag)
{
  INT8U i;
  
  for(i=0;i<UseTimeMaxNum+1;i++)
  {
    if((TimeACnt[i].TimeCnt != 0)&&(TimeACnt[i].TimeCnt<TimeACnt[i].TimeOut+1))
    {
      TimeACnt[i].TimeCnt --;
      if(TimeACnt[i].TimeCnt == 0)
      {
        *timeout_flag = (1<<31)+i;
        TimeACnt[i].TimeOutFlag |= FLAGSETBIT(i);
        if(TimeACnt[i].TimeMode == TIME_MODE_CYCLE)//ѭ������ģʽ��Ҫ�������ü���
        {
          TimeACnt[i].TimeCnt = TimeACnt[i].TimeOut;
        }
//        TimeACnt[i].TimeFuction(TimeACnt[i].Para);        
      }
    }
  }
}