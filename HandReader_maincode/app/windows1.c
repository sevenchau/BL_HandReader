#include "windows1.h"
#include "lcdappshow.h"

BUT_TypeDef ActiveTcb[ACTIVE_NUM];

strWindow  HisActinveWindow; // ��ʷ�����
strContro  HisActiveContro; //  ��ʷ��ؼ�

pfuc fTiggerEventHook[CONTORL_NUM];//�����¼��ҹ�

strWindow sMainWindow;
strContro sMainControBuf[CONTORL_NUM];
/*�����˸*/
void AppCursorGlink(void)
{
  CursorGlink();
}
//-------------------------------------------------------------------------------------------------
// Clears screen
//-------------------------------------------------------------------------------------------------
void GLCD_ClearScreen(void)
{
  unsigned char i, j;
  for(j = 0; j < KS0108_SCREEN_HEIGHT/8; j++)
  {
    GLCD_GoTo(0,j);
    for(i = 0; i < KS0108_SCREEN_WIDTH; i++)
      GLCD_WriteData(0x00);
  }
}

/*��ʾ��˾logo*/
void GLCD_ShowLoGo(void)
{
  GLCD_Bitmap((char*)gImage_LOGO,0,0,46,50);
  GLCD_Bitmap((char*)gImage_yunengyibiao,40,0,81,38);
  GLCD_Bitmap((char*)gImage_nanjynybkjyxgs,0,46,121,18);

  GLCD_Line(45, 32,120,32);  
  GLCD_Line(45, 33,120,33);
  GLCD_Line(45, 34,120,34);
  GLCD_Line(45, 35,120,35);
  GLCD_Line(45, 36,120,36);

  GLCD_TextGoTo(13, 5);
  GLCD_WriteString("Co.,Ltd.");
  
  IcoInit();
}

/*
********************************************************************************
                      һ��������
********************************************************************************
*/
// һ�������洰�� ����
void MainInterFrameCreate(void* para)
{
  para = para;
  
  GLCD_Bitmap((char*)gImage_TIME,0,0,33,16);
  
  
  GLCD_Line(0, 18,128,18);  
  GLCD_Line(0, 19,128,19);
  GLCD_Line(0, 20,128,20);
  
  GLCD_Line(0, 60,128,60);
  GLCD_Line(0, 61,128,61);
  GLCD_Line(0, 62,128,62);  
  
  IcoInit();
}

//  һ������ؼ�����
void MainControlsMsgCreate(void* para)
{
  switch(*((unsigned char*)para))
  {
  case 1:
    GLCD_Bitmap((char*)gImage_now_msg,0,5*7,32,32);
    break;
  case 2:
    GLCD_Bitmap((char*)gImage_stor_msg,32,5*7,32,32);
    break;
  case 3:
    GLCD_Bitmap((char*)gImage_loca_msg,64,5*7,32,32);//GLCD_Bitmap GLCD_BitmapAntiColor
    break;
  case 4:
    GLCD_Bitmap((char*)gImage_cfg_msg,96,5*7,32,32);
    break;
  default:
    break;
  }
}

/*һ������ؼ��¼�*/
void MainControlEventTrigger(void* para)
{
  strContro* active_contorl;
  strWindow* active_interface;
  
  active_contorl = (strContro*)para; // ��ؼ�
  active_interface = &sMainWindow; // �����
  
  if((active_contorl->contorl_addrx == active_interface->pctrpoint_tcb[0].contorl_addrx)
     &&(active_contorl->contorl_addry == active_interface->pctrpoint_tcb[0].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_BitmapAntiColor((char*)gImage_now_msg,0,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_now_msg,0,5*7,32,32);
      break;
    case TIGGER_EVNT:
      fTiggerEventHook[0](para);
      break;
    }
  }
  else if((active_contorl->contorl_addrx == active_interface->pctrpoint_tcb[1].contorl_addrx)
          &&(active_contorl->contorl_addry == active_interface->pctrpoint_tcb[1].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_BitmapAntiColor((char*)gImage_stor_msg,32,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_stor_msg,32,5*7,32,32);
      break;
    case TIGGER_EVNT:
      fTiggerEventHook[1](para);
      break;
    }
  }
  else if((active_contorl->contorl_addrx == active_interface->pctrpoint_tcb[2].contorl_addrx)
          &&(active_contorl->contorl_addry == active_interface->pctrpoint_tcb[2].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_BitmapAntiColor((char*)gImage_loca_msg,64,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_loca_msg,64,5*7,32,32);
      break;
    case TIGGER_EVNT:
      fTiggerEventHook[2](para);
      break;
    }
  }
  else if((active_contorl->contorl_addrx == active_interface->pctrpoint_tcb[3].contorl_addrx)
          &&(active_contorl->contorl_addry == active_interface->pctrpoint_tcb[3].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_BitmapAntiColor((char*)gImage_cfg_msg,96,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_cfg_msg,96,5*7,32,32);
      break;
    case TIGGER_EVNT:
      fTiggerEventHook[3](para);
      break;
    }
  }
}

