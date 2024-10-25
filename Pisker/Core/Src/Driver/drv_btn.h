/**
 * @file       button.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 * @brief      Header for button.h file
 *             The driver for reading User Button in STM32F411-DISCO

 * @note       None
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BUTTON_H
#define __BUTTON_H
/* Includes ----------------------------------------------------------- */
#include "bsp_btn.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  RELEASE_HIGH = 0,
  RELEASE_LOW
} btn_release_mode_t;

typedef enum
{
  SINGLE_CLICK_BUTTON = 1,
  DOUBLE_CLICK_BUTTON,
  HOLD_BUTTON,
  RELEASE_BUTTON
} btn_info_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the button driver.
 *
 * This function sets up the necessary hardware and configurations
 * for the button input. It should be called once during system
 * initialization.
 *
 * @return true if initialization is successful, false otherwise.
 */
bool drv_btn_init(void);

/**
 * @brief Checks for button events and updates the button state.
 *
 * This function should be called regularly in the main loop or in a
 * timer interrupt to monitor the button state. It updates the
 * provided btn_info_t structure with the current button state,
 * including whether the button is currently pressed and whether it
 * was pressed since the last check.
 *
 * @param button_state Pointer to a btn_info_t structure to be updated
 *                     with the current button state.
 */
void drv_btn_check_event(btn_info_t *button_state);
#endif
/* End of file -------------------------------------------------------- */
