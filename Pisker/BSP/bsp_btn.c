/**
 * @file       bsp_button.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-08-03
 * @author     Tin Lu Trung
 *
 * @brief      BSP for button
 */
/* Includes ----------------------------------------------------------- */
#include "bsp_btn.h"
/* Private defines ---------------------------------------------------- */
#define DEBOUNCE_MILIS 30
#define SINGLE_CLICK_MAX 500
#define DOUBLE_GAP_MILIS_MAX 300
#define LONG_MILIS_MIN 3000
/* Private enumerate/structure ---------------------------------------- */
typedef struct
{
  uint8_t btn_logic;
  uint8_t btn_pre_logic;
  uint32_t btn_timeup;
  uint32_t btn_timedown;
  uint32_t btn_pretimedown;
} bsp_btn_manage_t;
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static bsp_btn_manage_t bsp_btn_info;
/* Private function prototypes ---------------------------------------- */
void bsp_reset_info(void);
/* Function definitions ----------------------------------------------- */
bool bsp_button_init(button_t *button)
{
  button->gpio_pin = BTN_PIN;
  button->gpio_port = BTN_PORT;
  button->state = BTN_STATE_RELEASE;
  bsp_btn_info.btn_logic = 0;
  bsp_btn_info.btn_pre_logic = 0;
  bsp_btn_info.btn_timeup = 0;
  bsp_btn_info.btn_timedown = 0;
  return true;
}
btn_event_t bsp_btn_check_state_one_button(button_t *button)
{
  btn_event_t event = BTN_EVENT_RELEASE;
  uint32_t now = HAL_GetTick();
  // Check change
  if (bsp_btn_info.btn_logic != HAL_GPIO_ReadPin(button->gpio_port, button->gpio_pin))
  {
    bsp_btn_info.btn_pre_logic = bsp_btn_info.btn_logic;
    bsp_btn_info.btn_logic = !bsp_btn_info.btn_logic;
    switch (bsp_btn_info.btn_logic)
    {
    case GPIO_PIN_RESET:
    {
      bsp_btn_info.btn_timedown = now;
    }
    break;
    case GPIO_PIN_SET:
    {
      bsp_btn_info.btn_timeup = now;
    }
    break;
    default:
      break;
    }
  }
  switch (button->state)
  {
  case BTN_STATE_RELEASE:
  {
    if (bsp_btn_info.btn_logic == bsp_btn_info.btn_pre_logic)
    {
      button->state = BTN_STATE_RELEASE;
      event = BTN_EVENT_RELEASE;
    }
    else if ((bsp_btn_info.btn_pre_logic) && (bsp_btn_info.btn_timedown - bsp_btn_info.btn_timeup < DEBOUNCE_MILIS))
    {
      button->state = BTN_STATE_RELEASE;
      event = BTN_EVENT_RELEASE;
    }
    else if ((bsp_btn_info.btn_pre_logic) && (bsp_btn_info.btn_timedown - bsp_btn_info.btn_timeup > DEBOUNCE_MILIS) && (bsp_btn_info.btn_timedown - bsp_btn_info.btn_timeup < SINGLE_CLICK_MAX))
    {
      button->state = BTN_STATE_PRESSED;
      event = BTN_EVENT_RELEASE;
    }
    else if ((bsp_btn_info.btn_logic) && (now - bsp_btn_info.btn_timeup > LONG_MILIS_MIN))
    {
      button->state = BTN_STATE_HOLDING;
      event = BTN_EVENT_HOLD;
    }
    break;
  }
  case BTN_STATE_PRESSED:
  {
    if ((!bsp_btn_info.btn_logic) && (now - bsp_btn_info.btn_timedown > DOUBLE_GAP_MILIS_MAX))
    {
      button->state = BTN_STATE_RELEASE;
      event = BTN_EVENT_SINGLE_CLICK;
      bsp_reset_info();
    }
    else if ((!bsp_btn_info.btn_pre_logic) && (bsp_btn_info.btn_timeup - bsp_btn_info.btn_timedown <= DOUBLE_GAP_MILIS_MAX))
    {
      button->state = BTN_STATE_MAYBE_2_CLICK;
      event = BTN_EVENT_RELEASE;
      // save pre_timedown
      bsp_btn_info.btn_pretimedown = bsp_btn_info.btn_timedown;
    }
  }
  break;
  case BTN_STATE_MAYBE_2_CLICK: // Code here
  {
    if ((bsp_btn_info.btn_pre_logic) && (bsp_btn_info.btn_timedown - bsp_btn_info.btn_timeup <= DEBOUNCE_MILIS))
    {
      button->state = BTN_STATE_MAYBE_2_CLICK;
      event = BTN_EVENT_RELEASE;
      // reset half btn_info
      bsp_btn_info.btn_logic = 0;
      bsp_btn_info.btn_pre_logic = 0;
      bsp_btn_info.btn_timedown = 0;
      bsp_btn_info.btn_timeup = 0;
    }
    else if ((bsp_btn_info.btn_pre_logic) && (bsp_btn_info.btn_timedown - bsp_btn_info.btn_timeup > DEBOUNCE_MILIS) && (bsp_btn_info.btn_timedown - bsp_btn_info.btn_timeup < SINGLE_CLICK_MAX))
    {
      button->state = BTN_STATE_2_CLICK;
      event = BTN_EVENT_RELEASE;
    }
    else if ((bsp_btn_info.btn_logic) && (now - bsp_btn_info.btn_timeup > LONG_MILIS_MIN))
    {
      button->state = BTN_STATE_HOLDING;
      event = BTN_EVENT_HOLD;
    }
    if ((!bsp_btn_info.btn_logic) && (now - bsp_btn_info.btn_pretimedown >= DOUBLE_GAP_MILIS_MAX))
    {
      button->state = BTN_STATE_RELEASE;
      event = BTN_EVENT_SINGLE_CLICK;
      bsp_reset_info();
    }
    break;
  }
  case BTN_STATE_2_CLICK:
  {
    if ((!bsp_btn_info.btn_logic) && (now - bsp_btn_info.btn_timedown) > DOUBLE_GAP_MILIS_MAX)
    {
      button->state = BTN_STATE_RELEASE;
      event = BTN_EVENT_DOUBLE_CLICK;
      bsp_reset_info();
    }
    break;
  }
  case BTN_STATE_HOLDING:
  {
    if ((!bsp_btn_info.btn_logic))
    {
      button->state = BTN_STATE_RELEASE;
      event = BTN_EVENT_RELEASE;
      bsp_reset_info();
    }
    break;
  }
  default:
    break;
  }
  return event;
}
void bsp_reset_info(void)
{
  bsp_btn_info.btn_logic = 0;
  bsp_btn_info.btn_pre_logic = 0;
  bsp_btn_info.btn_timeup = 0;
  bsp_btn_info.btn_timedown = 0;
  bsp_btn_info.btn_pretimedown = 0;
}
