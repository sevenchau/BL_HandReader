#include  "rfdriver_reader.h"
#include "string.h"
#include "includes.h"
#include "queue.h"
#include "lcdappshow.h"

#define AD_DOMAIN_EN     0x68
#define AD_DOMAIN_EX     0x68
#define DATA_EX          0x16

#define CMD_READ_MSG     0x11  // ��ȡ���ܱ�����
#define ACK_READ_MSG0    0x91  // �� �޺���
#define ACK_READ_MSG1    0xB1  // �� �к���
#define ACK_READ_ERR0    0xD1  // �쳣

#define CMD_READ_FOLLOW  0x12  // ����������
#define ACK_READ_FOLLOW0 0x92  // ���޺���
#define ACK_READ_FOLLOW1 0xB2  // ���к���
#define ACK_READ_ERR1    0xD2  // �쳣

typedef INT8U      CMD_Tpyedef;   // ������

// ��ַ ��
typedef struct __ADDR_DOMAIN // 6 byte
{
  INT8U addr0;
  INT8U addr1;
  INT8U addr2;
  INT8U addr3;
  INT8U addr4;
  INT8U addr5;
  INT8U addr6;
}ADDR_TypeDef;

// ���� ��ʾ
typedef union __DATA_MARK // 4 byte
{
  INT32U DmarkWord;
  struct
  {
    INT8U Dmark0;
    INT8U Dmark1;
    INT8U Dmark2;
    INT8U Dmark3;
    INT8U Dmark4;
  }byte;
}DMARK_TypeDef;

typedef struct __CMD_DMARK
{
  CMD_Tpyedef cmd;
  DMARK_TypeDef data_mark;
}CMDMARK_TypeDef;

const CMDMARK_TypeDef ConstCmdDmark[] =
{
  {.cmd = 0x11,.data_mark.DmarkWord = 0x00000000},
//  {.cmd = }
};

#define RF_NUM     5

Queue QRf;
INT8U RfQueueTcb[RF_NUM][RF_ELEMENT];

void RfModeInit(void)
{
  USART1_Config();
//  Rf_Vdd_on();
////  Rf_Vdd_Off();
  memset(RfQueueTcb,0,RF_NUM*RF_ELEMENT);
  Queue_Init(&QRf,RF_NUM,RF_ELEMENT);
}

void RfRxIntEnable(void)
{
  USARTx_IntEn(INT_ID_USART1);
}

void RfRxIntDisable(void)
{
  USARTx_IntDis(INT_ID_USART1);
}

// ���ݽ��� �����
INT8U RfEventEnqueue(INT8U* pdata)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR         cpu_sr;
#endif 
  
  unsigned short ptigger;
  
  CPU_CRITICAL_ENTER(); 
  if(!enQueue(&QRf, &ptigger))
  {
    memcpy(&RfQueueTcb[ptigger],pdata,RF_ELEMENT);
    CPU_CRITICAL_EXIT();
    return 0;
  }
  CPU_CRITICAL_EXIT();
  return 1;
}

extern INT8U uTargetAddr[6];
// ���� ������ ����
INT8U RfEventDelqueue(INT8U* pcmd,INT8U* prdata,INT8U* prlen)
{
#if (CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL)
  CPU_SR         cpu_sr;
#endif 
  
  
  unsigned short ptigger;
  INT8U tmp_tcb[RF_ELEMENT];
  INT8U sum = 0;
  
  CPU_CRITICAL_ENTER();
  while(!deQueue(&QRf, &ptigger))
  {
    memset(tmp_tcb,0,RF_ELEMENT);
    memcpy(&tmp_tcb,&RfQueueTcb[ptigger],RF_ELEMENT);
    memset(RfQueueTcb[ptigger],0,RF_ELEMENT);
    CPU_CRITICAL_EXIT();
    if(0x93 != tmp_tcb[8]) // ��ȡ��ַָ��ʱ������ַУ��
    {
      if(0 != memcmp(uTargetAddr,tmp_tcb+1,6)) // 6�ֽ� ��ַ�Ƚ�GetTargetAddress()
      {
        return 1;
      }
    }
    
    for(INT8U i=0;i<tmp_tcb[9]+10;i++)
    {
      sum += tmp_tcb[i];
    }
    if(tmp_tcb[tmp_tcb[9]+10] !=  sum) // У��������ȷ
    {
       return 1;
    }
    
    // У��ͨ��
    *pcmd = tmp_tcb[8]; // 1�ֽ� ������ֵ
    
    *prlen = tmp_tcb[9];
    
    for(INT8U i=0;i<*prlen;i++)// ʵ������
    {
      if(*(tmp_tcb+10+i) < 0x33)
      {
        *(prdata+i) = 0xff-0x33+*(tmp_tcb+10+i);
      }
      else
      {
        *(prdata+i) = *(tmp_tcb+10+i)-0x33;
      }
    }
    
    return 0;
  }
  CPU_CRITICAL_EXIT();
  
  return 1;
}

// ���ݴ��
void RFSendMsgDataPackage(const INT8U* addr_domain,INT8U cmd,const INT8U* pdata,INT8U len,INT8U* prdata,INT8U* rlen)
{
  INT8U tmp_value = 0;
  
  // ����
  *(prdata+0)  = 0xfe;
  *(prdata+1)  = 0xfe;
  *(prdata+2)  = 0xfe;
  *(prdata+3)  = 0xfe;
  
  // ��ַ��
  *(prdata+4)  = AD_DOMAIN_EN;
  memcpy(prdata+5,addr_domain,6);
  *(prdata+11) = AD_DOMAIN_EX;
  
  // ������
  *(prdata+12) = cmd;
  
  // ���ݳ���
  *(prdata+13) = len;
  
  // ������
  for(INT8U i=0;i<len;i++)
  {
    *(prdata+14+i) = *(pdata+i)+0x33;
  }
  
  // У���
  for(INT8U i=0;i<len+10;i++)
  {
    tmp_value += *(prdata+4+i);
  }
  *(prdata+14+len) = tmp_value;
  
  *(prdata+15+len) = DATA_EX;
  *rlen = len+15+1;
}