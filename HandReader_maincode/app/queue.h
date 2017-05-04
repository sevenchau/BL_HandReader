#ifndef __QUEUE_H
#define __QUEUE_H

#include "app.h"
#include "includes.h"
#include "os_cpu.h"

typedef struct 
{
  unsigned short head;
  unsigned short tail;
  unsigned short queue_size;
  unsigned short element_num;
}Queue;

/* ��ʼ������ */
void Queue_Init(Queue *queue,unsigned char queue_size,unsigned char element_size);

/* �ж϶����Ƿ�Ϊ�� */
unsigned short isEmpty(Queue *queue);
/* �ж϶����Ƿ�Ϊ�� */
unsigned short isFull(Queue *queue);
/* ��������� */
unsigned short enQueue(Queue *queue, unsigned short* pointer);
/* ���ݳ����� */
unsigned char deQueue(Queue *queue, unsigned short* pointer);

#endif