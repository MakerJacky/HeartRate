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



#define  WaveSlopeRange 30		  /**< ��ݲ��жϱ�׼��ʼΪ25 > */
#define  HeartRateMAX	160			 /**<   �������ֵ ��ʼΪ160    > */
#define  HeartRateMIN   40			 /**<   ������Сֵ ��ʼΪ40    > */
#define  SampleRate     2				 /**<   ������ Ĭ��Ϊ2ms    > */	
#define  SamplePointTotal 30000		 /**<   ���еĲ����� 60*1000/SampleRate > */	
#define  TriggerPeriodPoint 10				 /**<  ���δ��ڲ��� 10> */	
#define  SamplePointMax     8000				 /**<  ���ʲ������ֵĬ��4000��> */	
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
    HRPointMax = 2,	 /**<   ���ʲ������ֵ����   > */
    HRLineOut = 3    /**<  ��������̫ƽ���˳�  > */
} HRState;


typedef enum
{
    SlopeUp= 0,   
    SlopeDown = 1,	
    SlopeSmooth = 2,	 
} SlopeDirection;


/**
 * @brief BPM wave define key definition.
 *
 * Each key definition will contains BPM wave type/ period / rising time / falling time 
 * key address/ key value.
 */
typedef struct HEART_RATE_PULSE
{
	uint8_t		index;			 /**<  �ڼ�������  > */
    uint8_t     type;        /**< wave type . Like sine, squre sawtooth... */
    uint16_t  	topIndex;    /**< top index */
	uint16_t  	topValue;    /**< top value */
	uint16_t  	topLength;    /**< top length */
	uint16_t  	bottomIndex;    /**< bottom index */
	uint16_t  	bottomValue;    /**< bottom value */
	uint16_t  	bottomLength;    /**< bottom length */
    uint16_t    upTime; 		/*   rising edge time   */
    uint16_t    downTime;      /*   falling edge time   */
	uint16_t	startPointIndex;	 /**<    ��ʼ��  > */
	uint16_t	endPointIndex;		 /**<   ������   > */		
	uint8_t		peakBottomValue;			 /**<  ��ֵ���   > */
	uint16_t	period;
} HEART_RATE_PULSE_T, *HEART_RATE_PULSE_INDEX;


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


typedef struct SLOPE
{
	uint16_t value;		
	SlopeDirection  direction;			
	uint8_t smooth;
} SLOPE_T, *SLOPE_INDEX;






/* ram define ------------------------------------------------------------------*/

extern uint16_t smoothValue;
extern uint16_t heartRate;   
extern uint16_t pointCount;
/*
 * common funcation subroutine
 * 
 */
void pushArrayData(uint16_t *array,int length,uint16_t data);




void clrHeartRateStack(void);

void heartRateClrRam(void);


uint16_t getArrayAverageWithoutPeak(uint16_t * array,int length);


/*
 * heart rate calculation main subroutine
 * 
 */


HRState getHeartRateWaves(uint16_t adData) ;







/*
 * heartRateParamSetup
 * param: _waveSlopeStandard  
 * _sampleRate 1 = 1ms 30 = 30ms
 */
void heartRateParamSetup(HEART_RATE_PARAM_T heartRateParam);


/*
 * �õ��˲��������ֵ
 * param:
 * return: heartRate
 */
uint16_t getHeartRateFilter(void);

/*
 * ÿ�ο�ʼ���Ա���Ҫ���ô˳�ʼ��
 * param:
 * return: 
 */
void heartRateInit(void);



#ifdef __cplusplus
}
#endif

#endif /* _RTL876X_ADC_H_ */

