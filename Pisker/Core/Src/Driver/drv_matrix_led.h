/**
 * @file        drv_rtc.h
 * @brief       Header file for RTC driver
 * @version     0.0.0
 * @date        [Insert Date]
 * @author      Lu Trung Tin
 *              Nguyen Nhat Tri
 *              Pham Bao Loc
 *
 * This file contains definitions and function prototypes for interfacing with the RTC (Real-Time Clock).
 */

/* Define to prevent recursive inclusion ------------------------------------- */
#ifndef __DRV_MATRIX_LED_
#define __DRV_MATRIX_LED_

/* Includes ------------------------------------------------------------------ */
#include <stdint.h>
#include <math.h>
#include "frame.h"
#include "stm32f4xx_hal.h"
#include "drv_rtc.h"
/* Public defines ------------------------------------------------------------ */
#define MAX_LED 512
#define USE_BRIGHTNESS 1

/* Public enumerations/structures -------------------------------------------- */

/**
 * @brief Enumeration for LED matrix status
 */
typedef enum
{
    D_LED_MATRIX_OK = 0,
    D_LED_MATRIX_ERROR = 1,
    D_LED_MATRIX_SENT_OK = 2,
    D_LED_MATRIX_SENT_ERROR = 3
} d_led_matrix_status_t;

typedef enum
{
    D_LED_MATRIX_ALARM_HOUR = 4,
    D_LED_MATRIX_ALARM_MIN = 5,
    D_LED_MATRIX_ALARM_SEC = 6,
    D_LED_MATRIX_ALARM_HOUR_PLUS_ONE = 7,
    D_LED_MATRIX_ALARM_MIN_PLUS_ONE = 8,
    D_LED_MATRIX_ALARM_SEC_PLUS_ONE = 9,
    D_LED_MATRIX_ALARM_NEXT = 10
} d_led_matrix_alarm_status_t;

typedef enum
{
    D_LED_MATRIX_SET_TIME_HOUR = 11,
    D_LED_MATRIX_SET_TIME_MIN = 12,
    D_LED_MATRIX_SET_TIME_SEC = 13,
    D_LED_MATRIX_SET_TIME_HOUR_PLUS_ONE = 14,
    D_LED_MATRIX_SET_TIME_MIN_PLUS_ONE = 15,
    D_LED_MATRIX_SET_TIME_SEC_PLUS_ONE = 16,

    D_LED_MATRIX_SET_TIME = 23

} d_led_matrix_set_time_status_t;

typedef enum
{
    D_LED_MATRIX_SET_TIME_DATE = 17,
    D_LED_MATRIX_SET_TIME_MONTH = 18,
    D_LED_MATRIX_SET_TIME_YEAR = 19,
    D_LED_MATRIX_SET_TIME_DATE_PLUS_ONE = 20,
    D_LED_MATRIX_SET_TIME_MONTH_PLUS_ONE = 21,
    D_LED_MATRIX_SET_TIME_YEAR_PLUS_ONE = 22,

    D_LED_MATRIX_SET_DATE = 24
} d_led_matrix_set_date_status_t;

typedef struct
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} d_led_matrix_alarm_t;

/* Public macros ------------------------------------------------------------- */

/* Public variables ---------------------------------------------------------- */

/* Public function prototypes ------------------------------------------------ */
void bsp_tim_init(TIM_HandleTypeDef *htim); // temp
/**
 * @brief       Set a specific LED in the matrix
 *
 * @param[in]   row          Row of the LED
 * @param[in]   col          Column of the LED
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the set operation
 */
