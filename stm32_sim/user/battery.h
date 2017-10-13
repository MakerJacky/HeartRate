/***************************************************************************************************
	* Copyright (c) 2017
	* All rights reserved.
	* ???????? battery.h
	* ? ???    GSM???
	* ????汾?? V1.0,SOMMER, 2017-01-05
	* ???????? ??
***************************************************************************************************/

#ifndef _BATTERY_H_
#define _BATTERY_H_
#include "stm32f10x.h"
#include <stdio.h>
#include "quectel_mc20.h"
#include "bsp_rtc.h"
/***************************************************************************************************
//#define   
***************************************************************************************************/
/***************************************************************************************************
//#STRUCT
***************************************************************************************************/  
typedef struct STRUCT_BATTERY_REPORT
{
	char  name[16];
	double  level;
	GNRMC_Info gnrmc_info;
	u8	type;
	UTC_TIME	time;
}BATTERY_REPORT;



int getBatteryMsgData(char *str,BATTERY_REPORT battery);

/***************************************************************************************************
//#PROGRAM define
***************************************************************************************************/


#endif
