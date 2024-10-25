/**
 * @file        drv_rtc.c
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
#include "drv_rtc.h"

/* Private defines ---------------------------------------------------- */
#define RTC_ADDRESS (0x68 << 1)
#define RTC_REG_TIME 0x00
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
static d_rtc_t rtc_ds1307;
// d_rtc_alarm_t rtc_alarm;
static d_rtc_alarm_t rtc_alarms[MAX_ALARMS];
/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */

uint8_t drv_rtc_bcd_to_dec(uint8_t d_rtc_bcd)
{
    return (d_rtc_bcd >> 4) * 10 + (d_rtc_bcd & 0x0f);
}

uint8_t drv_rtc_dec_to_bcd(uint8_t d_rtc_decimal)
{
    return (d_rtc_decimal / 10) << 4 | (d_rtc_decimal % 10);
}

uint32_t drv_rtc_get_time(void)
{
    rtc_ds1307.i2c_buf[0] = 0x00;

    bsp_i2c_status_t write_status = bsp_i2c_write_buffer(RTC_ADDRESS, 1);
    if (write_status != BSP_I2C_OK)
    {
        if (write_status == BSP_I2C_ERROR_ACK_FAILURE)
        {
            return D_RTC_ERROR_I2C_TIMEOUT;
        }
        else
        {
            return D_RTC_ERROR_I2C_WRITE;
        }
    }

    bsp_i2c_status_t read_status = bsp_i2c_read_buffer(RTC_ADDRESS, 7);
    if (read_status != BSP_I2C_OK)
    {
        if (read_status == BSP_I2C_ERROR_ACK_FAILURE)
        {
            return D_RTC_ERROR_I2C_TIMEOUT;
        }
        else
        {
            return D_RTC_ERROR_I2C_READ;
        }
    }

    rtc_ds1307.day = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[3]);

    rtc_ds1307.date = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[4]);
    rtc_ds1307.month = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[5]);
    rtc_ds1307.year = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[6]);

    rtc_ds1307.sec = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[0]);
    rtc_ds1307.min = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[1]);
    rtc_ds1307.hour = drv_rtc_bcd_to_dec(rtc_ds1307.i2c_buf[2]);

    return D_RTC_OK;
}

uint32_t drv_rtc_set_time(d_rtc_t *set_time, d_rtc_time_format_t time_format)
{

    if (set_time->hour > 23 || set_time->min > 59 || set_time->sec > 59 || set_time->date > 31 || set_time->month > 12)
    {
        return D_RTC_ERROR_INVALID_PARAM;
    }

    rtc_ds1307.i2c_buf[0] = 0x00;
    rtc_ds1307.i2c_buf[1] = drv_rtc_dec_to_bcd(set_time->sec);
    rtc_ds1307.i2c_buf[2] = drv_rtc_dec_to_bcd(set_time->min);

    if (time_format == D_RTC_12_FORMAT)
    {
        set_time->hour %= 12;
        if (set_time->hour == 0)
        {
            set_time->hour = 12; // ~12 AM
        }
        rtc_ds1307.i2c_buf[3] = drv_rtc_dec_to_bcd(set_time->hour);
        rtc_ds1307.i2c_buf[3] |= 0x40; // set bit 6 = 1 to convert to 12 format
        if (set_time->hour >= 12)
        {
            rtc_ds1307.i2c_buf[3] |= 0x20; // set bit 5 = 1 to show PM
        }
    }
    else if (time_format == D_RTC_24_FORMAT)
    {
        rtc_ds1307.i2c_buf[3] = drv_rtc_dec_to_bcd(set_time->hour);
    }
    else
    {
        rtc_ds1307.i2c_buf[3] = drv_rtc_dec_to_bcd(set_time->hour);
    }

    rtc_ds1307.i2c_buf[5] = drv_rtc_dec_to_bcd(set_time->date);
    rtc_ds1307.i2c_buf[6] = drv_rtc_dec_to_bcd(set_time->month);
    rtc_ds1307.i2c_buf[7] = drv_rtc_dec_to_bcd(set_time->year);

    bsp_i2c_status_t write_status = bsp_i2c_write_buffer(RTC_ADDRESS, 8);
    if (write_status != BSP_I2C_OK)
    {
        if (write_status == BSP_I2C_ERROR_ACK_FAILURE)
        {
            return D_RTC_ERROR_I2C_TIMEOUT;
        }
        else
        {
            return D_RTC_ERROR_I2C_WRITE;
        }
    }

    return D_RTC_OK;
}

d_rtc_t *drv_rtc_get_rtc_ds1307(void)
{
    return &rtc_ds1307;
}
#ifdef one_alarm
uint32_t drv_rtc_set_alarm(d_rtc_alarm_t *set_alarm)
{
    if (set_alarm->hour >= 24 || set_alarm->min >= 60 || set_alarm->sec >= 60)
    {
        return D_RTC_ERROR_INVALID_PARAM;
    }

    rtc_alarm.hour = set_alarm->hour;
    rtc_alarm.min = set_alarm->min;
    rtc_alarm.sec = set_alarm->sec;
    rtc_alarm.enabled = D_RTC_ALARM_ENABLED;

    return D_RTC_OK;
}
#endif

