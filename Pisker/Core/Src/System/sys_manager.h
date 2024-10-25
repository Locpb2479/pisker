/**
 * @file       sys_manager.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-08-03
 * @author     Tin Lu Trung
 *
 * @brief      System to manage the system
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef SYS_MANAGER_H_
#define SYS_MANAGER_H_
/* Includes ----------------------------------------------------------- */
#include "drv_btn.h"
#include "drv_rtc.h"
#include "drv_matrix_led.h"
#include "fft_handle.h"

#include <system_set_alarm.h>
#include <system_set_time.h>
#include "sys_sound.h"
#include "system_display.h"

#include "bsp_i2c.h"
#include "bsp_uart.h"
#include "frame.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
/* Public defines ----------------------------------------------------- */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_MANAGER_OK,
  SYS_MANAGER_ERROR
} sys_manger_error_t;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief Init system manager
 *
 * @return system_manager_error_t
 */
sys_manger_error_t sys_manager_init(void);

/**
 * @brief Run system manager
 *
 * @param button_state
 *
 * @return
 *  - SYS_MANAGER_OK 	: system manager ok
 *  - SYS_MANAGER_ERROR : system manager error
 */
sys_manger_error_t sys_manager_run(btn_info_t *button_state);

/* End of file -------------------------------------------------------- */
#endif /* SYS_MANAGER_H_ */
