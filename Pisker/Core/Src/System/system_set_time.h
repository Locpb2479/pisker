/**
 * @file       system_set_time.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 * @brief      System Manager for GPIO Project

 * @note       None
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef SYSTEM_SYSTEM_SET_TIME_C_
#define SYSTEM_SYSTEM_SET_TIME_C_
/* Includes ----------------------------------------------------------- */
#include <drv_btn.h>
#include <stdbool.h>
#include <sys_btn.h>
#include <drv_matrix_led.h>
#include <drv_rtc.h>
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */

typedef enum
{
  SYS_STATE_SET_TIME,
  SYS_STATE_SET_TIME_HOUR,
  SYS_STATE_SET_TIME_MIN,
  SYS_STATE_SET_TIME_SEC,
  SYS_STATE_SET_TIME_HOUR_PLUS_ONE,
  SYS_STATE_SET_TIME_MIN_PLUS_ONE,
  SYS_STATE_SET_TIME_SEC_PLUS_ONE,
  SYS_STATE_CONFIRM_SET_TIME,
  SYS_STATE_FINSH_SET_TIME,

  SYS_STATE_SET_DATE,
  SYS_STATE_SET_DATE_DATE,
  SYS_STATE_SET_DATE_MONTH,
  SYS_STATE_SET_DATE_YEAR,
  SYS_STATE_SET_DATE_DATE_PLUS_ONE,
  SYS_STATE_SET_DATE_MONTH_PLUS_ONE,
  SYS_STATE_SET_TIME_YEAR_PLUS_ONE,
  SYS_STATE_CONFIRM_SET_DATE,
  SYS_STATE_FINSH_SET_DATE,

  SYS_STATE_EXIT

} sys_state_set_time_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
void sys_set_time_init(void);
void sys_set_time_fsm_update(btn_info_t *button_state);
uint32_t sys_set_time_fsm_action();
uint32_t sys_set_time_loop(btn_info_t *button_state);
#endif
/* End of file -------------------------------------------------------- */
