/**
 * @file       bsp_button.h
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-08-03
 * @author     Tin Lu Trung
 *
 * @brief      BSP for button
 * Note:       This version using only one button
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef BSP_BTN_H_
#define BSP_BTN_H_
/* Includes ----------------------------------------------------------- */
#include "stm32f4xx_hal.h"

#include <stdbool.h>
#include <stdint.h>
/* Public defines ----------------------------------------------------- */
#define BTN_PIN		GPIO_PIN_0
#define BTN_PORT	GPIOA
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Enum for button events
 *
 */
typedef enum
{
    BTN_EVENT_RELEASE         = 0xA0u,
    BTN_EVENT_SINGLE_CLICK,
    BTN_EVENT_HOLD,
    BTN_EVENT_DOUBLE_CLICK
}
btn_event_t;

/**
 * @brief Enum for button state
 *
 */
typedef enum
{
    BTN_STATE_RELEASE     = 0x10u,
    BTN_STATE_PRESSED,
    BTN_STATE_MAYBE_2_CLICK,
    BTN_STATE_HOLDING,
    BTN_STATE_2_CLICK,
}
btn_state_t;

/**
 * @brief Struct for button variables
 *
 */
typedef struct
{
  btn_state_t 	 state;
  GPIO_TypeDef  *gpio_port;
  uint16_t       gpio_pin;
}
button_t;
/* Public function prototypes ----------------------------------------- */
/**
 * @brief           Initialize bsp button
 *
 * @return true     Init success
 * @return false    Init failure
 */
bool bsp_button_init(button_t *button);

/**
 * @brief                   Check state of button
 *
 * @param button            Button object
 * @return btn_event_t   Event of button current
 */
btn_event_t bsp_btn_check_state_one_button(button_t *button);

#endif /* BSP_BTN_H_ */
