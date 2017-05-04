#include "stm32f10x.h"
#include "includes.h"
#include "queue.h"
#include "protocol.h"
#include "string.h"
#include "serve.h"
#include "stdio.h"
#include  "rfdriver_reader.h"

#include "window_includes.h"
#include "lcdappshow.h"

#define __MYDEBUG 0x00

//#define VECT_TAB_OFFSET  0x0   �޸��ж�������ַ NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x08003000 );//0x3000
void FeedDog(void);

uint8_t ErrFlag = 0;

unsigned short mystrcmp(const char *a, const char *b, unsigned short n);
void uartSendMsg(INT8U channel, const INT8U* txbuf, INT8U ucbufLen);
INT8U ReadCardHandleFuction(const INT8U* pbuf);
void FeedDog(void);

extern INT8U uTargetAddr[6];
INT8U data_tcb[4] = {0x00,0x00,0x00,0x00};

INT8U KeyBusyStatus = 0;

volatile INT16U BackLightTime = 10;// 10*10*100
volatile INT16U ShutDownTime  = 1 ;// 1*600*100

void SYS_ClockCfg(void)
{
  ErrorStatus HSEStartUpStatus;
  
  RCC_DeInit();//������RCC�Ĵ�������Ϊȱʡֵ
  
  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);//�����ⲿ���پ���HSE ��
  
  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ�HSE ����,�ȴ��ⲿ��ʱ������
  
  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  //ʹ�ܻ���ʧ��Ԥȡָ����
    
    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);//���ô�����ʱֵ 
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHBʱ�ӣ�HCLK�� 
    
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);//���ø���AHBʱ�ӣ�PCLK2�� to APB2
    
    /* PCLK1 = HCLK/2 *///stm32��ʱ�ӱȽϸ���
    RCC_PCLK1Config(RCC_HCLK_Div2); //���ø���AHBʱ�ӣ�PCLK1��to APB1
    
    /* ADCCLK = PCLK2/8 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div8); //����ADCʱ�ӣ�ADCCLK)  
    
    /* PLLCLK = 8MHz * 9 = 72 MHz */
    //�����ⲿʱ��Դ����PLL�����ⲿʱ��Ƶ��*9
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    
    //��ʱPLLCLK =72MHz�������֪������ֵ����ΪUSB��ʱ��USBCLK = PLLCLK/1����PLLCLK/1.5������ȷ��USBCLK =48MHz
    
    //��������USBCLK��ʱ��ѡ����1.5��Ƶ
    RCC_PLLCmd(ENABLE);//���ż���PLL���������ż��
    
    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
    
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//����SYSCLK
    
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
  else
  {
    
    /* If HSE fails to start-up, the application will have wrong clock configuration.
    User can add here some code to deal with this error */   
    
    /* Go to infinite loop */
    while (1)
    {
    }
    
    
  }
}

int main(void)
{  
//  FeedDog();
  // ģ���ʼ��
//  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x08003000 );//0x3000
  
  OS_CPU_SysTickInit();   
  BSP_Init(); 
//  OS_CPU_SysTickInit(); 
//  SYS_ClockCfg();
    
  BSP_IntDisAll();
  
  FlashMsgInit();
  
  // ����ϵͳ
  OSInit();
  OSTaskCreate ((void (*)(void *))App_TaskStart, 
                (void *)0, 
                (OS_STK *)&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                (INT8U)APP_TASK_START_PRIO );   
  OSStart();
}

