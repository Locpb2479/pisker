/**
 * @file       bsp_uart.h
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    major.minor.patch
 * @date       2024-07-20
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 *
 * @brief      Header file for bsp_uart.c
 *
 * @note
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_UART_H_
#define __BSP_UART_H_
/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "uart_respond_fsm.h"

/* Public defines ----------------------------------------------------- */
#define RX_BUFFER_SIZE 25
#define TX_BUFFER_SIZE 25
#define MAIN_BUFFER_SIZE 20
#define UART_SUCCESS 0x00000000
#define UART_ERROR 0xFFFFFFFF
#define UART_BUSY 0X00000001
#define UART_TIMEOUT 0X00000002

/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  BSP_UART_SUCCESS = 0x00,
  BSP_UART_ERROR,
  BSP_UART_BUSY,
  BSP_UART_TIMEOUT
} bsp_uart_result_t;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
bsp_uart_result_t bsp_uart_pc_control_init(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx);
bsp_uart_result_t bsp_uart_pc_control_start_receive(void);
bsp_uart_result_t bsp_uart_pc_control_send(uint8_t *data, uint16_t size);
bsp_uart_result_t bsp_uart_pc_control_handle_it(uint16_t Size);
bsp_uart_result_t bsp_uart_dfp_init(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx);
bsp_uart_result_t bsp_uart_dfp_send(uint8_t *data, uint16_t size);

/* End of file -------------------------------------------------------- */
#endif /* BSP_UART_H_ */