/*����һ��������*/
void MainInterfaceCreate(void* para)
{
  unsigned char i;
  unsigned char addr_i;
  strWindow* psMainWindow;
  strContro*    pstrContro;
  
  GLCD_ClearScreen();
  
  memset(&sMainWindow,0,sizeof(sMainWindow));
  memset(sMainControBuf,0,sizeof(sMainControBuf));
  
  psMainWindow = &sMainWindow;
  psMainWindow->interface_name = MAIN_INTERFACE;
  psMainWindow->interface_father = (void*)0;
  psMainWindow->pctrpoint_tcb = sMainControBuf;
  psMainWindow->interface_create = MainInterFrameCreate;
  psMainWindow->cursor_addrx = 0;
  psMainWindow->cursor_addry = 0;
  psMainWindow->cursor_addr_max = CONTORL_NUM;
  
  psMainWindow->interface_create((void*)0);     // ������������
  
  fTiggerEventHook[0] = CurSecondLevelInterfaceCreate;
  fTiggerEventHook[1] = StorySecondLevelInterfaceCreate;
  fTiggerEventHook[2] = LocalSecondLevelInterfaceCreate;
  fTiggerEventHook[3] = CfgSecondLevelInterfaceCreate;
  
  // �ؼ����켰���� (1,x) (2,x) (3,x) (4,x)   x ��ʾֻ���в������α�ֻ�������˶������˶���Ч
  // (1,x) ��ǰ��Ϣ�ؼ�   (2,x)��ʷ��Ϣ�ؼ�  (3,x)������Ϣ�ؼ�   (4,x)������Ϣ�ؼ�
  for(i=0;i<psMainWindow->cursor_addr_max;i++)
  {
    pstrContro = &sMainControBuf[i];
    pstrContro->type = __BUTTON;
    pstrContro->status = UNSELECT;
    pstrContro->contorl_addrx = (i+1);
    pstrContro->contorl_addry = Y_MOVE_DISABLE;
    pstrContro->control_create = MainControlsMsgCreate; // �ؼ�����
    pstrContro->event_trigger  = MainControlEventTrigger;// �ؼ���Ӧ�¼�
    
    addr_i = i+1;
    psMainWindow->pctrpoint_tcb[i].control_create((void*)&addr_i);// ��������
  }
  
  IcoInit();
}

/*
********************************************************************************
                      end of һ��������
********************************************************************************
*/


/*
********************************************************************************
                      ���������� ������Ϣ
********************************************************************************
*/
static char UserName[10] = "00000000";
static char PasserWord[10] = "00000002";
static char DataMarked[10] = "00000000";
static char TxNumber[22] = "00000000000000000000";
static char TxNuLen = 20;

static char show_pass_word = 0;

void StorUserName(INT8U* pvalue,INT8U len)
{
  for(INT8U i=0;i<len;i++)
  {
    UserName[i] = *(pvalue+i);
  }
}

static INT8U tmp_name[10];
static INT8U bcd_value[15];
void ShowUserName(char* puser_name,INT8U* len)
{
  ReadMsgFromFlash(tmp_name,4,OPERATION_CODE);
  HexToBCD(tmp_name,4,bcd_value,len);
  sprintf(puser_name,"%d%d%d%d%d%d%d%d"
          ,bcd_value[7],bcd_value[6],bcd_value[5],bcd_value[4],bcd_value[3],bcd_value[2],bcd_value[1],bcd_value[0]);
}

//  һ������ؼ�����
void ProgramControlsMsgCreate(void* para)
{
  switch(*((unsigned char*)para))
  {
  case 1:
    GLCD_Bitmap((char*)gImage_sendmsg,0,5*7,32,32);
    break;
  case 2:
    GLCD_Bitmap((char*)gImage_datamark,32,5*7,32,32);
    break;
  case 3:
    GLCD_Bitmap((char*)gImage_usercode,64,5*7,32,32);
    break;
  case 4:
    GLCD_Bitmap((char*)gImage_password,96,5*7,32,32);
    break;
  default:
    break;
  }
}

