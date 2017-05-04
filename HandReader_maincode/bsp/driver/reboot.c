#include  "reboot.h"
#include "usartdriver.h"
#include "KS0108.h"

#define RCC_APB2Periph_WATCHDOG     RCC_APB2Periph_GPIOA
#define GPIOWATCHDOG                GPIOA
#define WATCHDOGPIN                 GPIO_Pin_12

void  reboot (void)
{
  while(1)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(65);
    WWDG_Enable(0x3f); 
    WWDG_SetWindowValue(65);
    WWDG_Enable(0x3f);
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(65);
    WWDG_Enable(0x3f); 
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    WWDG_SetWindowValue(65);
    WWDG_Enable(0x3f);
  }
}

void Wdt_Init(void)
{
  // Enable write access to IWDG_PR and IWDG_RLR registers 
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //IWDG->KR = 0x5555
  // IWDG counter clock: 40KHz(LSI) / 64 = 0.625 KHz 
  IWDG_SetPrescaler(IWDG_Prescaler_32);   
  // Set counter reload value to 1250 
  IWDG_SetReload(0xFFF);           //IWDG->RLR =0xFFF
  //Red IWDG counter
  IWDG_ReloadCounter();   //IWDG->KR = 0xAAAA
  // Enable IWDG (the LSI oscillator will be enabled by hardware) 
  IWDG_Enable();   //IWDG->KR = 0xCCCC
  
}

//ι�� 
void Kick_Dog(void)
{
  //Reload IWDG counter 
  IWDG_ReloadCounter();   //IWDG->KR = 0xAAAA          
} 

///*
//SP706 �� Exar��ԭ Sipex����˾�Ƴ��ĵ͹��ġ��߿ɿ����ͼ۸�� MCU��λ���оƬ��
//��������ؼ����ԣ� 
//z  ��Ϊ 4 �����ͺţ�SP706P��SP706R��SP706S��SP706T 
//z  ��λ�����PΪ�ߵ�ƽ��Ч��R/S/T Ϊ�͵�ƽ��Ч 
//z  ���ܵĵ͵�ѹ��أ�P/RΪ 2.63V��SΪ 2.93V��TΪ 3.08V 
//z  ��λ�����ȣ�200ms���ֵ�� 
//z  �����Ŀ��Ź���ʱ����1.6 �볬ʱ���ֵ�� 
//z  ȥ�� TTL/CMOS �ֶ���λ���루/MR �ܽţ� 
//*/
//void WDG_SP706_GPIO_Configration(void)
//{
//  GPIO_InitTypeDef  gpio_init;
//  
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_WATCHDOG, ENABLE);
//  
//  gpio_init.GPIO_Pin   = WATCHDOGPIN;
//  gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
//  gpio_init.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOWATCHDOG, &gpio_init);	
//}
//
//void WDG_SP706_Enable(void)
//{
//  GPIO_InitTypeDef  gpio_init;
//  
//  gpio_init.GPIO_Pin   = WATCHDOGPIN;
//  gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIOWATCHDOG, &gpio_init);
//}
//
//void WDG_SP706_Feed(void)
//{
//  u8 reg_val;
//  reg_val = GPIO_ReadOutputDataBit(GPIOWATCHDOG , WATCHDOGPIN);
//  if(reg_val == 1)
//  {
//    GPIO_ResetBits(GPIOWATCHDOG, WATCHDOGPIN);
//    return;
//  }
//  GPIO_SetBits(GPIOWATCHDOG, WATCHDOGPIN);   
//}

void Sys_Standby(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); //ʹ��PWR����ʱ��
  PWR_WakeUpPinCmd(ENABLE); //ʹ�ܻ��ѹܽŹ���
  PWR_EnterSTANDBYMode();  //���������STANDBY��ģʽ
}

//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{ 
  KS0108_LightOff();
  GLCD_WriteCommand(0x3E, 0);
  GLCD_WriteCommand(0x3E, 1);
  GLCD_WriteCommand(0x3E, 0);
  GLCD_WriteCommand(0x3E, 1);
  GLCD_WriteCommand(0x3E, 0);
  GLCD_WriteCommand(0x3E, 1);
  Rf_Vdd_Off();
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,DISABLE);  //��λ���� IO ��
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_USART1,DISABLE);  
  WKUP_Init();
  Sys_Standby();
}

//��� WKUP �ŵ��ź�
//����ֵ 1:�������� 3s ����
// 0:����Ĵ���
u8 IntCheckWakeUp(void)
{
  u8 t=0;
  u8 tx=0;//��¼�ɿ��Ĵ���
  while(1)
  {
    if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))//�Ѿ�������
    {
      t++;
      tx=0;
    }
    else
    {
      tx++; //���� 1000ms ��û�� WKUP �ź�
      if(tx>5)
      {
        return 0;//����İ���,���´�������
      }
    }
    OSTimeDly (30);
//    delay_ms(30);
    if(t>=100)//���³��� 3 ����
    {
      return 1; //���� 3s ������
    }
  }
}

//PA0 WKUP ���ѳ�ʼ��
void WKUP_Init(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);//ʹ�� GPIOA �͸��ù���ʱ��

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_0;  //PA.0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������GPIO_Mode_IN_FLOATING;//
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� IO
  //ʹ���ⲿ�жϷ�ʽ
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
  //�ж��� 0 ���� GPIOA.0
  EXTI_InitStructure.EXTI_Line = EXTI_Line0; //���ð������е��ⲿ��·
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //�����ⲿ�ж�ģ
  //ʽ:EXTI ��·Ϊ�ж�����
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//EXTI_Trigger_Rising; //�����ش���EXTI_Trigger_Rising_Falling;//
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); // ��ʼ���ⲿ�ж�
  
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ� 2 ��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; //�����ȼ� 2 ��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ�� NVIC
  
//  BSP_IntVectSet(BSP_INT_ID_EXTI0, BSP_IntHandlerEXTI0); 
//  BSP_IntPrioSet(BSP_INT_ID_EXTI0,2);   
//  BSP_IntEn(BSP_INT_ID_EXTI0);
//  
//  PWR_ClearFlag(PWR_FLAG_SB);//StandBy flag
  
//  if(IntCheckWakeUp()==0) 
//  {
//    Sys_Standby(); //���ǿ���,�������ģʽ
//  }
}

void StandbyIntEnable(void)
{
  BSP_IntEn(BSP_INT_ID_EXTI0);
}