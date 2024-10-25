/**
 * @file       system_set_alarm.h
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
#ifndef SYSTEM_SYSTEM_SET_ALARM_C_
#define SYSTEM_SYSTEM_SET_ALARM_C_
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
  SYS_STATE_CONFIRM_ALARM,
  SYS_STATE_SET_ALARM_HOUR,
  SYS_STATE_SET_ALARM_MIN,
  SYS_STATE_SET_ALARM_SEC,
  SYS_STATE_SET_ALARM_HOUR_PLUS_ONE,
  SYS_STATE_SET_ALARM_MIN_PLUS_ONE,
  SYS_STATE_SET_ALARM_SEC_PLUS_ONE,
  SYS_STATE_SET_ALARM_FINISH,
  SYS_STATE_DELETE_ALARM
} sys_state_set_alarm_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the alarm setting system.
 *
 * This function sets up the necessary components for configuring
 * the alarm. It initializes any required hardware or software
 * resources to allow the user to set and configure the alarm time.
 */
void sys_set_alarm_init(void);

/**
 * @brief Manages alarm setting operations in the main loop.
 *
 * This function should be called regularly in the main loop to
 * handle user interactions for setting the alarm. It checks the
 * state of the buttons and updates the alarm time accordingly,
 * allowing the user to navigate and configure the alarm settings.
 *
 * @param button_state Pointer to a btn_info_t structure that holds
 *                     the current state of the buttons.
 */
void sys_set_alarm_loop(btn_info_t *button_state);
#endif
/* End of file -------------------------------------------------------- */
