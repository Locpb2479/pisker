/**
 * @file       button.c
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
#include "drv_btn.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
static button_t button;
static btn_event_t button_event;
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
bool drv_btn_init(void)
{
  bsp_button_init(&button);
  return true;
}

void drv_btn_check_event(btn_info_t *button_state)
{
  button_event = bsp_btn_check_state_one_button(&button);
  if (button_event == BTN_EVENT_SINGLE_CLICK)
  {
    *button_state = SINGLE_CLICK_BUTTON;
  }
  else if (button_event == BTN_EVENT_DOUBLE_CLICK)
  {
    *button_state = DOUBLE_CLICK_BUTTON;
  }
  else if (button_event == BTN_EVENT_HOLD)
  {
    *button_state = HOLD_BUTTON;
  }
  if (button_event == BTN_EVENT_RELEASE)
  {
    *button_state = RELEASE_BUTTON;
  }
}
