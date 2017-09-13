/*
*********************************************************************************************************
*               Copyright(c) 2017, ETEK Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      lts1303m.C
* @brief      file of lts1303m
* @details   
* @author    jiangs
* @date      2017-05-04
* @version   v0.1
* *********************************************************************************************************
*/



/* Includes ------------------------------------------------------------------*/
#include "lts1303m.h"
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"

/* const define ------------------------------------------------------------------*/



#define RATE_NUM_MAX                        16
#define PLUSE_SAMPLE_MAX					32
#define WAVE_INDEX_MAX					16




#if 0
const HEART_RATE_PARAM_T HeartRateParamConst = 
{
		
	WaveSlopeRange,		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
	HeartRateMAX,			 /**<   �������ֵ ��ʼΪ160    > */
	HeartRateMIN,				 /**<   ������Сֵ ��ʼΪ40    > */
	SampleRate,				 /**<   ������ Ĭ��Ϊ2ms    > */	
	SamplePointTotal,			 /**<   ���еĲ����� 60*1000/2 > */	
	TriggerPeriodPoint,			 /**<  ���δ��ڲ��� 10> */	
	SamplePointMax,		 /**<  ���ʲ������ֵĬ��4000��> */	
	SmoothMax,			 /**<  ƽ�������ֵ Ĭ��Ϊ600> */	
	WaveArrayMax,		 /**<  ȡ���ٸ����ν��м���    Ĭ��3��> */	
	RecDetectData,		 /**<  ƽ���ȳ��������ж�Ϊ����Ĭ��10��> */	
	PeriodMax,	 /**<��������� (60000/HeartRateMAX)/SampleRate> */		
	PeriodMin,	 /**<��С������ (60000/HeartRateMIN)/SampleRate> */		
  PeakBottomStand,	 /**< ��Ч����ֱ�ӵļ�ֵ    > */		
};
#endif


/* ram define ------------------------------------------------------------------*/
uint16_t heartRate;   

uint16_t lastHeartRate = 60;

uint8_t  heartRateIndex  =0;





uint16_t heartRateStack[RATE_NUM_MAX];
uint16_t heartRateTemp[RATE_NUM_MAX];



uint16_t peakIndexs[PLUSE_SAMPLE_MAX];


uint8_t wavePulseState;
int peakCount ;
int pulseIndex;	//ÿָ֡ʾ
int peakStart;	//�߷忪ʼָʾ
int peakStop;	//�߷����ָʾ
int bottomStart;
int bottomStop;
int pointCount;	//��ʱ��ָʾ
int peakAve;
int pulsePeakIndex;   //�ߵ�ƽ �м��λ��



//static HEART_RATE_PARAM_T HeartRateParam;

/**
  *
 **/





/* subroutine define ------------------------------------------------------------------*/

void heartRateInit(void){
	pointCount = 0;
	wavePulseState = 0;
	peakCount= 0;
	pulseIndex = 0;
	pulsePeakIndex = 0;

}
/**
  *	1: bottom 2 peak 0 other
 **/


uint8_t getWavePeakBottom(uint16_t adData){
	
	uint16_t tmp;
	
	tmp = adData;
	if(tmp<100){
		return 1;
		}
	tmp= adData-40;
	
	if(tmp>900){
		return 2;
		}else {
		return 0;
		}	
}




