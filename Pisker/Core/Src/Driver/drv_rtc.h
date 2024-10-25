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
#ifndef __DRV_RTC_
#define __DRV_RTC_

/* Includes ------------------------------------------------------------------ */
#include "main.h"
#include "bsp_i2c.h"
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

/* Public defines ------------------------------------------------------------ */
#define D_RTC_I2C_BUF_SIZE 8
#define MAX_ALARMS 3
/* Public enumerations/structures -------------------------------------------- */

/**
 * @brief RTC structure to hold time and date information
 */
typedef struct
{
    uint8_t sec; // đã có tag ở dưới thì ko cần quá chi tiết như ni
    uint8_t min; // nên như này uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
    uint8_t i2c_buf[D_RTC_I2C_BUF_SIZE];
} d_rtc_t;

typedef enum
{
    D_RTC_12_FORMAT = 0,
    D_RTC_24_FORMAT = 1
} d_rtc_time_format_t;

typedef enum
{
    D_RTC_OK = 0,
    D_RTC_ERROR_I2C_WRITE = 1,
    D_RTC_ERROR_I2C_READ = 2,
    D_RTC_ERROR_I2C_TIMEOUT = 3,
    D_RTC_ERROR_INVALID_PARAM = 4
} d_rtc_status_t;

typedef enum
{
    D_RTC_ALARM_DISABLED = 5,
    D_RTC_ALARM_ENABLED = 6,
    D_RTC_ALARM_TRIGGERED
} d_rtc_alarm_state_t;

/**
 * @brief RTC alarm structure
 */
typedef struct
{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t enabled;
} d_rtc_alarm_t;

typedef struct
{
    d_rtc_alarm_t alarms[MAX_ALARMS];
} d_rtc_alarms_t;
/* Public macros ------------------------------------------------------------- */

/* Public variables ---------------------------------------------------------- */

/* Public function prototypes ------------------------------------------------ */

/**
 * @brief       Convert BCD to decimal
 *
 * @param[in]   d_rtc_bcd    BCD value to convert
 * @return      Decimal equivalent of the BCD value
 */
uint8_t drv_rtc_bcd_to_dec(uint8_t d_rtc_bcd);

/**
 * @brief       Convert decimal to BCD
 *
 * @param[in]   d_rtc_decimal    Decimal value to convert
 * @return      BCD equivalent of the decimal value
 */
uint8_t drv_rtc_dec_to_bcd(uint8_t d_rtc_decimal);

/**
 * @brief       Get the current time from the RTC
 */
uint32_t drv_rtc_get_time(void);

/**
 * @brief       Set the current time on the RTC
 *
 * @param[in]   set_hour     Hour to set
 * @param[in]   set_min      Minute to set
 * @param[in]   set_sec      Second to set
 * @param[in]   set_date     Date to set
 * @param[in]   set_month    Month to set
 * @param[in]   set_year     Year to set
 */
uint32_t drv_rtc_set_time(d_rtc_t *set_time, d_rtc_time_format_t time_format);

/**
 * @brief       Getter for rtc_ds1307
 * @return      Pointer to rtc_ds1307
 */
d_rtc_t *drv_rtc_get_rtc_ds1307(void);

/**
 * @brief Set the alarm time
 *
 * @param[in] set_alarm_hour Hour to set for the alarm
 * @param[in] set_alarm_min Minute to set for the alarm
 * @param[in] set_alarm_sec Second to set for the alarm
 */
// uint32_t drv_rtc_set_alarm(d_rtc_alarm_t *set_alarm); // ver 1 alarm
uint32_t drv_rtc_set_alarm(uint8_t alarm_index, d_rtc_alarm_t *set_alarm);
/**
 * @brief Check if the alarm has triggered
 *
 * @return 1 if the alarm has triggered, 0 otherwise
 */
uint32_t drv_rtc_check_alarm(void);

uint32_t drv_rtc_set_time_epoch(uint32_t epoch, d_rtc_time_format_t time_format);

#endif // __DRV_RTC_

/* End of file ---------------------------------------------------------------- */
