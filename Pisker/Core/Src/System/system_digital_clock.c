/**
 * @file       system_digital_clock.c
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
#include <system_digital_clock.h>
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
sys_state_digital_clock_t s_state_digital_clock;

/* Private variables -------------------------------------------------- */
void sys_digital_clock_fsm_update(btn_info_t *button_state);
uint32_t sys_digital_clock_fsm_action();
/* Private function prototypes ---------------------------------------- */
void sys_digital_clock_init(void)
{
  s_state_digital_clock = SYS_STATE_DIGITAL_CLOCK;
}

void sys_digital_clock_fsm_update(btn_info_t *button_state)
{
  switch (s_state_digital_clock)
  {
  case SYS_STATE_DIGITAL_CLOCK:
    if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_digital_clock = SYS_STATE_DATE_TIME;
    break;
  case SYS_STATE_DATE_TIME:
    if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_digital_clock = SYS_STATE_DIGITAL_CLOCK;
    break;

  default:
    break;
  }
}

uint32_t sys_digital_clock_fsm_action()
{
  switch (s_state_digital_clock)
  {

  case SYS_STATE_DIGITAL_CLOCK:
    drv_matrix_led_digital_clock();
    break;
  case SYS_STATE_DATE_TIME:
    drv_matrix_led_date_time();
    break;
  default:
    break;
  }
  return 0;
}

void sys_digital_clock_loop(btn_info_t *button_state)
{
  sys_digital_clock_fsm_update(button_state);
  sys_digital_clock_fsm_action();
}
