/**
******************************************************************************
* @file    main.c
* @author  fire
* @version V1.0
* @date    2015-01-xx
* @brief   WF-ESP8266 WiFiģ�����
******************************************************************************
* @attention
*
*
******************************************************************************
*/ 

#include "stm32f10x.h"

#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "lts1303m.h"
#include  "heart_rate_sample.h"


const HEART_RATE_PARAM_T HeartRateParam = 
{
		
	25,		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
	160,			 /**<   �������ֵ ��ʼΪ160    > */
	40,				 /**<   ������Сֵ ��ʼΪ40    > */
	2,				 /**<   ������ Ĭ��Ϊ2ms    > */	
	30000,			 /**<   ���еĲ����� 60*1000/2 > */	
	10,			 /**<  ���δ��ڲ��� 10> */	
	3500,		 /**<  ���ʲ������ֵĬ��4000��> */	
	200,			 /**<  ƽ�������ֵ Ĭ��Ϊ200> */	
	4000,			 /**<  ȡ���ٵ�����㷨> */	
	3,		 /**<  ȡ���ٸ����ν��м���    Ĭ��3��> */	
	10,		 /**<  ƽ���ȳ��������ж�Ϊ����Ĭ��10��> */	
	188,	 /**<��������� (60000/HeartRateMAX)/SampleRate> */		
	750,	 /**<��С������ (60000/HeartRateMIN)/SampleRate> */		
  100,	 /**< ��Ч����ֱ�ӵļ�ֵ    > */		
};

#if 0
typedef struct HEART_RATE_PARAM
{
	uint16_t WaveSlopeRange;		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
	uint8_t  HeartRateMAX;				 /**<   �������ֵ ��ʼΪ160    > */
	uint8_t	HeartRateMIN;				 /**<   ������Сֵ ��ʼΪ40    > */
	uint16_t SampleRate;				 /**<   ������ Ĭ��Ϊ20ms    > */	
	uint16_t SamplePointTotal;			 /**<   ���еĲ����� 60*1000/SampleRate > */	
	uint8_t TriggerPeriodPoint;				 /**<  ���δ��ڲ��� 10> */	
 	uint16_t SamplePointMax;				 /**<  ���ʲ������ֵĬ��4000��> */	
	uint16_t EvennessMax;				 /**<  ƽ�������ֵ Ĭ��Ϊ200> */	
	uint16_t WaveSampleMax;				 /**<  ȡ���ٵ�����㷨> */	
	uint16_t WaveArrayMax;				 /**<  ȡ���ٸ����ν��м���> */	
	
} HEART_RATE_PARAM_T, *HEART_RATE_PARAM_INDEX;

#endif

void heartRateSubroutine(){
		int i = 0;	
	    HRState bpmState;
		uint16_t heartRate = 40;

		heartRateInit();
	
		
		for(i=0;i<4000;i++){
		
		bpmState = 	 heartRateWaveDetect(testWave_TYPE3[i]);  
			
		if(bpmState==HRFinish){
		heartRate =	getHeartRateFilter();
			
		heartRateInit();
		
		//
		}
		if(bpmState==HRPointMax){
		heartRateInit();
			}
		if(bpmState==HRLineOut){
		heartRateClrRam();
			}
		
	}

}

/**
* @brief  ������
* @param  ��
* @retval ��
*/
int main(void)
{
	
	heartRateParamSetup(HeartRateParam);
	clrHeartRateStack();
	
	while(1){

	heartRateSubroutine();	
	
	}
		
		
		

	
}


/*********************************************END OF FILE**********************/
