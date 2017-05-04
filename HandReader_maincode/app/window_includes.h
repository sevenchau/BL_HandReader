#ifndef __WINDOW_INCLUDES_H
#define __WINDOW_INCLUDES_H

#include "includes.h"
#include "queue.h"

#include "KS0108.h"
#include "graphic.h"
#include "string.h"
#include "serve.h"

#include "windows1.h"
#include "windows2.h"
#include "windows3.h"
//#include "lcdappshow.h"

#define CONTORL_NUM             5

//�� ���� (һ������)
#define MAIN_INTERFACE          1
//���� ����
#define TWO_INTERFACE(x)        (20+x)
//��������(����)
#define TREE_INTERFACE(x)       (30+x)

#define BUTTON(x)                (10+x)
#define TEXT(x)                 (30+x)
#define SWITCH(x)               (50+x)

// �ؼ�����
#define __BUTTON                  1
#define __TEXT                    2
#define __SWITCH                  3

// �ؼ�״̬ 
#define SELECT                  1 // ѡ��
#define UNSELECT                2 // δѡ��
#define TIGGER_EVNT             3 // �����¼�״̬

#define X_MOVE_DISABLE   0xFF
#define Y_MOVE_DISABLE   0xFF

#define ACTIVE_NUM     5

typedef void (*pfuc) (void*);

typedef struct __TIGGER_EVETN
{
  unsigned char active_window;
  char* pactive_button_name;
  unsigned char data_len;
  int date_tcb[BUF_LEN];
}BUT_TypeDef;

typedef union __WORD_TO_TYTE
{
  unsigned int word;
  struct
  {
    unsigned char bytel;
    unsigned char byteh;
  };
}strWordToType;

typedef struct __CONTORLS_STR // �ؼ�
{
  unsigned char x_axis;
  unsigned char y_axis;
  char* cchar_name;           // �ַ�������ʽ
  int* cchar_value;           // �ַ�ֵ
  unsigned char type;         // �ؼ����� button text  switch progress bar(������)
  unsigned char status;       // ״̬��ѡ�� δѡ��  �����¼�
  unsigned char contorl_addrx;// �ؼ�x��ַ(�е�ַ �����α���Ѱ)
  unsigned char contorl_addry;// �ؼ�x��ַ(�е�ַ �����α���Ѱ)
  pfuc control_create;        // �ؼ�����
  pfuc event_trigger;         // �¼�����
}strContro;

typedef struct __INTERFACE    // ����
{
  unsigned char interface_name;    // ��������
  unsigned char cursor_addrx;// �α� x ��ַ ���˶�
  unsigned char cursor_addry; // �α� y ��ַ ���˶�
  unsigned char cursor_addr_max;// �α� �˶�ָ�� ���ֵ
  strContro* pctrpoint_tcb;     // �ؼ�ָ���б�
  pfuc interface_father;       // �� ����
  pfuc interface_create;        // ���幹�캯��
}strWindow;

extern const unsigned char gImage_LOGO[282];
extern const unsigned char gImage_yunengyibiao[405];
extern const unsigned char gImage_nanjynybkjyxgs[363];
extern const unsigned char gImage_now_msg[128];
extern const unsigned char gImage_stor_msg[128];
extern const unsigned char gImage_loca_msg[128];
extern const unsigned char gImage_cfg_msg[128];
extern const unsigned char gImage_TIME[66];
extern const unsigned char gImage_buttonframe[44];

extern const unsigned char gImage_sendmsg[128];
extern const unsigned char gImage_password[128];
extern const unsigned char gImage_usercode[128];
extern const unsigned char gImage_datamark[128];

extern strWindow sMainWindow;
extern strContro sMainControBuf[CONTORL_NUM];
extern strWindow HisActinveWindow; // ��ʷ�����
extern strContro HisActiveContro; //  ��ʷ��ؼ�
extern pfuc      fTiggerEventHook[CONTORL_NUM];//�����¼��ҹ�
extern BUT_TypeDef ActiveTcb[ACTIVE_NUM];
//extern Queue QActive;

#endif