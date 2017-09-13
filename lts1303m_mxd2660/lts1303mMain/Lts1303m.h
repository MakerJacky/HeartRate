/**
*********************************************************************************************************
*               Copyright(c) 2017, ETEK Semiconductor Corporation. All rights reserved.
*********************************************************************************************************
* @file      lts1303m.h
* @brief     header file of lts1303m
* @details   
* @author    jiangs
* @date      2017-05-04
* @version   v0.1
* *********************************************************************************************************
*/


#ifndef _LTS1303M_H_
#define _LTS1303M_H_

#ifdef __cplusplus
 extern "C" {
#endif

//#include "rtl876x.h"
#include "nrf.h"



#define  WaveSlopeRange 100		  /**< ��ݲ��жϱ�׼��ʼΪ25 > */
#define  HeartRateMAX	160			 /**<   �������ֵ ��ʼΪ160    > */
#define  HeartRateMIN   40			 /**<   ������Сֵ ��ʼΪ40    > */
#define  SampleRate     10				 /**<   ������ Ĭ��Ϊ2ms    > */	
#define  SamplePointTotal 15000		 /**<   ���еĲ����� 60*1000/SampleRate > */	
#define  TriggerPeriodPoint 10				 /**<  ���δ��ڲ��� 10> */	
#define  SamplePointMax     10000				 /**<  ���ʲ������ֵĬ��4000��> */	
#define  SmoothMax 		800		 /**<  ƽ�������ֵ Ĭ��Ϊ600> */	
#define  WaveSampleMax 		4000			 /**<  ȡ���ٵ�����㷨> */	
#define  WaveArrayMax		3		 /**<  ȡ���ٸ����ν��м���> */	
#define  RecDetectData		10		 /**<  ƽ���ȳ��������ж�Ϊ����> */	
#define  PeriodMax  		750			/**< ���������> */	
#define  PeriodMin			188			/**< ��С������> */	
#define  PeakBottomStand	100		/**<   ��ֵ��ֵ          > */	




/*
 * Defines the prototype to which the application bpm  function must conform.
 *  
 */
 /**<      > */
typedef enum
{
    HRInit = 0,   /*BPM init */
    HRFinish = 1,	 /*BPM finish */		
    HRError = 2	 /**<  �������ݴ��� > */
} HRState;

#if 0
typedef struct HEART_RATE_PARAM
{
	uint16_t waveSlopeRange;		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
	uint8_t  heartRateMAX;				 /**<   �������ֵ ��ʼΪ160    > */
	uint8_t	heartRateMIN;				 /**<   ������Сֵ ��ʼΪ40    > */
	uint16_t sampleRate;				 /**<   ������ Ĭ��Ϊ2ms    > */	
	uint16_t oneMinutePoint;			 /**<   ���еĲ����� 60*1000/SampleRate > */	
	uint8_t triggerPeriodPoint;				 /**<  ���δ��ڲ��� 10> */	
 	uint16_t samplePointMax;				 /**<  ���ʲ������ֵĬ��4000��> */	
	uint16_t evennessMax;				 /**<  ƽ�������ֵ Ĭ��Ϊ200> */	
	uint16_t waveArrayMax;				 /**<  ȡ���ٸ����ν��м���> */	
	uint16_t recDetectData;				 /**<  ƽ���ȳ��������ж�Ϊ����> */	
	uint16_t periodMax;					/**< ���������> */	
	uint16_t periodMin;					/**< ��С������> */	
	uint16_t peakBottomStand;			/**<   ��ֵ��ֵ          > */	
} HEART_RATE_PARAM_T, *HEART_RATE_PARAM_INDEX;

#endif





/* ram define ------------------------------------------------------------------*/


extern uint16_t heartRate;   

/*
 * common funcation subroutine
 * 
 */




/*
 * �õ��˲��������ֵ
 * param:
 * return: heartRate
 */
uint16_t getHeartRateDetection(void);

/*
 * ÿ�ο�ʼ���Ա���Ҫ���ô˳�ʼ��
 * param:
 * return: 
 */
void heartRateInit(void);


HRState getHeartRateWaveInfo(uint16_t adData,int count);

uint16_t getHeartRateSmooth(uint16_t tmpHeartRate);



#ifdef __cplusplus
}
#endif

#endif /* _RTL876X_ADC_H_ */