/*
-  ��������Ҫ��ɣ�
   1����������������ָʾ����
   2���������������������
      ���û�д�����������,��̶�ÿ����ʱ�䷢����λ�ź�
*/
void App_TaskStart(void* para)
{
  INT8U os_err;
  INT8U Qwindow_name;
  
  INT8U txdata_buf[60];
  char Qbutton_name[20];
  int Qvalue_buf[25];
  INT8U u8buf[25];
  unsigned char queue_data_len = 0;
  INT8U data_len;
  
  ByteTypeDef tmp_value;
  
#if (OS_TASK_STAT_EN > 0)
  OSStatInit();                                               
#endif
  
//  Rf_Vdd_Off();
//  LcdLightOff();
  LcdColse();
  
  WKUP_Init();  // �͹��� ��ʼ��
  OSSemNomarlCreate(KeyStandbySem); // �����ж��¼�,����͹����¼�
  
  OSSemPend (SemNormalTcb[KeyStandbySem],1500,&os_err);
  if(OS_ERR_NONE == os_err)
  {
    if(0 == IntCheckWakeUp())//�ػ�?//�ж�,��⵽ PA0 �ŵ�һ��������.//�ж��� 0 ���ϵ��жϼ��
    {
      Sys_Enter_Standby();
    }
  }
  if(OS_ERR_TIMEOUT == os_err)
  {
    Sys_Enter_Standby();
  }
  
  LCDKS0108_Initialize();// lcd init
  LcdLightOn();
  RX8025T_Init();
  
  GLCD_ShowLoGo();
  OSTimeDly (600);
  
  if(ErrFlag)
  {
    GLCD_TextGoTo(7, 5);
    GLCD_WriteAntiColorString("starting error");
  }
  else
  {
    GLCD_TextGoTo(7, 5);
    GLCD_WriteAntiColorString("starting");
  }

  OSTimeDly (90);
  
  ADC1_Config();
  GLCD_TextGoTo(0,7);
  GLCD_WriteAntiColorString("    ");
  OSTimeDly (80);
  
  GPIO_KeyConfInit();
  GLCD_WriteAntiColorString("    ");
  OSTimeDly (70);
  
  RfModeInit();
  Rf_Vdd_Off();
  GLCD_WriteAntiColorString("    ");
  OSTimeDly (60);
  
  GLCD_WriteAntiColorString("    ");
  OSTimeDly (50);
  FeedDog();
  
  GLCD_WriteAntiColorString("    ");
  OSTimeDly (40);
  
  MainInterfaceCreate((void*)0);   // ˢ�� ������
  
  FlashMsgInit();
  
  StandbyIntEnable();
  //  KeyScanEnable();      // ��������ɨ��
  RfRxIntEnable();     // ��������ģ��ͨ���ж�  
  //���� �ź�
  OSSemNomarlCreate(RfRxIntSem);     // ���߽����¼�
  OSSemNomarlCreate(UpdateEventSem); // ����¼�����ݸ����¼�
//  OSSemNomarlCreate(StandbySem);     // ����͹����¼�
  OSSemNomarlCreate(AutoGetAddrSem); // �����Զ���ȡĿ���ַ�¼�
  
  OSSemMutexCreate(LCDRefreshMutexSem);// LCD���������¼�
  
  FeedDog();
  FeedDog();
  
  OSTaskCreate ( (void (*)(void *))App_LcdShowRFMsgTask, 
                (void *)0, 
                (OS_STK *)&App_LcdShowRFStk[APP_LCD_SHOW_RFMSG_STK_SIZE - 1],
                (INT8U)APP_LCD_SHOWRF_CARD_PRIO );  
  
  OSTaskCreate ( (void (*)(void *))App_KeyScanTask, 
                (void *)0, 
                (OS_STK *)&App_KeyScanStk[APP_TASK_KEY_SCAN_STK_SIZE - 1],
                (INT8U)APP_TASK_KEY_SCAN_PRIO );    
  
  OSTaskCreate ( (void (*)(void *))App_RefreshEventTask, 
                (void *)0, 
                (OS_STK *)&App_RefreshEventStk[APP_RFFRESH_EVENT_STK_SIZE - 1],
                (INT8U)APP_TASK_RFFRESH_EVENT_PRIO );
  
//  OSTaskCreate ( (void (*)(void *))App_TaskIndicate, 
//                (void *)0, 
//                (OS_STK *)&App_TaskIndicateStk[APP_TASK_INDICATESTK_SIZE - 1],
//                (INT8U)APP_TASK_INDICATE_PRIO );
  
  OSTaskCreate ((void (*)(void *))App_TaskFeedDog, 
                (void *)0, 
                (OS_STK *)&App_TaskFeedDogStk[APP_TASK_FEEDDOG_STK_SIZE - 1],
                (INT8U)APP_TASK_FEEDDOG_PRIO );  
  while(1)
  {
    OSSemPend (SemNormalTcb[UpdateEventSem],0,&os_err); // ����ˢ�� ��д���Ӧģ�� (��дʱ�ӡ�д������TX�����)
    if(OS_ERR_NONE == os_err)
    {
      while(1 == LcdEventDelqueue(&Qwindow_name,Qbutton_name,Qvalue_buf,&queue_data_len))// ��ȡ�����е����� 
      {
        continue;
      } 
      // ���ݽ�������
      if(0 == strcmp(Qbutton_name,"TAID")) // Ŀ��id����
      {
        if(-1 != Qvalue_buf[0])
        {
          for(INT8U i=0;i<6;i ++)
          {
            tmp_value.bit4.bith = (*(Qvalue_buf+2*i) -0x30);
            tmp_value.bit4.bitl = (*(Qvalue_buf+2*i+1) -0x30);
            u8buf[5-i] = tmp_value.byte;
          }
          SetTargetAddress(u8buf);
        }
      }
      else if((TWO_INTERFACE(4) == Qwindow_name))
      {
        if(0 == strcmp(Qbutton_name,"DA")) // ��������
        {
          txdata_buf[0] = Qvalue_buf[2];
          txdata_buf[1] = Qvalue_buf[3];
          txdata_buf[2] = Qvalue_buf[4];
          txdata_buf[3] = Qvalue_buf[5];
          txdata_buf[4] = Qvalue_buf[6];
          txdata_buf[5] = Qvalue_buf[7];
          WriteDateReg(txdata_buf);
        }
        else if(0 == strcmp(Qbutton_name,"TI")) // ʱ������
        {
          txdata_buf[0] = Qvalue_buf[0];
          txdata_buf[1] = Qvalue_buf[1];
          txdata_buf[2] = Qvalue_buf[2];
          txdata_buf[3] = Qvalue_buf[3];
          txdata_buf[4] = Qvalue_buf[4];
          txdata_buf[5] = Qvalue_buf[5];
          SetTimeReg(txdata_buf);
        }
        else if(0 == strcmp(Qbutton_name,"BA")) // ����ʱ��
        {
          for(INT8U i=0;i<2;i ++)
          {
            tmp_value.bit4.bith = (*(Qvalue_buf+2*i) -0x30);
            tmp_value.bit4.bitl = (*(Qvalue_buf+2*i+1) -0x30);
            u8buf[1-i] = tmp_value.byte;
          }
          WriteMsgToFlash(u8buf,2,BACK_LIGHT_TIME);
        }
        else if(0 == strcmp(Qbutton_name,"SH")) // �ػ�ʱ��
        {
          for(INT8U i=0;i<2;i ++)
          {
            tmp_value.bit4.bith = (*(Qvalue_buf+2*i) -0x30);
            tmp_value.bit4.bitl = (*(Qvalue_buf+2*i+1) -0x30);
            u8buf[1-i] = tmp_value.byte;
          }
          WriteMsgToFlash(u8buf,2,SHUTOFF_TIME);
        }
        else if(0 == strcmp(Qbutton_name,"AD")) // ������ַ
        {
          for(INT8U i=0;i<2;i ++)  // ǰ4���ַ�(2���ֽڣ�Ϊ������ַ)
          {
            tmp_value.bit4.bith = (*(Qvalue_buf+2*i) -0x30);
            tmp_value.bit4.bitl = (*(Qvalue_buf+2*i+1) -0x30);
            u8buf[1-i] = tmp_value.byte;
          }
          WriteMsgToFlash(u8buf,2,LOCA_ADDR);
          for(INT8U i=0;i<4;i ++)  // ǰ8���ַ�(4���ֽڣ�Ϊ�����ߴ���)
          {
            tmp_value.bit4.bith = (*(Qvalue_buf+4+2*i) -0x30);
            tmp_value.bit4.bitl = (*(Qvalue_buf+4+2*i+1) -0x30);
            u8buf[3-i] = tmp_value.byte;
          }
          
          WriteMsgToFlash(u8buf,4,OPERATION_CODE);
          StorUserName((INT8U*)Qvalue_buf,8);
        }
        else
        {
          ;
        }
      }
      else if((TWO_INTERFACE(1) == Qwindow_name)||(TWO_INTERFACE(2) == Qwindow_name)) // ��ǰ��Ϣ���� // ��ʷ��Ϣ����
      {
        memset(data_tcb,0,4);
        if(TWO_INTERFACE(1) == Qwindow_name)
        {
          data_tcb[0] = 0x00;
        }
        else 
        {
          data_tcb[0] = GetStringNumberValue();
        }
        if(0 == strcmp(Qbutton_name,"AP")) // �ܹ���
        {
          data_tcb[2] = 0x00;
        }
        else if(0 == strcmp(Qbutton_name,"+P")) // ������
        {
          data_tcb[2] = 0x01;
        }
        else if(0 == strcmp(Qbutton_name,"-P"))
        {
          data_tcb[2] = 0x02;
        }
        else
        {
//          KeyBusyStatus = 0;
          goto LOOP1;
        }
        KeyBusyStatus = 1;
        Rf_Vdd_on();
        OSTimeDly (1000);
        for(INT8U i=0;i<5;i++)
        {
          if( -1 == Qvalue_buf[i])
          {
            KeyBusyStatus = 0;
            break;
          } 
          switch(Qvalue_buf[i])
          {
          case '0':
            data_tcb[1] = 0x00;
            break;
          case '1':
            data_tcb[1] = 0x01;
            break;
          case '2':
            data_tcb[1] = 0x02;
            break;
          case '3':
            data_tcb[1] = 0x03;
            break;
          case '4':
            data_tcb[1] = 0x04;
            break;
          default:
            break;
          } 
          memset(txdata_buf,0,sizeof(txdata_buf));
          RFSendMsgDataPackage(uTargetAddr,0x11,data_tcb,sizeof(data_tcb),txdata_buf,&data_len);//GetTargetAddress()
          if(data_len > 40) continue;
          USARTx_SenBufMsg(USART1,txdata_buf,data_len);
          IconOper(SEND,ICO_EN,50);
          OSTimeDly (700);
        }
        KeyBusyStatus = 0;
        Rf_Vdd_Off();
        OSTimeDly (10);
      }
      else if(TWO_INTERFACE(5) == Qwindow_name) // ��̴���
      {
        KeyBusyStatus = 1;
        memset(txdata_buf,0,sizeof(txdata_buf));
        for(INT8U i=0;i<queue_data_len;i++)
        {
          u8buf[i] = Qvalue_buf[i];
        }
        
        Rf_Vdd_on();
        OSTimeDly (1000);
        RFSendMsgDataPackage(uTargetAddr,0x14,u8buf,queue_data_len,txdata_buf,&data_len);
        USARTx_SenBufMsg(USART1,txdata_buf,data_len);
        IconOper(SEND,ICO_EN,50);
        OSTimeDly (700);
        KeyBusyStatus = 0;
        Rf_Vdd_Off();
        OSTimeDly (10);
      }
      else if(TREE_INTERFACE(2))  // ���������¼�
      {
        KeyBusyStatus = 1;
        Rf_Vdd_on();
        OSTimeDly (1000);
        memset(u8buf,0xAA,6);
        RFSendMsgDataPackage(u8buf,0x13,(void*)0,0,txdata_buf,&data_len);
        USARTx_SenBufMsg(USART1,txdata_buf,data_len);
        IconOper(SEND,ICO_EN,50);
        OSTimeDly (700);
        KeyBusyStatus = 0;
        Rf_Vdd_Off();
        OSTimeDly (10);
      }
      else
      {
        ;
      }
    }

  LOOP1:
//    KeyBusyStatus = 0;
    OSTimeDly (100);
  }
}