uint32_t drv_rtc_set_alarm(uint8_t alarm_index, d_rtc_alarm_t *set_alarm)
{
    if (alarm_index >= MAX_ALARMS || set_alarm->hour >= 24 || set_alarm->min >= 60 || set_alarm->sec >= 60)
    {
        return D_RTC_ERROR_INVALID_PARAM;
    }

    rtc_alarms[alarm_index].hour = set_alarm->hour;
    rtc_alarms[alarm_index].min = set_alarm->min;
    rtc_alarms[alarm_index].sec = set_alarm->sec;
    rtc_alarms[alarm_index].enabled = D_RTC_ALARM_ENABLED;

    return D_RTC_OK;
}
#ifdef VER_1_ALARM
uint32_t drv_rtc_check_alarm(void)
{
    if (rtc_alarm.enabled == D_RTC_ALARM_ENABLED)
    {
        uint32_t get_time_status = drv_rtc_get_time();
        if (get_time_status != D_RTC_OK)
        {
            return get_time_status;
        }

        if (rtc_ds1307.hour == rtc_alarm.hour &&
            rtc_ds1307.min == rtc_alarm.min &&
            rtc_ds1307.sec == rtc_alarm.sec)
        {
            rtc_alarm.enabled = D_RTC_ALARM_DISABLED; // Disable alarm after it triggers
            return D_RTC_ALARM_TRIGGERED;
        }
    }

    return D_RTC_OK;
}
#endif

uint32_t drv_rtc_check_alarms(void)
{
    for (uint8_t i = 0; i < MAX_ALARMS; i++)
    {
        if (rtc_alarms[i].enabled == D_RTC_ALARM_ENABLED)
        {
            uint32_t get_time_status = drv_rtc_get_time();
            if (get_time_status != D_RTC_OK)
            {
                return get_time_status;
            }

            if (rtc_ds1307.hour == rtc_alarms[i].hour &&
                rtc_ds1307.min == rtc_alarms[i].min &&
                rtc_ds1307.sec == rtc_alarms[i].sec)
            {
                rtc_alarms[i].enabled = D_RTC_ALARM_DISABLED; // Disable alarm after it triggers
                return D_RTC_ALARM_TRIGGERED;
            }
        }
    }

    return D_RTC_OK;
}

uint32_t drv_rtc_set_time_epoch(uint32_t epoch, d_rtc_time_format_t time_format)
{
    time_t rawtime = epoch; // GMT 0, epoch + 25200 (GMT+7); 
    struct tm *ts;

    ts = localtime(&rawtime);

    rtc_ds1307.i2c_buf[0] = 0;
    rtc_ds1307.i2c_buf[1] = drv_rtc_dec_to_bcd(ts->tm_sec);
    rtc_ds1307.i2c_buf[2] = drv_rtc_dec_to_bcd(ts->tm_min);

    if (time_format == D_RTC_12_FORMAT)
    {
        uint8_t hour = ts->tm_hour % 12;
        if (hour == 0)
        {
            hour = 12; // ~12 AM
        }
        rtc_ds1307.i2c_buf[3] = drv_rtc_dec_to_bcd(hour);
        rtc_ds1307.i2c_buf[3] |= 0x40; // set bit 6 = 1 to convert to 12 format
        if (ts->tm_hour >= 12)
        {
            rtc_ds1307.i2c_buf[3] |= 0x20; // // set bit 5 = 1 to show PM
        }
    }
    else if (time_format == D_RTC_24_FORMAT)
    {
        rtc_ds1307.i2c_buf[3] = drv_rtc_dec_to_bcd(ts->tm_hour);
    }
    else
    {
        rtc_ds1307.i2c_buf[3] = drv_rtc_dec_to_bcd(ts->tm_hour);
    }

    // rtc_ds1307.d_rtc_i2c_buf[4] = ts->tm_wday + 1;
    rtc_ds1307.i2c_buf[5] = drv_rtc_dec_to_bcd(ts->tm_mday);
    rtc_ds1307.i2c_buf[6] = drv_rtc_dec_to_bcd(ts->tm_mon + 1);    // Month (tm_mon start at 0)
    rtc_ds1307.i2c_buf[7] = drv_rtc_dec_to_bcd(ts->tm_year % 100); // Year (tm_year only suport 0-99)

    bsp_i2c_status_t write_status = bsp_i2c_write_buffer(RTC_ADDRESS, 8);
    if (write_status != BSP_I2C_OK)
    {
        if (write_status == BSP_I2C_ERROR_ACK_FAILURE)
        {
            return D_RTC_ERROR_I2C_TIMEOUT;
        }
        else
        {
            return D_RTC_ERROR_I2C_WRITE;
        }
    }

    return D_RTC_OK;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