/*һ������ؼ��¼�*/
void ProgramControlEventTrigger(void* para)
{
  INT8U len;
  strContro* active_contorl;
  
  ByteTypeDef tmp_value;
  BUT_TypeDef tigger_event;
  strWindow* active_window;
  
  active_contorl = (strContro*)para; // ��ؼ�
  active_window  = &sMainWindow;
  
  if((active_contorl->contorl_addrx == active_window->pctrpoint_tcb[0].contorl_addrx)
     &&(active_contorl->contorl_addry == active_window->pctrpoint_tcb[0].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_ClearScreenLiney(1);
      if(TxNuLen > 18)
      {
        GLCD_TextGoTo(0,1);
        GLCD_WriteString("TX:");
        OSTimeDly (200);
        GLCD_TextGoTo(0,1);
        GLCD_WriteString(TxNumber);
      }
      else
      {
        GLCD_TextGoTo(0,1);
        GLCD_WriteString("TX:");
        TxNumber[TxNuLen] = 0;
        GLCD_WriteString(TxNumber);
      }
      GLCD_BitmapAntiColor((char*)gImage_sendmsg,0,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_sendmsg,0,5*7,32,32);
      break;
    case TIGGER_EVNT:
      {
        tigger_event.active_window = active_window->interface_name;
        tigger_event.pactive_button_name = active_contorl->cchar_name;
        memset(&tigger_event.date_tcb,-1,sizeof(tigger_event.date_tcb));
        //DIo DI1 DI2 DI3 PA Pol Pl P2 Co C1 C2 C3 N1 N2 ...Nm  ˳��Ϊ������ʱ���ڸߵ��ڵͣ�����ʱ��λ�ȷ���
        
        // �ȱ��� ���ݱ�ʾ ��4���ֽڣ����ֽڱ�����ǰ��
        for(INT8U i=0;i<4;i++)
        {
          tmp_value.bit4.bith = *(DataMarked+2*i)-0x30;
          tmp_value.bit4.bitl = *(DataMarked+2*i+1)-0x30;
          
          tigger_event.date_tcb[3-i] = tmp_value.byte;
        }
        // �������� ��4���ֽڣ����ֽڱ�����ǰ��
        for(INT8U i=0;i<4;i++)
        {
          tmp_value.bit4.bith = *(PasserWord+2*i)-0x30;
          tmp_value.bit4.bitl = *(PasserWord+2*i+1)-0x30;
          
          tigger_event.date_tcb[7-i] = tmp_value.byte;
        }
        // ��������ߴ��� ��4���ֽڣ����ֽڱ�����ǰ��
        for(INT8U i=0;i<4;i++)
        {
          tmp_value.bit4.bith = *(UserName+2*i)-0x30;
          tmp_value.bit4.bitl = *(UserName+2*i+1)-0x30;
          
          tigger_event.date_tcb[11-i] = tmp_value.byte;
        }
        // �������ݲ���  ���ֽڱ�����ǰ��
        for(INT8U i=0;i<TxNuLen;i++)
        {
          //        tmp_value.bit4.bith = *(TxNumber+2*i)-0x30;
          //        tmp_value.bit4.bitl = *(TxNumber+2*i+1)-0x30;
          
          tigger_event.date_tcb[11+TxNuLen-i] = TxNumber[i];//tmp_value.byte;
        }
        // �������ݳ���
        tigger_event.data_len = 4+4+4+TxNuLen;
        //    memcpy(tigger_event.date_tcb,GetLcdData(),BUF_LEN);
        
//        GLCD_ClearScreenLiney(1);
//        if(TxNuLen > 18)
//        {
//          GLCD_TextGoTo(0,1);
//          GLCD_WriteString("TX:");
//          OSTimeDly (200);
//          GLCD_TextGoTo(0,1);
//          GLCD_WriteString(TxNumber);
//        }
//        else
//        {
//          GLCD_TextGoTo(0,1);
//          GLCD_WriteString("TX:");
//          TxNumber[TxNuLen] = 0;
//          GLCD_WriteString(TxNumber);
//        }
        
        if(LcdEventEnqueue(&tigger_event)) // ���뻺����,�������ź�
        {
          OSSemPost (SemNormalTcb[UpdateEventSem]);
          IconOper(WARING,ICO_EN,5);
          break;
        }
        IconOper(HOME,ICO_EN,5);
        OSSemPost (SemNormalTcb[UpdateEventSem]);
        break;
      }
      break;
    }
  }
  else if((active_contorl->contorl_addrx == active_window->pctrpoint_tcb[1].contorl_addrx)
          &&(active_contorl->contorl_addry == active_window->pctrpoint_tcb[1].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_ClearScreenLiney(1);
      GLCD_TextGoTo(0,1);
      GLCD_WriteString("DATEMARK:");
      GLCD_WriteString(DataMarked);
      GLCD_BitmapAntiColor((char*)gImage_datamark,32,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_datamark,32,5*7,32,32);
      break;
    case TIGGER_EVNT:
//      GLCD_ClearScreenLiney(1);
//      GLCD_TextGoTo(0,1);
//      GLCD_WriteString("DATEMARK:");
//      GLCD_WriteString(DataMarked);
      IconOper(HOME,ICO_EN,5);
      break;
    }
  }
  else if((active_contorl->contorl_addrx == active_window->pctrpoint_tcb[2].contorl_addrx)
          &&(active_contorl->contorl_addry == active_window->pctrpoint_tcb[2].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_ClearScreenLiney(1);
      GLCD_TextGoTo(0,1);
      GLCD_WriteString("USERCODE:");
      ShowUserName(UserName,&len);
      GLCD_WriteString(UserName);
      GLCD_BitmapAntiColor((char*)gImage_usercode,64,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_usercode,64,5*7,32,32);
      break;
    case TIGGER_EVNT:
//      GLCD_ClearScreenLiney(1);
//      GLCD_TextGoTo(0,1);
//      GLCD_WriteString("USERCODE:");
//      ShowUserName(UserName,&len);
//      GLCD_WriteString(UserName);
      IconOper(HOME,ICO_EN,5);
      break;
    }
  }
  else if((active_contorl->contorl_addrx == active_window->pctrpoint_tcb[3].contorl_addrx)
          &&(active_contorl->contorl_addry == active_window->pctrpoint_tcb[3].contorl_addry))
  {
    switch(active_contorl->status)
    {
    case SELECT:
      GLCD_ClearScreenLiney(1);
      GLCD_TextGoTo(0,1);
      GLCD_WriteString("PASSWORD:");
      GLCD_WriteString("************");
      GLCD_BitmapAntiColor((char*)gImage_password,96,5*7,32,32);
      break;
    case UNSELECT:
      GLCD_Bitmap((char*)gImage_password,96,5*7,32,32);
      break;
    case TIGGER_EVNT:
      GLCD_ClearScreenLiney(1);
      GLCD_TextGoTo(0,1);
      GLCD_WriteString("PASSWORD:");
      if(show_pass_word)
      {
        show_pass_word = 0;
        GLCD_WriteString(PasserWord);
        OSTimeDly (100);
//        GLCD_TextGoTo(9,1);
//        GLCD_WriteString("************");
      }
//      else
//      {
//        GLCD_WriteString("************");
//      }
      IconOper(HOME,ICO_EN,5);
      break;
    }
  }
}