uint32_t drv_led_matrix_set_led(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Set the brightness of the LED matrix
 *
 * @param[in]   brightness   Brightness level to set
 * @return      Status of the brightness set operation
 */
uint32_t drv_led_matrix_set_brightness(uint8_t brightness); // 0 to 45

/**
 * @brief       Send data to WS2812 LEDs
 *
 * @return      Status of the send operation
 */
uint32_t drv_led_matrix_ws2812_send();

/**
 * @brief       Draw a colon on the LED matrix
 *
 * @param[in]   row_offset   Row offset for the colon
 * @param[in]   col_offset   Column offset for the colon
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the draw operation
 */
uint32_t drv_led_matrix_draw_colon(uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Draw a digit on the LED matrix
 *
 * @param[in]   num          Digit to draw
 * @param[in]   row_offset   Row offset for the digit
 * @param[in]   col_offset   Column offset for the digit
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the draw operation
 */
uint32_t drv_led_matrix_draw_digit(uint8_t num, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Draw a number on the LED matrix
 *
 * @param[in]   number       Number to draw
 * @param[in]   row_offset   Row offset for the number
 * @param[in]   col_offset   Column offset for the number
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the draw operation
 */
uint32_t drv_led_matrix_draw_number(uint8_t number, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Draw seconds as a number on the LED matrix
 *
 * @param[in]   number       Seconds to draw
 * @param[in]   row_offset   Row offset for the seconds
 * @param[in]   col_offset   Column offset for the seconds
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the draw operation
 */
uint32_t drv_led_matrix_draw_number_sec(uint8_t number, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Draw time (hours, minutes, seconds) on the LED matrix
 *
 * @param[in]   hours        Hours to draw
 * @param[in]   minutes      Minutes to draw
 * @param[in]   seconds      Seconds to draw
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the draw operation
 */
uint32_t drv_led_matrix_draw_time(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Update the first row of the LED matrix
 *
 * @param[in]   seconds      Seconds to update
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the update operation
 */
uint32_t drv_led_matrix_update_first_row(uint8_t seconds, uint8_t red, uint8_t green, uint8_t blue);

/**
 * @brief       Update the last row of the LED matrix
 *
 * @param[in]   seconds      Seconds to update
 * @param[in]   red          Red color component
 * @param[in]   green        Green color component
 * @param[in]   blue         Blue color component
 * @return      Status of the update operation
 */
uint32_t drv_led_matrix_clear();

uint32_t drv_led_matrix_update_last_row(uint8_t seconds, uint8_t red, uint8_t green, uint8_t blue);

uint32_t drv_led_matrix_set_alarm_interactive(d_led_matrix_alarm_status_t set_time);

uint32_t drv_led_matrix_set_time_interactive(d_led_matrix_set_time_status_t set_time);

uint32_t drv_led_matrix_display_alarm_setting(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t set_alarm, uint8_t blink_state);

uint32_t drv_led_matrix_display_set_time_setting(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t set_time, uint8_t blink_state);

uint8_t *get_set_time_hour();

uint8_t *get_set_time_minutes();

uint8_t *get_set_time_seconds();

uint8_t *get_set_time_date();

uint8_t *get_set_time_month();

uint8_t *get_set_time_year();

uint32_t drv_led_matrix_draw_clock_icon(void);

uint32_t drv_led_matrix_draw_alarm_clock_icon(void);

uint32_t drv_led_matrix_draw_icon(arr icon_struct);

void drv_led_matrix_draw_string(const char *str, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue);

uint32_t drv_led_matrix_draw_letter(char letter, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue);

void drv_led_matrix_update_rgb_effect(uint32_t time);

void drv_matrix_led_trigger_alarm(uint8_t alarm_index);

uint8_t drv_matrix_led_check_alarms(uint8_t current_hour, uint8_t current_minute, uint8_t current_second);

uint32_t drv_led_matrix_set_date_interactive(d_led_matrix_set_date_status_t set_date);

uint32_t drv_led_matrix_display_set_date_setting(uint8_t date, uint8_t month, uint8_t year, uint8_t set_date, uint8_t blink_state);

uint32_t drv_led_matrix_display_rtc_setting(uint8_t set_rtc, uint8_t blink_state);

uint32_t drv_led_matrix_set_rtc_interactive(d_led_matrix_set_time_status_t set_rtc);

void drv_matrix_led_digital_clock(void);

void drv_matrix_led_date_time(void);

#endif // __DRV_MATRIX_LED_

/* End of file ---------------------------------------------------------------- */
