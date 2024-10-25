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
#ifndef DRV_UART_MN_DATA_H_
#define DRV_UART_MN_DATA_H_
/* Includes ------------------------------------------------------------------ */
#include "stm32f4xx_hal.h"
#include "drv_rtc.h"
#include <stdio.h>
#include "main.h"
/* Public defines ------------------------------------------------------------ */
/* Public macros ------------------------------------------------------------- */

/* Public variables ---------------------------------------------------------- */

/* Public function prototypes ------------------------------------------------ */
/**
 * @brief Process received data to configure the time on the DS1307 RTC.
 *
 * @param[in] huart UART handle used for transmitting responses.
 * @param[in] data Pointer to the received data buffer.
 * @param[in] size Size of the received data buffer.
 *
 * The data is expected to be in the format: mode-YYYY-MM-DD-HH-MM-SS.
 * The function parses the data and sets the time on the DS1307 RTC.
 */
void uart_process_received_data_config_time(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size);
/**
 * @brief Process data to transmit the current time from the DS1307 RTC.
 *
 * @param[in] huart UART handle used for transmitting the current time.
 * @param[in] data Pointer to the data buffer where the time information is stored.
 * @param[in] size Size of the data buffer.
 *
 * The function retrieves the current time from the DS1307 RTC and formats it
 * for transmission via UART.
 */
void uart_process_transmit_data_get_time(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size);
/**
 * @brief Process received data to configure the alarm time on the DS1307 RTC.
 *
 * @param[in] huart UART handle used for transmitting responses.
 * @param[in] alarm_data Pointer to the received alarm data buffer.
 * @param[in] size Size of the alarm data buffer.
 *
 * The data is expected to be in the format: mode-YYYY-MM-DD-HH-MM-SS.
 * The function parses the data and sets the alarm time on the DS1307 RTC.
 */
void uart_process_received_data_config_alarm(UART_HandleTypeDef *huart, uint8_t *alarm_data, uint16_t size);
/**
 * @brief Notify via UART when the alarm is ringing.
 *
 * @param[in] huart UART handle used for transmitting the alarm notification.
 *
 * The function sends a notification message indicating that the alarm is ringing.
 */
uint8_t ds1307_notify_alarm();
#endif
/* End of file ---------------------------------------------------------------- */