extern strWindow HisActinveWindow;

void App_RefreshEventTask(void)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR         cpu_sr;
#endif 
  INT8U os_err;
  INT8U battery_refresh = 0; 
  INT8U pro_active_window;
  INT32U DelayCnt = 0;
  uint16_t integer;
  uint16_t decimal;
  char tmp_buf[21];
  INT8U tim_value[15];
  INT8U bcd_value[15];
  float ppower_electric;
  float prtc_electric;
  INT8U id_display = 0;
  ByteTypeDef* bit4_value;
  INT16U tmp_bcd_hex = 0;
  
  while(1)  // ҳ�涨ʱˢ��
  { 
    OSSemPend (SemMutexTcb[LCDRefreshMutexSem],0,&os_err);
    if(OS_ERR_NONE == os_err)
    {
      
      if(pro_active_window == GetActiveWindow())
      {
        if(!battery_refresh)
        {
          battery_refresh = 1;
          DelayCnt = 0;
        }
      }
      else
      {
        pro_active_window = GetActiveWindow();
        battery_refresh = 0;
      }
      
      if((TREE_INTERFACE(1) == pro_active_window)||(TREE_INTERFACE(2) == pro_active_window))
      {
        pro_active_window = HisActinveWindow.interface_name;
        id_display = 1;
      }
      else
      {
        id_display = 0;
      }
      
      switch(pro_active_window)
      {
      case MAIN_INTERFACE:
        {
          /*ʱ�����*/
          if(1 == ReadDateReg((INT8U*)tim_value))
          {
            sprintf(tmp_buf,"20%c%c/%c%c/%c%c",tim_value[0],tim_value[1],tim_value[2],tim_value[3],tim_value[4],tim_value[5]);
            WindowTaskRefreshEvent(tmp_buf,0,GetActiveWindow());
          }        
          if(1 == ReadTimeReg((INT8U*)tim_value))
          {
            sprintf(tmp_buf,"%c%c:%c%c:%c%c",tim_value[0],tim_value[1],tim_value[2],tim_value[3],tim_value[4],tim_value[5]);
            WindowTaskRefreshEvent(tmp_buf,1,GetActiveWindow());
          }
          break;
        }
      case TWO_INTERFACE(1):
        break;
      case TWO_INTERFACE(2):
        break;
      case TWO_INTERFACE(3):
        {
          
          CalculateSampleValues(&prtc_electric,&ppower_electric);
          
          if(0 == DelayCnt%50)// ��ص������
          {
            FloatChangeToInt(ppower_electric,&integer, &decimal);
            sprintf(tmp_buf,"%03d.%03dV",integer,decimal);//ppower_electric .3f
            WindowTaskRefreshEvent(tmp_buf,4,GetActiveWindow());
          }
          
          if(0 == DelayCnt%50)// ʱ�ӵ������
          {
            FloatChangeToInt(prtc_electric,&integer, &decimal);
            sprintf(tmp_buf,"%03d.%03dV",integer,decimal);//ppower_electric .3f
            WindowTaskRefreshEvent(tmp_buf,5,GetActiveWindow()); // ����ˢ���¼�
          }
          
          if(1 == id_display)
          {
            break;
          }
          // ����ID ����
          // ����IDˢ��
          memset(tim_value,0,sizeof(tim_value));
          ReadMsgFromFlash(tim_value,2,LOCA_ADDR);
          ReadMsgFromFlash(tim_value+2,4,OPERATION_CODE);
          HexToBCD(tim_value,6,bcd_value,&os_err);
          sprintf(tmp_buf,"%d%d%d%d%d%d%d%d%d%d%d%d",bcd_value[3],bcd_value[2],bcd_value[1],bcd_value[0]
                  ,bcd_value[11],bcd_value[10],bcd_value[9],bcd_value[8],bcd_value[7],bcd_value[6],bcd_value[5],bcd_value[4]);//ppower_electric .3f
          WindowTaskRefreshEvent(tmp_buf,3,GetActiveWindow());
          
          break;
        }
      case TWO_INTERFACE(4):
        {
          /*ʱ�����*/
          if(1 == ReadDateReg((INT8U*)tim_value))
          {
            sprintf(tmp_buf,"20%c%c/%c%c/%c%c",tim_value[0],tim_value[1],tim_value[2],tim_value[3],tim_value[4],tim_value[5]);
            WindowTaskRefreshEvent(tmp_buf,1,GetActiveWindow());
          }        
          if(1 == ReadTimeReg((INT8U*)tim_value))
          {
            sprintf(tmp_buf,"%c%c:%c%c:%c%c",tim_value[0],tim_value[1],tim_value[2],tim_value[3],tim_value[4],tim_value[5]);
            WindowTaskRefreshEvent(tmp_buf,2,GetActiveWindow());
          }
          
          if(1 == id_display)
          {
            break;
          }
          // ����ʱ�� ����
          memset(tim_value,0,sizeof(tim_value));
          ReadMsgFromFlash(tim_value,2,BACK_LIGHT_TIME);
          BackLightTime = (INT16U)((tim_value[1]<<8)+tim_value[0]);
          HexToBCD(tim_value,2,bcd_value,&os_err);
          sprintf(tmp_buf,"%d%d%d%d sec",bcd_value[3],bcd_value[2],bcd_value[1],bcd_value[0]);//ppower_electric .3f
          WindowTaskRefreshEvent(tmp_buf,3,GetActiveWindow());
          // ����ʱ�� ����
          memset(tim_value,0,sizeof(tim_value));
          ReadMsgFromFlash(tim_value,2,SHUTOFF_TIME);
          ShutDownTime = (INT16U)((tim_value[1]<<8)+tim_value[0]);
          HexToBCD(tim_value,2,bcd_value,&os_err);
          sprintf(tmp_buf,"%d%d%d%d min",bcd_value[3],bcd_value[2],bcd_value[1],bcd_value[0]);//ppower_electric .3f
          WindowTaskRefreshEvent(tmp_buf,4,GetActiveWindow());
          // ����IDˢ��
          memset(tim_value,0,sizeof(tim_value));
          ReadMsgFromFlash(tim_value,2,LOCA_ADDR);
          ReadMsgFromFlash(tim_value+2,4,OPERATION_CODE);
          HexToBCD(tim_value,6,bcd_value,&os_err);
          sprintf(tmp_buf,"%d%d%d%d%d%d%d%d%d%d%d%d",bcd_value[3],bcd_value[2],bcd_value[1],bcd_value[0]
                  ,bcd_value[11],bcd_value[10],bcd_value[9],bcd_value[8],bcd_value[7],bcd_value[6],bcd_value[5],bcd_value[4]);//ppower_electric .3f
          WindowTaskRefreshEvent(tmp_buf,5,GetActiveWindow());
          break;
        }
        break;
      default:
        break;
      }
      if(0 == DelayCnt%5)
      {
        AppCursorGlink();   // ���ˢ���¼�
        IcoGlintTaskEvent();// ͼ��ˢ���¼�
      }
    }
    while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
    
    CalculateSampleValues(&prtc_electric,&ppower_electric);// ��ص������ // ʱ�ӵ������
    
    if((ppower_electric < 2.6)||(prtc_electric < 2.6))
    {
      IconOper(BATTERY,ICO_EN,0xff);
      
      if(ppower_electric < 2.4)
      {
        OSTaskDel(APP_LCD_SHOWRF_CARD_PRIO);
        OSTaskDel(APP_TASK_KEY_SCAN_PRIO);
        OSTaskDel(APP_TASK_START_PRIO);
        GLCD_ClearScreen();
        GLCD_TextGoTo(5, 3);
        GLCD_WriteString("low power...");
        GLCD_TextGoTo(2, 4);
        GLCD_WriteString("dev will shutdown");
        OSTimeDly (1000);
        OSTimeDly (1000);
        OSTimeDly (1000);
        Sys_Enter_Standby();        
      }
    }
    else
    {
      IconOper(BATTERY,ICO_DIS,0xff);
    }
    
    // ����ʱ�� ����
    memset(tim_value,0,sizeof(tim_value));
    CPU_CRITICAL_ENTER();
    ReadMsgFromFlash(tim_value,2,BACK_LIGHT_TIME);
    CPU_CRITICAL_EXIT();
    bit4_value = (ByteTypeDef*)&tim_value[1];
    tmp_bcd_hex = ((INT16U)(bit4_value->bit4.bith))*1000 + ((INT16U)(bit4_value->bit4.bitl))*100;
    bit4_value = (ByteTypeDef*)&tim_value[0];
    tmp_bcd_hex += ((INT16U)(bit4_value->bit4.bith))*10 + ((INT16U)(bit4_value->bit4.bitl));
    BackLightTime = tmp_bcd_hex;

    // ����ʱ�� ����
    memset(tim_value,0,sizeof(tim_value));
    CPU_CRITICAL_ENTER();
    ReadMsgFromFlash(tim_value,2,SHUTOFF_TIME);
    CPU_CRITICAL_EXIT();
    bit4_value = (ByteTypeDef*)&tim_value[1];
    tmp_bcd_hex = ((INT16U)(bit4_value->bit4.bith))*1000 + ((INT16U)(bit4_value->bit4.bitl))*100;
    bit4_value = (ByteTypeDef*)&tim_value[0];
    tmp_bcd_hex += ((INT16U)(bit4_value->bit4.bith))*10 + ((INT16U)(bit4_value->bit4.bitl));
    ShutDownTime = tmp_bcd_hex;
    
    DelayCnt ++;
    FeedDog();
    OSTimeDly (100);
  }
}

