#ifndef __KS0108_H
#define __KS0108_H

#include "graphic.h"
//-------------------------------------------------------------------------------------------------
// Graphic LCD C library
// http://glcd-libc.dxp.pl
// (c) Rados�aw Kwiecie�, radek@dxp.pl
//-------------------------------------------------------------------------------------------------
#define KS0108_SCREEN_WIDTH	128
#define KS0108_SCREEN_HEIGHT	64


#define DISPLAY_SET_Y       0x40  // Y
#define DISPLAY_SET_X       0xB8  // X
#define DISPLAY_START_LINE  0xC0  // ��Ļ��ʼ��ʾ  �����ڹ���
#define DISPLAY_ON_CMD		0x3E
  #define ON	0x01
  #define OFF	0x00

#define DISPLAY_STATUS_BUSY	0x80
#define DISPLAY_STATUS_OFF      0x20

#define BUF_LEN  35

////////////////////////////////////////////////////////////////////////////////
//unsigned char GLCD_ReadStatus(unsigned char controller);
unsigned char GLCD_ReadStatus(unsigned char controller);
void GLCD_WriteCommand(unsigned char commandToWrite, unsigned char controller);

void GLCD_ReBoot(void);
void GLCD_Initialize(void);

void GLCD_TextGoTo(unsigned char x, unsigned char y);
void GLCD_GoTo(unsigned char, unsigned char);

void GLCD_WriteData(unsigned char);
void GLCD_WriteString(char *);
void GLCD_WriteAntiColorString(char * stringToWrite);//�ַ��� ��ɫ

unsigned char GLCD_ReadByteFromROMMemory(char *);

void GLCD_WriteIcon(unsigned char on_off);//ͼ�����

void GLCD_SetPixel(unsigned char x, unsigned char y, unsigned char color);

void GLCD_ClearScreen(void); // ����
void GLCD_ClearScreenLiney(unsigned char y);//�����ǰ ��

void GLCD_BitmapAntiColor(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy);// ͼ��ɫ
void GLCD_Bitmap(char * bmp, unsigned char x, unsigned char y, unsigned char dx, unsigned char dy);
////////////////////////////////////////////////////////////////////////////////
#define CUR_DIS     0x00
#define CUR_EN      0x01

#define MOVE_LEFT   0x01
#define MOVE_RIGHT  0x02
#define MOVE_UP     0x03
#define MOVE_DOWN   0x04

void CursorInit(unsigned char xstart,unsigned char ystart,unsigned char xmax,unsigned char ymax);// ����ʼ��
void CursorEnable(void); // ʹ����˸
void CursorDisable(void);// ʧ����˸
void CursorGlink(void);  // �����˸
void CursorMove(unsigned char direction);// ����ƶ�
void ScanfChar(char char_msg);// �ַ�����
void DeletChar(void);         // �ַ�ɾ��

void ShowScanfChar(char char_msg);/*��ʾ��ǰ������ַ��������棬�Ա�ѡ��*/
unsigned char CursorBehindData(void);//���������Ƿ�������
////////////////////////////////////////////////////////////////////////////////
#define SEND       0x00
#define WARING     0x01
#define HOME       0x02
#define BATTERY    0x03

#define ICO_EN     0xff
#define ICO_DIS    0x00
#define ICO_NUM    0x04

void IcoInit(void);
void IconOper(unsigned char ico_select, unsigned char ico_active,unsigned char ico_count);// ico ͼ�����
void IcoGlintTaskEvent(void);// ico ��˸�¼�

int* GetLcdData(void);
void ClearLcdStorData(void);

void KS0108_LightOn(void);
void KS0108_LightOff(void);
//-------------------------------------------------------------------------------------------------
// End of file KS0108.h
//-------------------------------------------------------------------------------------------------

#endif



