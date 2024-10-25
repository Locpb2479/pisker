/**
 * @file        system_set_time.c
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Lu Trung Tin
 *              Nguyen Nhat Tri
 *              Pham Bao Loc
 * @brief       none
 *
 * @note        none
 *
 * @example     none
 *
 */
/* Define to prevent recursive inclusion ------------------------------ */
/* Includes ----------------------------------------------------------- */
#include <system_set_time.h>
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
sys_state_set_time_t s_state_set_time;
sys_state_set_time_t s_state_set_time_temp;
sys_state_set_time_t check_set_finish;
d_rtc_t set_time;
d_rtc_t set_date;
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
void sys_set_time_init(void)
{
  s_state_set_time = SYS_STATE_SET_DATE;
}
void sys_set_time_fsm_update(btn_info_t *button_state)
{
  switch (s_state_set_time)
  {
  case SYS_STATE_SET_TIME:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_DATE;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_EXIT;
    else if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_TIME_HOUR;
    break;
  case SYS_STATE_SET_TIME_HOUR:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_TIME_MIN;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_CONFIRM_SET_TIME;
    else if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_TIME_HOUR_PLUS_ONE;
    break;
  case SYS_STATE_SET_TIME_MIN:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_TIME_SEC;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_CONFIRM_SET_TIME;
    else if (*button_state == SINGLE_CLICK_BUTTON)
    {
      s_state_set_time = SYS_STATE_SET_TIME_MIN_PLUS_ONE;
    }
    break;
  case SYS_STATE_SET_TIME_SEC:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_TIME_HOUR;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_CONFIRM_SET_TIME;
    else if (*button_state == SINGLE_CLICK_BUTTON)
    {
      s_state_set_time = SYS_STATE_SET_TIME_SEC_PLUS_ONE;
    }
    break;
  case SYS_STATE_SET_TIME_HOUR_PLUS_ONE:
    s_state_set_time = SYS_STATE_SET_TIME_HOUR;
    break;
  case SYS_STATE_SET_TIME_MIN_PLUS_ONE:
    s_state_set_time = SYS_STATE_SET_TIME_MIN;
    break;
  case SYS_STATE_SET_TIME_SEC_PLUS_ONE:
    s_state_set_time = SYS_STATE_SET_TIME_SEC;
    break;
  case SYS_STATE_CONFIRM_SET_TIME:
    s_state_set_time = SYS_STATE_SET_TIME;
    break;
  case SYS_STATE_FINSH_SET_TIME:
    s_state_set_time = SYS_STATE_SET_TIME;
    break;
  case SYS_STATE_SET_DATE:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_TIME;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_EXIT;
    else if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_DATE_DATE;
    break;
  case SYS_STATE_SET_DATE_DATE:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_DATE_MONTH;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_CONFIRM_SET_DATE;
    else if (*button_state == SINGLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_DATE_DATE_PLUS_ONE;
    break;
  case SYS_STATE_SET_DATE_MONTH:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_DATE_YEAR;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_CONFIRM_SET_DATE;
    else if (*button_state == SINGLE_CLICK_BUTTON)
    {
      s_state_set_time = SYS_STATE_SET_DATE_MONTH_PLUS_ONE;
    }
    break;
  case SYS_STATE_SET_DATE_YEAR:
    if (*button_state == DOUBLE_CLICK_BUTTON)
      s_state_set_time = SYS_STATE_SET_DATE_DATE;
    else if (*button_state == HOLD_BUTTON)
      s_state_set_time = SYS_STATE_CONFIRM_SET_DATE;
    else if (*button_state == SINGLE_CLICK_BUTTON)
    {
      s_state_set_time = SYS_STATE_SET_TIME_YEAR_PLUS_ONE;
    }
    break;
  case SYS_STATE_SET_DATE_DATE_PLUS_ONE:
    s_state_set_time = SYS_STATE_SET_DATE_DATE;
    break;
  case SYS_STATE_SET_DATE_MONTH_PLUS_ONE:
    s_state_set_time = SYS_STATE_SET_DATE_MONTH;
    break;
  case SYS_STATE_SET_TIME_YEAR_PLUS_ONE:
    s_state_set_time = SYS_STATE_SET_DATE_YEAR;
    break;
  case SYS_STATE_CONFIRM_SET_DATE:
    s_state_set_time = SYS_STATE_SET_DATE;
    break;
  case SYS_STATE_FINSH_SET_DATE:
    s_state_set_time = SYS_STATE_SET_DATE;
    break;
  case SYS_STATE_EXIT:
    break;
  default:
    break;
  }
}

uint32_t sys_set_time_fsm_action()
{
  switch (s_state_set_time)
  {

  case SYS_STATE_SET_TIME:
    drv_led_matrix_clear();
    drv_led_matrix_set_rtc_interactive(D_LED_MATRIX_SET_TIME);
    break;
  case SYS_STATE_SET_TIME_HOUR:
    drv_led_matrix_set_time_interactive(D_LED_MATRIX_SET_TIME_HOUR);
    break;
  case SYS_STATE_SET_TIME_MIN:
    drv_led_matrix_set_time_interactive(D_LED_MATRIX_SET_TIME_MIN);
    break;
  case SYS_STATE_SET_TIME_SEC:
    drv_led_matrix_set_time_interactive(D_LED_MATRIX_SET_TIME_SEC);
    break;
  case SYS_STATE_SET_TIME_HOUR_PLUS_ONE:
    drv_led_matrix_set_time_interactive(D_LED_MATRIX_SET_TIME_HOUR_PLUS_ONE);
    break;
  case SYS_STATE_SET_TIME_MIN_PLUS_ONE:
    drv_led_matrix_set_time_interactive(D_LED_MATRIX_SET_TIME_MIN_PLUS_ONE);
    break;
  case SYS_STATE_SET_TIME_SEC_PLUS_ONE:
    drv_led_matrix_set_time_interactive(D_LED_MATRIX_SET_TIME_SEC_PLUS_ONE);
    break;
  case SYS_STATE_CONFIRM_SET_TIME:

    set_time.hour = *get_set_time_hour();
    set_time.min = *get_set_time_minutes();
    set_time.sec = *get_set_time_seconds();
    set_time.date = *get_set_time_date();
    set_time.month = *get_set_time_month();
    set_time.year = *get_set_time_year();

    drv_rtc_set_time(&set_time, D_RTC_24_FORMAT);
    break;
  case SYS_STATE_FINSH_SET_TIME:
    drv_led_matrix_clear();
    return SYS_STATE_FINSH_SET_TIME;
    break;

  case SYS_STATE_SET_DATE:
    drv_led_matrix_clear();
    drv_led_matrix_set_rtc_interactive(D_LED_MATRIX_SET_DATE);
    break;
  case SYS_STATE_SET_DATE_DATE:
    drv_led_matrix_set_date_interactive(D_LED_MATRIX_SET_TIME_DATE);
    break;
  case SYS_STATE_SET_DATE_MONTH:
    drv_led_matrix_set_date_interactive(D_LED_MATRIX_SET_TIME_MONTH);
    break;
  case SYS_STATE_SET_DATE_YEAR:
    drv_led_matrix_set_date_interactive(D_LED_MATRIX_SET_TIME_YEAR);
    break;
  case SYS_STATE_SET_DATE_DATE_PLUS_ONE:
    drv_led_matrix_set_date_interactive(D_LED_MATRIX_SET_TIME_DATE_PLUS_ONE);
    break;
  case SYS_STATE_SET_DATE_MONTH_PLUS_ONE:
    drv_led_matrix_set_date_interactive(D_LED_MATRIX_SET_TIME_MONTH_PLUS_ONE);
    break;
  case SYS_STATE_SET_TIME_YEAR_PLUS_ONE:
    drv_led_matrix_set_date_interactive(D_LED_MATRIX_SET_TIME_YEAR_PLUS_ONE);
    break;
  case SYS_STATE_CONFIRM_SET_DATE:

    set_time.hour = *get_set_time_hour();
    set_time.min = *get_set_time_minutes();
    set_time.sec = *get_set_time_seconds();
    set_time.date = *get_set_time_date();
    set_time.month = *get_set_time_month();
    set_time.year = *get_set_time_year();

    drv_rtc_set_time(&set_time, D_RTC_24_FORMAT);

    break;
  case SYS_STATE_FINSH_SET_DATE:
    drv_led_matrix_clear();
    return SYS_STATE_FINSH_SET_DATE;
    break;
  case SYS_STATE_EXIT:
    return 1;
  default:

    break;
  }
  return 0;
}

uint32_t sys_set_time_loop(btn_info_t *button_state)
{
  sys_set_time_init();
  while (1)
  {
    drv_btn_check_event(button_state);
    sys_set_time_fsm_update(button_state);
    check_set_finish = sys_set_time_fsm_action();
    if (check_set_finish == 1)
    {
      return 1;
    }
  }
}
