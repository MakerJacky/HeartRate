/**
****************************************************************************
* @file    app_timer.h
* @brief
* @author  wanli.han
* @version Initial Draft
* @date    2016/11/17
* @history
* @note
* detailed description:

******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT 2016 maxscend </center></h2>
*/
#ifndef __APP_TIMER_H__
#define __APP_TIMER_H__

#include "list.h"
#include "mxd2660_rtc.h"


typedef void (*timer_out_handler)(void *param);


#define TIMER_BIG  		(1)
#define TIMER_EQUAL 	(0)
#define TIMER_LITTLE    (0xFF)


#define TIMER_RETURN_CODE_BASE            (0)
#define TIMER_SUCCESS                     (TIMER_RETURN_CODE_BASE + 0)  ///< successful command
#define TIMER_INVALID_PARAM               (TIMER_RETURN_CODE_BASE + 1)  ///< parameter invallid
#define TIMER_INVALID_STATE               (TIMER_RETURN_CODE_BASE + 2)  ///< no free timer to use

/*******************************************************
1.����δ��ʼ������timer������TIMER_NOT_INIT״̬
2.����timer_create֮��״̬�޸�ΪTIMER_INIT��������ڷ�DELETE״̬���޸�״̬ΪTIMER_START
3.�����������е�timer����TIMER_RUNNING״̬������RUNNING״̬�仯��INIT START STOP״̬
4.���е���timer_stop֮���״̬��ΪTIMER_STOP״̬����ʱδ��������ɾ��
5.��������ɾ����timer����TIMER_DELETE״̬������TIMER_DELETE״̬����timer_create
6.��������״̬����ΪTIMER_INIT״̬
7.��������ȹ����У��������������ɾ���ڵ㣬����������½ڵ�
8.����ɾ���������������ɺ�ͳһִ��
9.�����ڲ�״̬�����ڵ���callback֮ǰ����
10.�������е�״̬ΪTIMER_START��TIMER_STOP��TIMER_RUNNING
*******************************************************/
typedef enum
{
    TIMER_NOT_INIT = 0,       /**< The timer has been allocated. never run into timer_create*/
    TIMER_INIT,               /**< The timer node has been allocated. */
    TIMER_START,              /**< The timer is call timer_start, will add to running list soon. */
    TIMER_RUNNING,            /**< The timer is running. */
    TIMER_STOP,               /**< The timer is be stop, but not delete form list. */
    TIMER_DELETE,             /**< The timer node has been delete from list. or */
}TIMER_RUN_STATE;

typedef enum
{
    APP_TIMER_MODE_ONCE,     /**< The timer will expire only once. */
    APP_TIMER_MODE_REPEATED,      /**< The timer will restart each time it expires. */
    APP_TIMER_MODE_MAX
}TIMER_MODE;


typedef struct timer_node
{
    struct timer_node *next;
    TIMER_MODE mode;     /**< work mode. */
    TIMER_RUN_STATE state;  /**< Timer state. */
    uint16 end_high;    /**< timerout compare low value. */
    uint32 end_low;     /**< timerout compare low value. */
    uint32 offset;      /**< compare increment. */
    void *p_context;    /**< parameter point. */
    timer_out_handler p_handle; /**< timerout callback function. */
}timer_node_t;


#define TIMER_LOG_DEBUG_EN   0
#if TIMER_LOG_DEBUG_EN
#define timer_log(addr,data)  LOG(addr,data)
#else
#define timer_log(addr,data)
#endif

/**
* @brief  app timer initialize function,before use rtc timer, please call this function
* @param  none
* @return none
*/
extern void timer_init(void);

/**
* @brief  create one timer
* @param  p_timer_id if create the timer successed, this point will save the new timer id
*         mode work mode
*         timeout_handler callback function after the timer is arrived
* @return APP_TIMER_SUCCESS create success
*         APP_TIMER_INVALID_PARAM parameter invalid
*         APP_TIMER_NO_MEM all the timer is be using
*/
extern uint8 timer_create(timer_node_t *timer, TIMER_MODE mode, timer_out_handler handler);

/**
* @brief  start the timer
* @param  timer timer_node_t point that the timer should be initialized
*         ms timer out value unit ms,0~131072000ms
*         p_context point to the parameter when the timerout happened will send to the timerout handler
* @return APP_TIMER_SUCCESS start successed
*         APP_TIMER_INVALID_STATE timer state is invalid
*         APP_TIMER_INVALID_PARAM parameter invalid
*/
extern uint8 timer_start(timer_node_t *timer, uint64 ms, void *p_context);

/**
* @brief  stop one timer, after this, the timer can be restart
* @param  timer point to the timer will be stop
* @return none
*/
extern void timer_stop(timer_node_t *timer);

/**
* @brief  delete one timer, after this, the timer cannot be restart
* @param  timer point to the timer will be delete
* @return none
*/
extern void timer_delete(timer_node_t *timer);

/**
* @brief  add the timer that runned, and the end counter is setted
* @param  timer point to one timer node
* @return none
*/
extern uint8 timer_add(timer_node_t *timer);

/**
* @brief  rtc channel1 interrupt call this function, to find which timer is end and call the callback function
* @param  none
* @return none
*/
extern void timerout_handler(void);

/**
* @brief  handle rtc counter overflow interrupt, minus running timer high counter
* @param  none
* @return none
*/
extern void timeroverflow_handler(void);

/**
* @brief  check withc compare is big
* @param
* @return 0--A==B, 1--A>B, 0xFF--A<B
*/
extern uint8 rtc_check_big_compare(uint16 highA, uint16 highB, uint32 lowA, uint32 lowB);

#endif