HRState getHeartRateWaveInfo(uint16_t adData,int count) {
	HRState state;
	uint8_t peak;
	state = HRInit;
	// printf("adData = %d\r\n",adData);
	
	peak = getWavePeakBottom( adData);
//	printf("isWavePeak = %d\r\n",peak);
	pointCount++;
	

	if(wavePulseState==0){			//�жϸ߷�
		if(peak==2){
			peakCount++;
			if(peakCount>10){
				peakCount = 0;
				wavePulseState =1;
				if(pulseIndex==0){	//��֡��ʼ
			
				pointCount=10;			
				peakStart = 10;
				pulseIndex = 1;
				printf("peakstart[%d] = %d \r\n ",count,adData);		  
				}else {						//��һ֡����
				printf("peakstart2[%d] = %d \r\n ",count,adData);		  
				bottomStop = pointCount;
				peakStart = pointCount-10;
				pulseIndex++;
				if(pulseIndex>16){
					state=HRFinish;
					}
			
				
					}
				}

			
			}else {
			peakCount=0;
				}
			
		}else {					//	�жϵ͹�
		if(peak!=2){			//�����ڸ߷�ֵ
			peakCount++;
			if(peakCount>10){
				wavePulseState =0;
				peakStop = pointCount-10;
				peakAve = peakStop-peakStart;
				pulsePeakIndex= peakStart+peakAve;
				peakIndexs[pulseIndex-1]=pulsePeakIndex; 
				printf("peakstop[%d] = %d peakAve = %d pulsePeakIndex = %d \r\n ",count,adData,peakAve,pulsePeakIndex);		  
				}else {						
				bottomStart = pointCount;
				
				
	
				}

			
			}else {
			peakCount=0;
				}
		}
	

	if(pointCount>=SamplePointMax){
		state = HRError;
		}
	
	return state;
	
}



/**
  * @brief  This function getArrayMaxIndex
  * @param uint16_t  array[], int len
  * @retval array max index
  */
int getArrayMaxIndex(uint16_t *array,int len){
	int i,iMax;

    for(i=iMax=0;i<len;i++){
        if(array[iMax]<array[i]){
			  iMax=i;
        	}
          
    	}
    return iMax;
}

int getArrayMinIndex(uint16_t *array,int len){
	int i,iMin;

    for(i=iMin=0;i<len;i++)
        if(array[iMin]>array[i])
            iMin=i;
  
    return iMin;
}

uint16_t getHeartAverage(uint16_t *array,int length){
	int i = 0;
	int total = 0;
	for(i=0;i<length;i++){
		total +=array[i];
		}
	return total/length;
}


uint16_t getHeartAverageWithoutPeak(uint16_t *array,int length){
	int i = 0;
	int total = 0;
	int maxIndex,minIndex;
	uint16_t ave;
	minIndex = getArrayMinIndex(array,length);
	maxIndex = getArrayMaxIndex(array,length);
	
	for(i=0;i<length;i++){
		if(i!=maxIndex&&i!=minIndex){
			total +=array[i];
			}	
		}
	ave = total/(length-2);
	return ave;
}

uint16_t getHeartRateSmooth(uint16_t tmpHeartRate){
	int i = 0;
	
	if(heartRateIndex<9){
			heartRateStack[heartRateIndex++]=tmpHeartRate;
			heartRate = getHeartAverage(heartRateStack,heartRateIndex);
	}else {
	for(i=0;i<7;i++){
	//	printf("b heart = %d\r\n",heartRateStack[i] );
		heartRateStack[i]=heartRateStack[i+1];
		//printf("a heart = %d\r\n",heartRateStack[i] );
		//nrf_delay_ms(100);
		}
	heartRateStack[7] = tmpHeartRate;
	heartRate = getHeartAverage(heartRateStack,8);
	}
	printf(" smooth heart  = %d\r\n",heartRate );
	
	return heartRate;
}


uint16_t getHeartRateDetection(void){
	int i = 0;
	uint16_t tmpHeartRate;
	int count = 0;
	for(i=0;i<(pulseIndex-2);i++){
		//printf("getHeartRateDetection[%d] = %d  \r\n ",i,peakIndexs[i+1]-peakIndexs[i]);	
		tmpHeartRate = SamplePointTotal/ (peakIndexs[i+1]-peakIndexs[i]);
		// printf(" heart [%d]= %d\r\n",i,tmpHeartRate );
		// nrf_delay_ms(100);
		if(tmpHeartRate<=HeartRateMAX&&tmpHeartRate>=HeartRateMIN){
			heartRateTemp[count++]=tmpHeartRate;
		
			}
	}
	if(count!=0){
	tmpHeartRate =	getHeartAverageWithoutPeak(heartRateTemp,count);
	}else {
	tmpHeartRate = lastHeartRate;
	}
	
	printf("  before heart = %d\r\n",tmpHeartRate );
	heartRate = tmpHeartRate;
	lastHeartRate = tmpHeartRate;
	
	 

	return heartRate;
}