void ChangeInfomationFromInput(void)
{
  INT8U i;
  strContro* hisactive_contorl;
  hisactive_contorl = &HisActiveContro;
  ByteTypeDef tmp_value;
  INT8U u8buf[4];
  
  switch(hisactive_contorl->contorl_addrx)
  {
  case 3:
    {
      for( i=0;i<8;i++)
      {
        if(-1 == *(GetLcdData()+i+1))break;
        UserName[i] = *(GetLcdData()+i+1);
      }
      if(i != 8) 
      {
        OK_Status = 1;
        return;
      }
      for(INT8U i=0;i<4;i ++)  // ǰ8���ַ�(4���ֽڣ�Ϊ�����ߴ���)
      {
        tmp_value.bit4.bith = (*(UserName+2*i) -0x30);
        tmp_value.bit4.bitl = (*(UserName+2*i+1) -0x30);
        u8buf[3-i] = tmp_value.byte;
      }
      WriteMsgToFlash(u8buf,4,OPERATION_CODE); // ��flash
      OK_Status = 0;
      return;
    }
  case 4:
    {
      for(i=0;i<8;i++)
      {
        if(-1 == *(GetLcdData()+i+1))break;
        PasserWord[i] = *(GetLcdData()+i+1);
        show_pass_word = 1;
      }
      if(i != 8) 
      {
        OK_Status = 1;
        return;
      } 
      OK_Status = 0;
      return;
    }
  case 2:
    {
      for(i=0;i<8;i++)
      {
        if(-1 == *(GetLcdData()+i+1))break;
        DataMarked[i] = *(GetLcdData()+i+1);
      }
      if(i != 8) 
      {
        OK_Status = 1;
        return;
      } 
      OK_Status = 0;
      return;
    }
  case 1:
    {
      memset(TxNumber,' ',20);
      for(i=0;i<20;i++)
      {
        if(-1 == *(GetLcdData()+i+1))break;
        TxNumber[i] = *(GetLcdData()+i+1);
      }
//      if(i%2) {OK_Status = 1;return;} // ¼������ݱ���Ϊż����
      TxNuLen = i;
      OK_Status = 0;
      break;
    }
  }
}

