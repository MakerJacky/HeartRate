/***************************************************************************************************
	* Copyright (c) 2017
	* All rights reserved.
	* �ļ����ƣ� QuectelM26.h
	* ժ Ҫ��    GSMģ��
	* ��ǰ�汾�� V1.0,SOMMER, 2017-01-05
	* ���ļ�¼�� ��
***************************************************************************************************/

#ifndef _QUECTEL_MC20_H_
#define _QUECTEL_MC20_H_
#include "stm32f10x.h"
#include <stdio.h>

/***************************************************************************************************
//#define   
***************************************************************************************************/
#define		HTTP_time_out	3801
#define		HTTP_busy	3802
#define		HTTP_UART_busy	3803
#define		HTTP_get_no_request	3804
#define		HTTP_network_busy	3805
#define		HTTP_network_open_failed	3806
#define		HTTP_network_no_config	3807
#define		HTTP_network_deactive	3808
#define		HTTP_network_error	3809
#define		HTTP_url_error	3810
#define		HTTP_empty_url	3811
#define		HTTP_ip_addr_error	3812
#define		HTTP_DNS_error	3813
#define		HTTP_socket_create_error	3814
#define		HTTP_socket_connect_error	3815
#define		HTTP_socket_read_error	3816
#define		HTTP_socket_write_error	3817
#define		HTTP_socket_close	3818
#define		HTTP_data_encode_error	3819
#define		HTTP_data_decode_error	3820
#define		HTTP_to_read_timeout	3821
#define		HTTP_response_failed	3822
#define		incoming_call_busy	3823
#define		voice_call_busy	3824
#define		input_timeout	3825
#define		wait_data_timeout	3826
#define		waitHttp_response_timeout	3827
#define		alloc_memory_fail	3828
#define		HTTP_need_relocation	3829
#define		Exceed_max_length	4000
#define		Open_file_fail	4001
#define		Write_file_fail	4002
#define		Get_size_fail	4003
#define		Read_fail	4004
#define		List_file_fail	4005
#define		Delete_file_fail	4006
#define		Get_Disk_info_fail	4007
#define		No_space	4008
#define		Time_out	4009
#define		File_not_found	4010
#define		File_too_large	4011
#define		File_already_exist	4012
#define		Invalid_parameter	4013
#define		Driver_error	4014
#define		Create_fail	4015
#define		Access_denied	4016
#define		Files_too_large	4017


#define RX_BUF_MAX_LEN     256                                     //�����ջ����ֽ���

#define ERROR_STR_MAX     8  
#define MAX_SIZE     16  





#define     MC20_Usart( fmt, ... )           USART2_printf (  fmt, ##__VA_ARGS__ ) 
#define     MC20_UsartByte( fmt, len )           USART2_printfByte (  fmt, len) 



/***************************************************************************************************
//#CONST
***************************************************************************************************/


/***************************************************************************************************
//#ENUM
***************************************************************************************************/
typedef enum
{
    MC20_OK       =          0,                            //OK
    STRING_ERR    =          1,                            //��Ԥ�ڷ����ַ���
    CONNECT_ERR   =          2,                              //��ģ�����Ӵ���
    QUERY_BAUD_ERR   =       3,                             //�����ʴ���
    CLOSE_SOCKET_ERR   =     4,                             //�ر�SOCKET����
    CLOSE_CONTEXT_ERR   =    5,                            //�ر�CONTEXT����
    SQ_ERR   =               6,                           //�źŲ�ѯ����
    REG_ERR   =              7,                           //����ע��ʧ��
    GREG_ERR   =             8,                           //GPRS����ʧ��
    SET_CONTEXT_ERR   =      9,                           //����CONTEXT����
    ACT_CONTEXT_ERR   =      10,                           //����CONTEXT����
    QUERY_ACT_ERR   =        11,                           //��ѯ����ʧ��
    SET_SOCKET_ERR   =       12,                           //����SOCKETʧ��
    ENTER_DATA_MODE_ERR   =  13,                           //����ģʽ����
    QUERY_SOCKET_ERR   =     14,                           //��ѯSOCKETʧ��
    RESET_ERR   =            15,                           //��λʧ��
    DEFAULT_ERR   =          16,                           //Ĭ�ϴ���
    QUERY_PIN_ERR   =        17,                          //��SIM������SIM����PIN��
    BACK_TO_TRAN_ACCESS_MODE_ERR   =  18,                 //��ģ�����Ӵ���
    OVER_TIME   =          19    ,                           //��ʱ����
    RESP_ERR   =          20    ,                        // CMD resp error
    STRING_NULL = 21,
      GSM_IMEI_ERR = 22,
      SIM_NOT_READY = 23,
      GSM_NUM_ERR = 24,
      CSQ_ERR		= 25,
	CREG_ERR = 26,
		CGREG_ERR = 27,
		GET_GNSS_ERR = 28,
		GSM_NUM_FLOAT_ERR = 29,
} MC20_RESP;



