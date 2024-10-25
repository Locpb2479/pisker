/*
 * uart_respond_fsm.c
 *
 *  Created on: Jul 23, 2024
 *      Author: Tri Nguyen
 */

#include "uart_respond_fsm.h"
#include "drv_uart_mn_rec_data.h"
#include "drv_rtc.h"
#include "drv_dfplayer.h"

void fsm_process_received_data(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
// Ensure the received data is in the correct format: mode-YYYY-MM-DD-HH-MM-SS
#ifdef DEBUG_
  if ((size != 25) || (data[5] != '-') || (data[10] != '-') || (data[13] != '-') || (data[16] != '-') || (data[19] != '-') || (data[22] != '-'))
  {

    const char *error_msg = "Wrong format\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
    return; // Incorrect format
  }
#endif

  rtc_fsm_time_t fsm_state;

  // Determine the FSM state based on the mode
  if (strncmp((char *)data, "stime", 5) == 0)
  {
    fsm_state = FSM_SET_TIME;
  }
  else if (strncmp((char *)data, "alarm", 5) == 0)
  {
    fsm_state = FSM_ALARM_TIME;
  }
  else if (strncmp((char *)data, "gtime", 5) == 0)
  {
    fsm_state = FSM_GET_TIME;
  }
  else if (strncmp((char *)data, "start", 5) == 0)
  {
    fsm_state = FSM_START_SONG;
  }
  else if (strncmp((char *)data, "sstop", 5) == 0)
  {
    fsm_state = FSM_STOP_SONG;
  }
  else if (strncmp((char *)data, "snext", 5) == 0)
  {
    fsm_state = FSM_NEXT_SONG;
  }
  else if (strncmp((char *)data, "sprev", 5) == 0)
  {
    fsm_state = FSM_PREVIOUS_SONG;
  }
  else if (strncmp((char *)data, "volup", 5) == 0)
  {
    fsm_state = FSM_VOLUME_UP;
  }
  else if (strncmp((char *)data, "voldw", 5) == 0)
  {
    fsm_state = FSM_VOLUME_DOWN;
  }
  else
  {
    const char *error_msg = "Unknown mode\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
    return;
  }

#ifdef DEBUG_
  ds1307_time_t time;
  time.ds1307_year = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
  time.ds1307_month = (data[11] - '0') * 10 + (data[12] - '0');
  time.ds1307_date = (data[14] - '0') * 10 + (data[15] - '0');
  time.ds1307_hour = (data[17] - '0') * 10 + (data[18] - '0');
  time.ds1307_minute = (data[20] - '0') * 10 + (data[21] - '0');
  time.ds1307_second = (data[23] - '0') * 10 + (data[24] - '0');
  time.ds1307_day = 1; // Default to Monday or adjust if needed
#endif

  switch (fsm_state)
  {
  case FSM_SET_TIME:
    uart_process_received_data_config_time(huart, (uint8_t *)data, size);
    break;

  case FSM_ALARM_TIME:
    uart_process_received_data_config_alarm(huart, (uint8_t *)data, size);
    break;

  case FSM_GET_TIME:
    uart_process_transmit_data_get_time(huart, (uint8_t *)data, size);
    break;

  case FSM_START_SONG:
    // Handle start song
    drv_df_playfromstart();
    break;

  case FSM_STOP_SONG:
    // Handle stop song
    drv_df_pause();
    break;

  case FSM_NEXT_SONG:
    // Handle next song
    drv_df_next();
    break;

  case FSM_PREVIOUS_SONG:
    // Handle previous song
    drv_df_previous();
    break;

  case FSM_VOLUME_UP:
    // Handle volume up
    drv_df_up_volume();
    break;

  case FSM_VOLUME_DOWN:
    // Handle volume down
    drv_df_down_volume();
    break;

  default:
    const char *error_msg_default = "Unhandled FSM state\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)error_msg_default, strlen(error_msg_default), HAL_MAX_DELAY);
    break;
  }
}
#ifdef DEBUG_
void fsm_notify_alarm(UART_HandleTypeDef *huart)
{
  const char *alarm_msg = "Alarm ringing!\r\n";
  HAL_UART_Transmit(huart, (uint8_t *)alarm_msg, strlen(alarm_msg), HAL_MAX_DELAY);
}
#endif
