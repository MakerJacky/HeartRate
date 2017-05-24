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
#include "stm32f10x.h"
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
	uint16_t WaveSlopeRange;		  /**< ��ݲ��жϱ�׼��ʼΪ200 > */
	uint8_t  HeartRateMAX;				 /**<   �������ֵ ��ʼΪ160    > */
	uint8_t	HeartRateMIN;				 /**<   ������Сֵ ��ʼΪ40    > */
	uint16_t SampleRate;				 /**<   ������ Ĭ��Ϊ2ms    > */	
	uint16_t SamplePointTotal;			 /**<   ���еĲ����� 60*1000/SampleRate > */	
	uint8_t TriggerPeriodPoint;				 /**<  ���δ��ڲ��� 10> */	
 	uint16_t SamplePointMax;				 /**<  ���ʲ������ֵĬ��4000��> */	
	uint16_t EvennessMax;				 /**<  ƽ�������ֵ Ĭ��Ϊ200> */	
	uint16_t WaveSampleMax;				 /**<  ȡ���ٵ�����㷨> */	
	uint16_t WaveArrayMax;				 /**<  ȡ���ٸ����ν��м���> */	
	uint16_t RecDetectData;				 /**<  ƽ���ȳ��������ж�Ϊ����> */	
	uint16_t PeriodMax;					/**< ���������> */	
	uint16_t PeriodMin;					/**< ��С������> */	
	uint16_t PeakBottomStand;			/**<   ��ֵ��ֵ          > */	
} HEART_RATE_PARAM_T, *HEART_RATE_PARAM_INDEX;


typedef struct SLOPE
{
	uint16_t value;		
	SlopeDirection  direction;			
	uint8_t smooth;
} SLOPE_T, *SLOPE_INDEX;



/* ram define ------------------------------------------------------------------*/


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

