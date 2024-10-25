/**
 * @file       bsp_uart.c
 * @copyright  Copyright (C) 2019 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    0.0.0
 * @date       2024-07-21
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 *
 * @brief      A BSP source code for UART
 *
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_uart.h"
/* Private defines ---------------------------------------------------- */
#define SUCCESS_INIT "Successful Initialization\n"
#define ERROR_MESSAGE "Wrong format\r\n"
/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  UART_HandleTypeDef *huart;
  DMA_HandleTypeDef *hdma_usart_rx;
  uint8_t *uart_tx_buffer;
  uint8_t *uart_rx_buffer;
  uint8_t *uart_main_buffer;
  uint16_t uart_tx_rx_buffer_size;
  uint16_t uart_main_buffer_size;
} bsp_uart_data_t;

typedef enum
{
  FSM_SET_RTC,
  FSM_ALARM_TIME,
  FSM_GET_TIME,
  FSM_START_SONG,
  FSM_STOP_SONG,
  FSM_NEXT_SONG,
  FSM_PREVIOUS_SONG,
  FSM_VOLUME_UP,
  FSM_VOLUME_DOWN
} pc_control_fsm_state_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static bsp_uart_data_t uart_dfp_data;
static bsp_uart_data_t uart_pc_control_data;

static bsp_pc_control_state_t b_pc_control_info;
static uint8_t buart_flag;
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */
bsp_uart_result_t bsp_uart_dfp_init(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx)
{
  uart_dfp_data.hdma_usart_rx = hdma_usart_rx;
  uart_dfp_data.huart = huart;

  uint8_t succes[] = SUCCESS_INIT;
  bsp_uart_dfp_send(succes, sizeof(succes));

  return BSP_UART_SUCCESS;
}

bsp_uart_result_t bsp_uart_dfp_send(uint8_t *data, uint16_t size)
{
  HAL_UART_Transmit(uart_dfp_data.huart, data, size, HAL_MAX_DELAY);
  return BSP_UART_SUCCESS;
}

bsp_uart_result_t bsp_uart_pc_control_init(UART_HandleTypeDef *huart, DMA_HandleTypeDef *hdma_usart_rx)
{
  uart_pc_control_data.huart = huart;
  uart_pc_control_data.hdma_usart_rx = hdma_usart_rx;
  uint8_t succes[] = SUCCESS_INIT;
  bsp_uart_pc_control_send(succes, sizeof(succes));
  return BSP_UART_SUCCESS;
}

bsp_uart_result_t bsp_uart_pc_control_init_buffer(uint8_t *tx_buffer, uint8_t *rx_buffer, uint16_t buffer_size)
{
  uart_pc_control_data.uart_tx_buffer = tx_buffer;
  uart_pc_control_data.uart_rx_buffer = rx_buffer;
  uart_pc_control_data.uart_tx_rx_buffer_size = buffer_size;
  return BSP_UART_SUCCESS;
}

bsp_uart_result_t bsp_uart_start_receive(void)
{
  HAL_UARTEx_ReceiveToIdle_DMA(uart_pc_control_data.huart, uart_pc_control_data.uart_rx_buffer, RX_BUFFER_SIZE);
  __HAL_DMA_DISABLE_IT(uart_pc_control_data.hdma_usart_rx, DMA_IT_HT);
  return BSP_UART_SUCCESS;
}

bsp_uart_result_t bsp_uart_pc_control_send(uint8_t *data, uint16_t size)
{
  HAL_UART_Transmit(uart_pc_control_data.huart, data, size, HAL_MAX_DELAY);
  return BSP_UART_SUCCESS;
}

bsp_pc_control_state_t bsp_uart_pc_control_handle_it(uint16_t Size)
{
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
