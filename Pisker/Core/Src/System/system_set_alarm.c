/**
 * @file       system_set_alarm.c
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @version    1.0.0
 * @date       2024-07-06
 * @author     <first_name_1> <last_name_1>
 * @author     <first_name_2> <last_name_2>
 * @author     <first_name_2> <last_name_2>
 *
 * @brief      Button Driver
 *             The driver for button in STM32F411
 *
 * @note
 */
/* Includes ----------------------------------------------------------- */
#include <system_set_alarm.h>
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
sys_state_set_alarm_t s_state_set_alarm;
sys_state_set_alarm_t s_state_set_alarm_temp;
/* Private variables -------------------------------------------------- */
void sys_set_alarm_fsm_update(btn_info_t *button_state);
uint32_t sys_set_alarm_fsm_action();
/* Private function prototypes ---------------------------------------- */
void sys_set_alarm_init(void)
{
  s_state_set_alarm = SYS_STATE_SET_ALARM_SEC;
}

void sys_set_alarm_fsm_update(btn_info_t *button_state)
{
  switch (s_state_set_alarm)
  {
  case SYS_STATE_SET_ALARM_HOUR:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_alarm = SYS_STATE_SET_ALARM_MIN;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_alarm = SYS_STATE_CONFIRM_ALARM;
    else if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_set_alarm = SYS_STATE_SET_ALARM_HOUR_PLUS_ONE;
    break;
  case SYS_STATE_SET_ALARM_MIN:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_alarm = SYS_STATE_SET_ALARM_SEC;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_alarm = SYS_STATE_CONFIRM_ALARM;
    else if (*button_state == SINGLE_CLICK_BUTTON)
    {
      s_state_set_alarm = SYS_STATE_SET_ALARM_MIN_PLUS_ONE;
    }
    break;
  case SYS_STATE_SET_ALARM_SEC:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_alarm = SYS_STATE_SET_ALARM_HOUR;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_alarm = SYS_STATE_CONFIRM_ALARM;
    else if (*button_state == SINGLE_CLICK_BUTTON)
    {
      s_state_set_alarm = SYS_STATE_SET_ALARM_SEC_PLUS_ONE;
    }
    break;
  case SYS_STATE_SET_ALARM_HOUR_PLUS_ONE:
    s_state_set_alarm = SYS_STATE_SET_ALARM_HOUR;
    break;
  case SYS_STATE_SET_ALARM_MIN_PLUS_ONE:
    s_state_set_alarm = SYS_STATE_SET_ALARM_MIN;
    break;
  case SYS_STATE_SET_ALARM_SEC_PLUS_ONE:
    s_state_set_alarm = SYS_STATE_SET_ALARM_SEC;
    break;
  case SYS_STATE_CONFIRM_ALARM:
    s_state_set_alarm = SYS_STATE_SET_ALARM_FINISH;
    break;
  case SYS_STATE_SET_ALARM_FINISH:
    s_state_set_alarm = SYS_STATE_SET_ALARM_HOUR;
    break;
  default:
    break;
  }
}

uint32_t sys_set_alarm_fsm_action()
{
  switch (s_state_set_alarm)
  {

  case SYS_STATE_SET_ALARM_HOUR:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_HOUR);
    break;
  case SYS_STATE_SET_ALARM_MIN:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_MIN);
    break;
  case SYS_STATE_SET_ALARM_SEC:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_SEC);
    break;
  case SYS_STATE_SET_ALARM_HOUR_PLUS_ONE:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_HOUR_PLUS_ONE);
    break;
  case SYS_STATE_SET_ALARM_MIN_PLUS_ONE:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_MIN_PLUS_ONE);
    break;
  case SYS_STATE_SET_ALARM_SEC_PLUS_ONE:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_SEC_PLUS_ONE);
    break;
  case SYS_STATE_CONFIRM_ALARM:
    drv_led_matrix_set_alarm_interactive(D_LED_MATRIX_ALARM_NEXT);
    break;
  case SYS_STATE_SET_ALARM_FINISH:
    return SYS_STATE_SET_ALARM_FINISH;
    break;
  default:
    break;
  }
  return 0;
}

void sys_set_alarm_loop(btn_info_t *button_state)
{
  sys_set_alarm_fsm_update(button_state);
  sys_set_alarm_fsm_action();
}
