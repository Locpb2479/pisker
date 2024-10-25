/**
 * @file        drv_uart_mn_rec_data.h
 * @brief       Header file for RTC driver
 * @version     0.0.0
 * @date        [Insert Date]
 * @author      Lu Trung Tin
 *              Nguyen Nhat Tri
 *              Pham Bao Loc
 *
 * This file contains definitions and function prototypes for interfacing with the RTC (Real-Time Clock).
 */
/* Define to prevent recursive inclusion ------------------------------------- */
#ifndef UART_RESPOND_FSM_H_
#define UART_RESPOND_FSM_H_
/* Includes ------------------------------------------------------------------ */
#include "stm32f4xx_hal.h"
#include "drv_uart_mn_rec_data.h"
/* Public defines ------------------------------------------------------------ */
/* Public macros ------------------------------------------------------------- */

/* Public variables ---------------------------------------------------------- */
/* Public enumerations/structures -------------------------------------------- */
typedef enum
{
    FSM_SET_TIME,
    FSM_ALARM_TIME,
    FSM_GET_TIME,
    FSM_START_SONG,
    FSM_STOP_SONG,
    FSM_NEXT_SONG,
    FSM_PREVIOUS_SONG,
    FSM_VOLUME_UP,
    FSM_VOLUME_DOWN
} rtc_fsm_time_t;
/* Public function prototypes ------------------------------------------------ */

/**
 * @brief Process received data to handle finite state machine (FSM) operations.
 *
 * @param[in] huart UART handle used for transmitting responses or notifications.
 * @param[in] data Pointer to the received data buffer.
 * @param[in] size Size of the received data buffer.
 *
 * The function parses the received data and performs FSM operations based on the data content.
 * This include configuring time, setting alarms, or other FSM-related tasks.
 */

void fsm_process_received_data(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size);

#endif /* UART_RESPOND_FSM_H_ */
