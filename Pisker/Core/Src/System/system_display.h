/**
 * @file       system_display.h
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
#ifndef SYSTEM_SYSTEM_DISPLAY_C_
#define SYSTEM_SYSTEM_DISPLAY_C_
/* Includes ----------------------------------------------------------- */
#include "system_set_alarm.h"
#include "system_set_time.h"
#include "system_digital_clock.h"
#include "fft_handle.h"
#include "bsp_adc.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */

typedef enum
{
  SYS_STATE_DISPLAY_DIGITAL_CLOCK_ICON,
  SYS_STATE_DISPLAY_SET_RTC_ICON,
  SYS_STATE_DISPLAY_SET_ALARM_ICON,
  SYS_STATE_DISPLAY_DIGITAL_CLOCK,
  SYS_STATE_DISPLAY_SET_RTC,
  SYS_STATE_DISPLAY_SET_ALARM

} sys_state_display_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the display system.
 *
 * This function sets up the display hardware and any necessary
 * configurations. It should be called once during system
 * initialization to prepare the display for operation.
 */
void sys_display_init(void);

/**
 * @brief Displays the digital clock icon on the screen.
 *
 * This function draws the icon representing the digital clock
 * on the display, indicating that the digital clock mode is active.
 */
void sys_display_digital_clock_icon(void);

/**
 * @brief Displays the RTC (Real-Time Clock) icon on the screen.
 *
 * This function draws the icon representing the RTC on the
 * display, indicating that the RTC mode is active.
 */
void sys_display_set_rtc_icon(void);

/**
 * @brief Displays the alarm icon on the screen.
 *
 * This function draws the icon representing the alarm on the
 * display, indicating that the alarm mode is active.
 */
void sys_display_set_alarm_icon(void);

/**
 * @brief Displays the current time in digital clock format.
 *
 * This function updates the display to show the current time
 * in a digital clock format.
 */
void sys_display_digital_clock(void);

/**
 * @brief Displays the RTC (Real-Time Clock) settings.
 *
 * This function updates the display to show the current RTC
 * settings, allowing the user to view or adjust the real-time clock.
 */
void sys_display_set_rtc(void);

/**
 * @brief Displays the alarm settings.
 *
 * This function updates the display to show the current alarm
 * settings, allowing the user to view or adjust the alarm.
 */
void sys_display_set_alarm(void);

/**
 * @brief Displays the music icon on the screen.
 *
 * This function draws the icon representing the music player
 * on the display, indicating that the music mode is active.
 */
void sys_display_music_icon(void);

/**
 * @brief Displays a Fast Fourier Transform (FFT) visualization.
 *
 * This function updates the display to show an FFT visualization,
 * which is typically used to represent audio signals in the
 * frequency domain.
 */
void sys_display_fft(void);
#endif
/* End of file -------------------------------------------------------- */