typedef enum
{

	UNKONW_STATE		=  -1,
    IP_INITIAL      =  0,  // IP INITIAL
    IP_START        =	1,
    IP_CONFIG       =	2,
    IP_IND			=   3,	
    IP_GPRSACT		=	4, // IP GPRSACT
	IP_STATUS       =	5,	//IP STATUS
	CONNECTING		= 	6,	//CONNECTING
	IP_CLOSE		=	7,		//CONNECT CLOSE
    CONNECT_OK		=	8,		// CONNECT OK
    PDP_DEACT       =	9,
    NO_RESP			= 10,		// NO RESP
}GSM_STATE;


/***************************************************************************************************
//#STRUCT
***************************************************************************************************/  
    
typedef struct  STRUCT_GSM_ERROR    					   //������������                        
{
	char  type;
    u16 code;                           
    char  detail[ ERROR_STR_MAX ];                      
	
}GSM_ERROR;      


typedef struct  STRUCT_USARTx_Frame                                  //��������֡�Ĵ���ṹ��
{
	char  FrameBuffer[ RX_BUF_MAX_LEN ];
    u16 FramLength;                           
    u8  FramFinishFlag   ;                              
	
} USARTX_Frame_REC;







typedef struct STRUCT_AGPS_DATA
{
	
	u8 valid;
	float Latitude;//����ԭ����
	float Longitude;//γ��Դ����
	
}AGPS_Data;


typedef struct STRUCT_GSM_RESP{
	u8 state;
	char respCmd[32];
	char respData[16][32];
	char dataLen;
} GSM_RESP;


typedef struct STRUCT_GNRMC_Info{ 
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 Minute;
	u8 second;
	
	double longitude; // ����
	u8 longitude_suffix; // ���Ȱ���E(����)��W(����)

	double latitude; // γ��
	u8 latitude_suffix; // γ�Ȱ���N(������)��S(�ϰ���)
	u8 position_valid; // ��λ�Ƿ���Ч

}GNRMC_Info;


/***************************************************************************************************
//#RAM
***************************************************************************************************/
extern USARTX_Frame_REC MC20_Frame_Rec ;



/***************************************************************************************************
//#PROGRAM define
***************************************************************************************************/
int GNRMC_Parse(unsigned char* pstr, GNRMC_Info* pGNRMCInfo );



u8 getResError(char *str,char *rep1, char * rep2);
u8 removeSpecial(char s[],u16 len,char t[]);



void testATCommand(void);


 void QuectelMC20_SendCmd( const char *string);
extern u8 QuectelMC20_ContextPrepare(void);
extern u8 QuectelMC20_Comm_Send(char *buff);


//static u8   getGSMAckData(char *str, u16 overtime);

u8 sendHttpPostData(char *data,int len);

u8 sendSocketData(uint8_t *data,int32_t len);

u8 OPEN_MC20(void);
u8 MC20_Init(void);
uint8_t gsmNetRegistor(void);
uint8_t contextAction(void);


u8 connectSocket(void);
u8 closeSocket(void);
u16 getGSMRecData(char *str, u16 overtime);
u8 getQuecLocatorAGPS(GNRMC_Info *GNRMC);
u8 getGnssData(GNRMC_Info *GNRMC);
GSM_STATE getGSMState(void);
void clrRecBuffer(void);
void printArray(char * data,int len);
#endif