void SendMsgWindowFrameCreate(void* para)
{
  strContro* tmp_para;
  INT8U len;
  
  tmp_para = (strContro*)para;
  
  GLCD_Line(0, 1*8-5,128,1*8-5); 
  
  if(MAIN_INTERFACE == HisActinveWindow.interface_name)
  {
    GLCD_TextGoTo(0,1);
    GLCD_WriteString("    Program Window");    
  }
    
  GLCD_Line(0, 3*8-5,128,3*8-5);
  GLCD_Line(0, 3*8-4,128,3*8-4);
  GLCD_Line(0, 3*8-3,128,3*8-3);
  
  
  GLCD_Line(0, 60,128,60);
  GLCD_Line(0, 61,128,61);
  GLCD_Line(0, 62,128,62);  
  
  IcoInit();
}

/*�ؼ���Ӧ*/
void SendMsgControlEventTrigger(void* para)
{
  ByteTypeDef tmp_value;
  BUT_TypeDef tigger_event;
  strContro* active_contorl;
  strWindow* active_window;
  
  active_contorl = (strContro*)para; // ��ؼ�
  active_window  = &sMainWindow;
  
  switch(active_contorl->status)
  {
  case SELECT:
  	MainSecondLevelSelectEvent(para);
    break;
  case UNSELECT:
  	MainSecondLevelUnselectEvent(para);
    break;
  case TIGGER_EVNT:
    {
      if(4 != active_contorl->contorl_addrx) break;
      tigger_event.active_window = active_window->interface_name;
      tigger_event.pactive_button_name = active_contorl->cchar_name;
      memset(&tigger_event.date_tcb,-1,sizeof(tigger_event.date_tcb));
      //DIo DI1 DI2 DI3 PA Pol Pl P2 Co C1 C2 C3 N1 N2 ...Nm  ˳��Ϊ������ʱ���ڸߵ��ڵͣ�����ʱ��λ�ȷ���
      
      // �ȱ��� ���ݱ�ʾ ��4���ֽڣ����ֽڱ�����ǰ��
      for(INT8U i=0;i<4;i++)
      {
        tmp_value.bit4.bith = *(DataMarked+2*i)-0x30;
        tmp_value.bit4.bitl = *(DataMarked+2*i+1)-0x30;
        
        tigger_event.date_tcb[3-i] = tmp_value.byte;
      }
      // �������� ��4���ֽڣ����ֽڱ�����ǰ��
      for(INT8U i=0;i<4;i++)
      {
        tmp_value.bit4.bith = *(PasserWord+2*i)-0x30;
        tmp_value.bit4.bitl = *(PasserWord+2*i+1)-0x30;
        
        tigger_event.date_tcb[7-i] = tmp_value.byte;
      }
      // ��������ߴ��� ��4���ֽڣ����ֽڱ�����ǰ��
      for(INT8U i=0;i<4;i++)
      {
        tmp_value.bit4.bith = *(UserName+2*i)-0x30;
        tmp_value.bit4.bitl = *(UserName+2*i+1)-0x30;
        
        tigger_event.date_tcb[11-i] = tmp_value.byte;
      }
      // �������ݲ���  ���ֽڱ�����ǰ��
      for(INT8U i=0;i<TxNuLen;i++)
      {
//        tmp_value.bit4.bith = *(TxNumber+2*i)-0x30;
//        tmp_value.bit4.bitl = *(TxNumber+2*i+1)-0x30;
        
        tigger_event.date_tcb[11+TxNuLen-i] = TxNumber[i];//tmp_value.byte;
      }
      // �������ݳ���
      tigger_event.data_len = 4+4+4+TxNuLen;
      //    memcpy(tigger_event.date_tcb,GetLcdData(),BUF_LEN);
      
      if(LcdEventEnqueue(&tigger_event)) // ���뻺����,�������ź�
      {
        OSSemPost (SemNormalTcb[UpdateEventSem]);
        IconOper(WARING,ICO_EN,5);
        break;
      }
      IconOper(HOME,ICO_EN,5);
      OSSemPost (SemNormalTcb[UpdateEventSem]);
      break;
    }
  default:
    break;
  }
}