void  App_KeyScanTask (void *p_arg)
{
  INT8U os_err;
  INT16U key_value;
  INT16U cnt_lcd_light=0;
  INT8U lcd_light_status = 0;
  
  while(1)
  {
    if(OSSemAccept (SemNormalTcb[KeyStandbySem]))
    {
      if(IntCheckWakeUp())//�ػ�?//�ж�,��⵽ PA0 �ŵ�һ��������.//�ж��� 0 ���ϵ��жϼ��
      {
        OSTaskDel(APP_LCD_SHOWRF_CARD_PRIO);
//        OSTaskDel(APP_TASK_KEY_SCAN_PRIO);
        OSTaskDel(APP_TASK_RFFRESH_EVENT_PRIO);
        OSTaskDel(APP_TASK_START_PRIO);
        OSTimeDly (1000);
  
        GLCD_ClearScreen();
        GLCD_ShowLoGo();
        OSTimeDly (500);
        
        GLCD_TextGoTo(7, 5);
        GLCD_WriteAntiColorString("shut down");
        OSTimeDly (90);
        
        GLCD_TextGoTo(0,7);
        GLCD_WriteAntiColorString(" ");
        OSTimeDly (80);
        
        GLCD_WriteAntiColorString("    ");
        OSTimeDly (70);
        
        GLCD_WriteAntiColorString("    ");
        OSTimeDly (60);
        
        GLCD_WriteAntiColorString("    ");
        OSTimeDly (50);
        
        GLCD_WriteAntiColorString("    ");
        OSTimeDly (40);

        GLCD_WriteAntiColorString("    ");
        OSTimeDly (30);
        
        Sys_Enter_Standby();
      }
      else
      {
        lcd_light_status = ~lcd_light_status;
        if(lcd_light_status) // ����һ�ι���
        {
          LcdLightOff();
        }
        else                 // �ٵ���һ�ο���
        {
          cnt_lcd_light=0;    // ʹ�ܿ��������¼���
          LcdLightOn();
        }
      }
    }
    
    OSSemPend (SemMutexTcb[LCDRefreshMutexSem],0,&os_err);
    if(!KeyBusyStatus)
    {
      if(OS_ERR_NONE == os_err)
      {    
        key_value = CaptureKeyNum(OSTimeDly);
        if(0 != key_value) 
        {
          cnt_lcd_light = 0;
          EventResponseHander(key_value);
        }
      } 
    }

    if((0==lcd_light_status)&&(!cnt_lcd_light))
    {
      LcdLightOn();
    }
    
    cnt_lcd_light++;
    if(cnt_lcd_light > BackLightTime*10L) // 1xNs�ص�
    {
      if(0 != BackLightTime)
        LcdLightOff();
    }
    
    if(cnt_lcd_light > ShutDownTime*600L) // 60xN s �޲����ػ�
    {
      if(0 != ShutDownTime)
        Sys_Enter_Standby();
    }
    
    while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
    
    OSTimeDly (100);
  }
}

