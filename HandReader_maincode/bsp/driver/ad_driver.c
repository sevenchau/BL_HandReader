#include "ad_driver.h"
#include "includes.h"
#include "string.h"
/*
* PA4 ------ AD12 IN4     RTC��ص���   3.6V 1:1�����ѹ
* PA5 ------ AD12 IN5     �����ص���  3V   1:1�����ѹ
*/

//ADC_DMACmd(ADC1, ENABLE);
#define  Sample_Num 100
#define  Channel_Num 2
uint16_t ADC_ConvertedValue[Sample_Num][Channel_Num] = {0};

void ADC_DMA_Config(void)
{
 DMA_InitTypeDef DMA_InitStructure;
              
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
 DMA_DeInit(DMA1_Channel1);
 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//���� DMAͨ���������ַ
 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;//����DMAͨ���洢����ַ
 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//ָ������ΪԴ��ַ
 DMA_InitStructure.DMA_BufferSize = Sample_Num*Channel_Num;//����DMA��������С
 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ����
 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ����
 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�����������ݿ��16λ
 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//����洢�����ݿ��16λ
 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAͨ������ģʽλ���λ���ģʽ
 DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ�����ȼ���
 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//��ֹDMAͨ���洢�����洢������
 DMA_Init(DMA1_Channel1, &DMA_InitStructure);
 DMA_Cmd(DMA1_Channel1,ENABLE);
 
// DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);//������������ж�     
// BSP_IntVectSet(BSP_INT_ID_DMA1_CH1, BSP_IntHandlerDMA1_CH1); 
// BSP_IntPrioSet(BSP_INT_ID_DMA1_CH1,1);   
// BSP_IntEn(BSP_INT_ID_DMA1_CH1);
}

void ADC1_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 ADC_InitTypeDef ADC_InitStructure;
  
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
 GPIO_Init(GPIOA, &GPIO_InitStructure);
 ADC_DMA_Config();
  
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//RCC_APB2Periph_AFIO
// ADC_DeInit(ADC1);
 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC1��ADC2�����ڶ���ģʽ
 ADC_InitStructure.ADC_ScanConvMode = ENABLE;//��ͨ��
 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������ת��
 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת������Ҷ���
 ADC_InitStructure.ADC_NbrOfChannel = Channel_Num;//ͨ����Ŀ
 ADC_Init(ADC1, &ADC_InitStructure); 
// ADC_TempSensorVrefintCmd(ENABLE);//ʹ��Ƭ���¶ȴ�����
  
 //STM32 ��ADC ʱ��Ƶ�ʷ�Χ��0.6MHz - 14MHz�� ����ʱ����ݼĴ���������Ϊ��1.5��.....239.5 ��ʱ�����ڣ�
// RCC_ADCCLKConfig(RCC_PCLK2_Div8); //ADC ���Ϊ14M PCLK 6��Ƶ 72/6 = 12M ��С����ʱ�� 1.5us
 ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_239Cycles5);//ͨ����ת������ת��ʱ��
 ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 2, ADC_SampleTime_239Cycles5);
  
 ADC_DMACmd(ADC1, ENABLE);
 ADC_Cmd(ADC1, ENABLE);
 
 ADC_ResetCalibration(ADC1);
 while(ADC_GetResetCalibrationStatus(ADC1));
 ADC_StartCalibration(ADC1);//��ʼУ׼
 while(ADC_GetCalibrationStatus(ADC1));
 ADC_SoftwareStartConvCmd(ADC1, DISABLE);//ʹ��ADC�����ת����������
}

void CalculateSampleValues(float* ppower_electric,float* prtc_electric)
{
  uint32_t sum = 0;
  
  for(uint8_t i=0;i<Sample_Num;i++)
  {  
    sum += ADC_ConvertedValue[i][0];
  }
  *ppower_electric = ((float)((float)sum/(float)Sample_Num/4096.0))*3.0*2;
  
  sum = 0;
  for(uint8_t i=0;i<Sample_Num;i++)
  {  
    sum += ADC_ConvertedValue[i][1];
  }
  *prtc_electric = ((float)((float)sum/(float)Sample_Num/4096.0))*3.6*2;
}


// ��С��ת�� �������ֺ�С������
void FloatChangeToInt(float value,uint16_t* integer, uint16_t* decimal)
{
  *integer = (uint16_t)value;
  *decimal = (uint16_t)((value - (*integer))*1000);
}