/**
 * @file       system_digital_clock.h
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
#ifndef SYSTEM_SYSTEM_DIGITAL_CLOCK_H_
#define SYSTEM_SYSTEM_DIGITAL_CLOCK_H_
/* Includes ----------------------------------------------------------- */
#include <drv_btn.h>
#include <drv_matrix_led.h>
#include <drv_rtc.h>

#include <stdbool.h>
#include <sys_btn.h>
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */

typedef enum
{
  SYS_STATE_DIGITAL_CLOCK,
  SYS_STATE_DATE_TIME
} sys_state_digital_clock_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/**
 * @brief Initializes the digital clock system.
 *
 * This function sets up the digital clock, initializing any
 * necessary hardware or software components. It should be called
 * once during system initialization to prepare the clock for
 * operation.
 */
void sys_digital_clock_init(void);
/**
 * @brief Handles digital clock operations in the main loop.
 *
 * This function should be called regularly in the main loop to
 * manage the digital clock based on button events. It checks the
 * state of the buttons and performs the appropriate actions, such
 * as setting the time, starting/stopping the clock, or other clock
 * functions.
 *
 * @param button_state Pointer to a btn_info_t structure that holds
 *                     the current state of the buttons.
 */
void sys_digital_clock_loop(btn_info_t *button_state);
#endif
/* End of file -------------------------------------------------------- */
