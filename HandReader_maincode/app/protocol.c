/*
-  �ļ�����: protocol.c
-  �ļ�����: 
-  �汾����: v1.1 2012.04
-  ��������: __Rangers
*/
#include "protocol.h"
#include "string.h"
#include "serve.h"

#define ERROR_PROTOCOL_BASE ERROR_BRGIN(1)       //Э�鲿�ֻ�ַ

/*
*��������: flash_ProDataLearning ����:flash ͨ��Э�����
*Э������: |head|pow|spd|fre|idH|idL|NA.|NA.|NA.|NA.|NA.|NA.|NA.|NA.|CRC|0x7E|
*��ڲ���: data_buf-�������
*          redata_len-������ݳ���
*���ڲ���: FALSE �� TRUE
*/
uierr flash_ProDataLearning(const INT8U* data_buf , const INT8U size)
{
  return TRUE;
}

/*
- ��������: flashInit_DataPackage flashc��ʼ���洢Э��
- ��ڲ���: buf �洢����  buflen �洢����
- ���ڲ���: FALSE TRUE
*/
uierr flashInit_DataPackage(INT8U* buf , INT8U buflen)
{
  return TRUE;
}

/*
- ��������: flash_DataPackage flash�洢Э��
- ��ڲ���: buf �洢����  buflen �洢����
- ���ڲ���: FALSE TRUE
*/
void flash_DataPackage(const INT8U* buf , INT8U* rebuf, INT8U buflen)
{
}
