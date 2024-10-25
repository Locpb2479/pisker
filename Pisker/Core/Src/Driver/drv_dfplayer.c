/**
 * @file       drv_dfplayer.c
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @version    1.0.0
 * @date       2024-07-06
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 *
 * @brief      Button Driver
 *             The driver for button in STM32F411
 *
 * @note
 */
/* Includes ----------------------------------------------------------- */
#include "drv_dfplayer.h"

/* Private defines ---------------------------------------------------- */
#define START_BYTE 0x7E
#define END_BYTE 0xEF
#define VERSION 0xFF
#define CMD_LEN 0x06
#define FEEDBACK 0x00
#define SOURCE 0x02
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
void drv_df_send_cmd(uint8_t cmd, uint8_t param1, uint8_t param2);
static uint8_t drv_df_volume;
/* Private definitions ----------------------------------------------- */
drv_dfplayer_status_t drv_df_playfromstart(void)
{
  drv_df_send_cmd(0x03, 0x00, 0x01);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}
drv_dfplayer_status_t drv_df_init(uint8_t volume)
{
  drv_df_send_cmd(0x0C, 0x00, 0x00);
  HAL_Delay(200);
  drv_df_send_cmd(0x3F, 0x00, SOURCE);
  HAL_Delay(200);
  drv_df_send_cmd(0x06, 0x00, volume);
  drv_df_volume = volume;
  HAL_Delay(500);
  return DRV_DFPLAYER_OK;
}
drv_dfplayer_status_t drv_df_next(void)
{
  drv_df_send_cmd(0x01, 0x00, 0x00);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}
drv_dfplayer_status_t drv_df_pause(void)
{
  drv_df_send_cmd(0x0E, 0, 0);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}
drv_dfplayer_status_t drv_df_previous(void)
{
  drv_df_send_cmd(0x02, 0, 0);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}
drv_dfplayer_status_t drv_df_playback(void)
{
  drv_df_send_cmd(0x0D, 0, 0);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}

drv_dfplayer_status_t drv_df_playrandom(void)
{
  drv_df_send_cmd(0x18, 0x00, 0x00);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}

void drv_df_send_cmd(uint8_t cmd, uint8_t param1, uint8_t param2)
{
  uint16_t checksum = VERSION + CMD_LEN + cmd + FEEDBACK + param1 + param2;
  checksum = 0 - checksum;
  uint8_t cmd_sequence[10] = {START_BYTE, VERSION, CMD_LEN, cmd, FEEDBACK, param1, param2, (checksum >> 8) & 0x00ff, (checksum & 0x00ff), END_BYTE};
  bsp_uart_dfp_send(cmd_sequence, 10);
}

drv_dfplayer_status_t drv_df_playfile(uint8_t file_number)
{
  drv_df_send_cmd(0x03, 0x00, file_number);
  HAL_Delay(200);
  return DRV_DFPLAYER_OK;
}

drv_dfplayer_status_t drv_df_up_volume()
{
  drv_df_volume += 5;
  if(drv_df_volume > 30)
    {
      drv_df_volume = 30;
    }
  drv_df_send_cmd(0x06, 0x00, drv_df_volume);
    HAL_Delay(500);
    return DRV_DFPLAYER_OK;
}

drv_dfplayer_status_t drv_df_down_volume()
{
  drv_df_volume -= 5;
  if(drv_df_volume < 0)
    {
      drv_df_volume = 0;
    }
  drv_df_send_cmd(0x06, 0x00, drv_df_volume);
    HAL_Delay(500);
    return DRV_DFPLAYER_OK;
}
