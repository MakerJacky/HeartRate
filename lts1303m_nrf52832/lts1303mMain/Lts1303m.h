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
typedef struct HEART_RATE_WAVE
{
	uint8_t		waveIndex;			 /**<  �ڼ�������  > */
  uint8_t    waveType;        /**< wave type . Like sine, squre sawtooth... */
  uint16_t  	topIndex;    /**< top index */
	uint16_t  	topValue;    /**< top value */
	uint16_t  	topLength;    /**< top length */
	uint16_t  	bottomIndex;    /**< bottom index */
	uint16_t  	bottomValue;    /**< bottom value */
	uint16_t  	bottomLength;    /**< bottom length */
  uint16_t    risingEdge; 		/*   rising edge time   */
  uint16_t    fallingEdge;      /*   falling edge time   */
	uint16_t	firstPointIndex;	 /**<    ��ʼ��  > */
	uint16_t	endPointIndex;		 /**<   ������   > */		
	uint8_t		peakBottomValue;			 /**<  ��ֵ���   > */
	
} HEART_RATE_WAVE_T, *HEART_RATE_WAVE_INDEX;


typedef struct HEART_RATE_PARAM
{
	uint16_t waveSlopeRange;		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
	uint8_t  heartRateMAX;				 /**<   �������ֵ ��ʼΪ160    > */
	uint8_t	heartRateMIN;				 /**<   ������Сֵ ��ʼΪ40    > */
	uint16_t sampleRate;				 /**<   ������ Ĭ��Ϊ2ms    > */	
	uint16_t samplePointTotal;			 /**<   ���еĲ����� 60*1000/SampleRate > */	
	uint8_t triggerPeriodPoint;				 /**<  ���δ��ڲ��� 10> */	
 	uint16_t samplePointMax;				 /**<  ���ʲ������ֵĬ��4000��> */	
	uint16_t evennessMax;				 /**<  ƽ�������ֵ Ĭ��Ϊ200> */	
	uint16_t waveSampleMax;				 /**<  ȡ���ٵ�����㷨> */	
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

#define  WaveSlopeRange 25		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
#define  HeartRateMAX	160			 /**<   �������ֵ ��ʼΪ160    > */
#define  HeartRateMIN   40			 /**<   ������Сֵ ��ʼΪ40    > */
#define  SampleRate     2				 /**<   ������ Ĭ��Ϊ2ms    > */	
#define  SamplePointTotal 30000		 /**<   ���еĲ����� 60*1000/SampleRate > */	
#define  TriggerPeriodPoint 10				 /**<  ���δ��ڲ��� 10> */	
#define  SamplePointMax     3500				 /**<  ���ʲ������ֵĬ��4000��> */	
#define  EvennessMax 		200		 /**<  ƽ�������ֵ Ĭ��Ϊ200> */	
#define  WaveSampleMax 		4000			 /**<  ȡ���ٵ�����㷨> */	
#define  WaveArrayMax		3		 /**<  ȡ���ٸ����ν��м���> */	
#define  RecDetectData		10		 /**<  ƽ���ȳ��������ж�Ϊ����> */	
#define  PeriodMax  		188			/**< ���������> */	
#define  PeriodMin			750			/**< ��С������> */	
#define  PeakBottomStand	100		/**<   ��ֵ��ֵ          > */	

/* ram define ------------------------------------------------------------------*/


const HEART_RATE_PARAM_T HeartRateParamInit = 
{
		
	WaveSlopeRange,		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
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


HRState heartRateWaveDetect(uint16_t adData) ;







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