/*
�������浱ǰ��Ϣ����
*/
void SendMsgWindowCreate(void* para)
{
  unsigned char i;
  
  strWindow* psMainWindow;
  strContro*    pstrContro;
  
  GLCD_ClearScreen();
  
  memset(&sMainWindow,0,sizeof(sMainWindow));
  memset(sMainControBuf,0,sizeof(sMainControBuf));
  
  // �����ʼ��
  psMainWindow = &sMainWindow;
  psMainWindow->interface_name = TWO_INTERFACE(5);
  psMainWindow->interface_father = MainInterfaceCreate;
  psMainWindow->pctrpoint_tcb = sMainControBuf;
  psMainWindow->interface_create = SendMsgWindowFrameCreate;
  psMainWindow->cursor_addrx = 0;
  psMainWindow->cursor_addry = 0;
  psMainWindow->cursor_addr_max = 4;
   
  pstrContro = &sMainControBuf[0];
  pstrContro->x_axis = 0;
  pstrContro->y_axis = 7;
  pstrContro->cchar_name   = "PROG";
  psMainWindow->interface_create((void*)pstrContro);//����������
  
  pstrContro = &sMainControBuf[0];
  pstrContro->x_axis             = 6;
  pstrContro->y_axis             = 7;
  pstrContro->cchar_name         = "TX";
  pstrContro->cchar_value        = (void*)0;
  pstrContro->contorl_addrx      = 1;
  pstrContro->contorl_addry      = Y_MOVE_DISABLE;
  pstrContro->type               = __BUTTON;
  pstrContro->status             = UNSELECT;
  pstrContro->control_create     = ProgramControlsMsgCreate;
  pstrContro->event_trigger      = ProgramControlEventTrigger;
  
  pstrContro = &sMainControBuf[1];
  pstrContro->x_axis             = 10;
  pstrContro->y_axis             = 7;
  pstrContro->cchar_name         = "DA";
  pstrContro->cchar_value        = (void*)0;
  pstrContro->contorl_addrx      = 2;
  pstrContro->contorl_addry      = Y_MOVE_DISABLE;
  pstrContro->type               = __BUTTON;
  pstrContro->status             = UNSELECT;
  pstrContro->control_create     = ProgramControlsMsgCreate;
  pstrContro->event_trigger      = ProgramControlEventTrigger;
  
  pstrContro = &sMainControBuf[2];
  pstrContro->x_axis             = 14;
  pstrContro->y_axis             = 7;
  pstrContro->cchar_name         = "US";
  pstrContro->cchar_value        = (void*)0;
  pstrContro->contorl_addrx      = 3;
  pstrContro->contorl_addry      = Y_MOVE_DISABLE;
  pstrContro->type               = __BUTTON;
  pstrContro->status             = UNSELECT;
  pstrContro->control_create     = ProgramControlsMsgCreate;
  pstrContro->event_trigger      = ProgramControlEventTrigger;
  
  pstrContro = &sMainControBuf[3];
  pstrContro->x_axis             = 18;
  pstrContro->y_axis             = 7;
  pstrContro->cchar_name         = "PA";
  pstrContro->cchar_value        = (void*)0;
  pstrContro->contorl_addrx      = 4;
  pstrContro->contorl_addry      = Y_MOVE_DISABLE;
  pstrContro->type               = __BUTTON;
  pstrContro->status             = UNSELECT;
  pstrContro->control_create     = ProgramControlsMsgCreate;
  pstrContro->event_trigger      = ProgramControlEventTrigger;
  
  INT8U addr=0;;
  
  // �����ؼ�
  for(i=0;i<psMainWindow->cursor_addr_max;i++)
  {
    addr = i+1;
    psMainWindow->pctrpoint_tcb[i].control_create((void*)&addr);//(void*)&psMainWindow->pctrpoint_tcb[i]
  }
}
