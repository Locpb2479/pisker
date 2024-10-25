/**
 * @file       system_button.h
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 * @brief      System Driver For Button
 *             The driver for system button in STM32F411

 * @note       None
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_BUTTON_H
#define __SYS_BUTTON_H
/* Includes ----------------------------------------------------------- */
#include <drv_btn.h>
#include <stdbool.h>
/* Public defines ----------------------------------------------------- */
#define DEBOUNCE_MILIS 30
#define SINGLE_CLICK_MAX 500
#define DOUBLE_GAP_MILIS_MAX 500
#define LONG_MILIS_MIN 3000
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
    SYS_BTN_EVENT_RELEASE,
    SYS_BTN_EVENT_SINGLE_CLICK,
    SYS_BTN_EVENT_HOLD,
    SYS_BTN_EVENT_DOUBLE_CLICK
}
sys_btn_event_t ;
typedef enum
{
    SYS_BTN_STATE_RELEASE,
    SYS_BTN_STATE_PRESSED,
    SYS_BTN_STATE_MAYBE_2_CLICK,
    SYS_BTN_STATE_HOLDING,
    SYS_BTN_STATE_2_CLICK,
}
sys_btn_state_t ;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
bool sys_btn_state();
sys_btn_event_t sys_btn_get_event();
#endif
/* End of file -------------------------------------------------------- */