INT8U data[RF_ELEMENT];
void  App_LcdShowRFMsgTask (void *p_arg)
{
  INT8U os_err;
  INT8U cmd;
//  INT32U dmark;
  char tmp_buf[21];
  INT8U dlen;
  INT8U rdlen;
  
  while(1)
  {
    OSSemPend (SemNormalTcb[RfRxIntSem],0,&os_err);
    
    if(OS_ERR_NONE == os_err)
    {
      memset(data,0,sizeof(data));
      OSSemPend (SemMutexTcb[LCDRefreshMutexSem],0,&os_err);
      if(OS_ERR_NONE == os_err)
      {
      while(!RfEventDelqueue(&cmd,data,&dlen))
      {
        switch(cmd)
        {
        case 0x91:  // ��ȡ ��ǰ��Ϣ
          {
            if(8 != dlen) break;  // �ж����ݳ���
            HexToBCD(data+4,dlen,(INT8U*)tmp_buf,&rdlen);
            sprintf(tmp_buf,"%d%d%d%d%d%d.%d%d kWh",tmp_buf[7],tmp_buf[6],tmp_buf[5],tmp_buf[4],tmp_buf[3],tmp_buf[2],tmp_buf[1],tmp_buf[0]);
//            OSSemPend (SemMutexTcb[LCDRefreshMutexSem],0,&os_err);
//            if(OS_ERR_NONE == os_err)
//            {
              if((TWO_INTERFACE(1) != GetActiveWindow())&&(TWO_INTERFACE(2) != GetActiveWindow()))
              {
//                while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
                break;// �жϽ���
              } 
//              dlen = dmark>>8; //0x00000000  0x00000100 0x00000200 0x00000300 0x00000400
              if(dlen > 8) break;
              WindowTaskRefreshEvent(tmp_buf,data[1]+1,GetActiveWindow());
//            }
//            while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
          }
          break;
        case 0x93:
          HexToBCD(data,dlen,(INT8U*)tmp_buf,&rdlen);
          sprintf(tmp_buf," %d%d %d%d %d%d %d%d %d%d %d%d",tmp_buf[11],tmp_buf[10],tmp_buf[9],tmp_buf[8],
                  tmp_buf[7],tmp_buf[6],tmp_buf[5],tmp_buf[4],tmp_buf[3],tmp_buf[2],tmp_buf[1],tmp_buf[0]);
//          OSSemPend (SemMutexTcb[LCDRefreshMutexSem],0,&os_err);
//          if(OS_ERR_NONE == os_err)
//          {
            if(TREE_INTERFACE(2) != GetActiveWindow())
            {
//              while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
              break;// �жϽ���
            } 
            SetTargetAddress(data);
            PrintfStringToWindowEvent(tmp_buf,1,5);
//          }
//          while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
          break;
        case 0x94:
          break;
        case 0xD1:
        case 0xD4:
          IconOper(WARING,ICO_EN,10);
          break;
        default:
          break;
        }
        
        IconOper(SEND,ICO_DIS,0xff);
        
        OSTimeDly (30);
      }
    }
    
    }
    while(OS_ERR_NONE != OSSemPost (SemMutexTcb[LCDRefreshMutexSem]));
    OSTimeDly (100);
  }
}

void App_TaskFeedDog(void *p_arg)
{
//#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
//  CPU_SR         cpu_sr;
//#endif 
  
  while(1)
  {
    FeedDog();
    OSTimeDly (100);
  }
}

/*
-  ��������Ҫ��ɣ�
   1������ָʾ����
*/
void  App_TaskIndicate (void *p_arg)
{  
  while(1)
  {
    OSTimeDly (1000);    
  }
}

void FeedDog(void)
{
  static INT8U init = 0;
#if __MYDEBUG == 0
  if(!init)
  {
    init = 1;
    Wdt_Init();//WDG_SP706_GPIO_Configration();WDG_SP706_Enable();
  }
  else
  {
    Kick_Dog();//WDG_SP706_Feed();
  }
#else
  init = init;
#endif
}