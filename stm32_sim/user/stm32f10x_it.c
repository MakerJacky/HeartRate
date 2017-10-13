/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <stdio.h>
#include "bsp_SysTick.h"
#include "quectel_mc20.h"
#include "bsp_gpio.h"   
#include "stm32f10x_rtc.h"
//extern void TimingDelay_Decrement(void);
//extern void USART2_printf(USART_TypeDef* USARTx, char *Data,...);


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TimingDelay_Decrement();	
}


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
/**
  * @brief  This function handles USART2 Handler.
  * @param  None
  * @retval None
  */
 #if 0
void USART2_IRQHandler( void )
{	


	char ch;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		ch  = USART_ReceiveData( USART2 );
		TIM_SetCounter(TIM3,0);
		if( MC20_Fram_Record  .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //Ԥ��1���ֽ�д������
		{
				MC20_Fram_Record .Data_RX_BUF [ MC20_Fram_Record  .FramLength ++ ]  = ch;

		}
		
	}
	 	 
	if ( USART_GetITStatus( USART2, USART_IT_IDLE ) == SET )                                         //����֡�������
	{
	
    MC20_Fram_Record  .FramFinishFlag = 1;
		
		ch = USART_ReceiveData( USART2 );                                                              //�������������жϱ�־λ(�ȶ�USART_SR��Ȼ���USART_DR)
	
  }	

 
}


void USART1_IRQHandler(void)      //����1 �жϷ������
{




  	char ch;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		ch  = USART_ReceiveData( USART1 );
		
		
		if( MC20_Fram_Record  .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //Ԥ��1���ֽ�д������
		{
				MC20_Fram_Record .Data_RX_BUF [ MC20_Fram_Record  .FramLength ++ ]  = ch;

		}
		if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_8)){
			LED2_ON;
			}else {
			LED2_OFF;
			}
	}

	 	 
	if ( USART_GetITStatus( USART1, USART_IT_IDLE ) != RESET )                                         //����֡�������
	{
	
    MC20_Fram_Record  .FramFinishFlag = 1;
		
		ch = USART_ReceiveData( USART1 );   
		if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_6)){
			LED3_ON;
			}else {
			LED3_OFF;
			}
	}

}
#endif

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{

  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
    {
   	GPIO_WriteBit(GPIOB,GPIO_Pin_0, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0)));
    }
    RTC_ClearITPendingBit(RTC_IT_SEC); 
  RTC_WaitForLastTask();
//char os_str[512];
 // sprintf( os_str,    "RTC irq \0");
		
	//OLED_ShowStr(0,0,os_str,1);
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/



void TIM3_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  ); 
	//	  MC20_Fram_Record  .FramFinishFlag = 1;
		TIM_Cmd(TIM3,DISABLE);
		/*
		if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5)){
			LED4_ON;
			}else {
			LED4_OFF;
			}
		*/
		}
		
}





/**
  * @}
  */ 
void EXTI1_IRQHandler(void)
{	   

	
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
