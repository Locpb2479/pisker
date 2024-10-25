/*
 * drv_uart_mn_rec_data.c
 *
 *  Created on: Jul 22, 2024
 *      Author: Tri Nguyen
 */

/**
 * @file        drv_uart_mn_rec_data.c
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
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
#include "drv_uart_mn_rec_data.h"
#define TIME_STRING_LENGTH 20

typedef struct
{
    d_rtc_alarm_t alarm_time;
    uint8_t is_set; // Flag to check if the alarm is set
} alarm_t;

static alarm_t alarms[MAX_ALARMS]; // Array to store multiple alarms
static uint8_t alarm_count = 1;    // Current number of alarms set

static d_rtc_t _alarm_time;
static uint8_t _alarm_set = 0; // Flag to indicate if the alarm is set

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */

#ifdef VER1_
static ds1307_time_t parsed_time;

static uint8_t parse_and_set_time(uint8_t *data, uint16_t size);

void uart_process_received_data_config_time(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    // Ensure the received data is in the correct format: YYYY-MM-DD-HH-MM-SS
    if ((size < 18) || (data[4] != '-') || (data[7] != '-') || (data[10] != '-') || (data[13] != '-') || (data[16] != '-'))
    {
        const char *error_msg = "Wrong format\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return; // Incorrect format
    }

    ds1307_time_t time;
    time.ds1307_year = (data[0] - '0') * 1000 + (data[1] - '0') * 100 + (data[2] - '0') * 10 + (data[3] - '0');
    time.ds1307_month = (data[5] - '0') * 10 + (data[6] - '0');
    time.ds1307_date = (data[8] - '0') * 10 + (data[9] - '0');
    time.ds1307_hour = (data[11] - '0') * 10 + (data[12] - '0');
    time.ds1307_minute = (data[14] - '0') * 10 + (data[15] - '0');
    time.ds1307_second = (data[17] - '0') * 10 + (data[18] - '0');
    time.ds1307_day = 1; // Default to Monday or adjust if needed

    // Set the time on the DS1307 RTC
    ds1307_set_time(&time);

    // Send success message
    const char *success_msg = "Config success\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)success_msg, strlen(success_msg), HAL_MAX_DELAY);
}
#endif

#ifdef VER2_
void uart_process_received_data_config_time(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    // Ensure the received data is in the correct format: mode-YYYY-MM-DD-HH-MM-SS
    if (size != 25 || data[5] != '-' || data[10] != '-' || data[13] != '-' || data[16] != '-' || data[19] != '-' || data[22] != '-')
    {
        const char *error_msg = "Wrong format\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return; // Incorrect format
    }

    // Determine the mode
    if (strncmp((char *)data, "stime", 5) == 0)
    {
        ds1307_time_t time;
        time.ds1307_year = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
        time.ds1307_month = (data[11] - '0') * 10 + (data[12] - '0');
        time.ds1307_date = (data[14] - '0') * 10 + (data[15] - '0');
        time.ds1307_hour = (data[17] - '0') * 10 + (data[18] - '0');
        time.ds1307_minute = (data[20] - '0') * 10 + (data[21] - '0');
        time.ds1307_second = (data[23] - '0') * 10 + (data[24] - '0');
        time.ds1307_day = 1; // Default to Monday or adjust if needed

        // Set the time on the DS1307 RTC
        ds1307_set_time(&time);

        // Send success message
        const char *success_msg = "Config time success\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)success_msg, strlen(success_msg), HAL_MAX_DELAY);
    }
    else if (strncmp((char *)data, "alarm", 5) == 0)
    {
        ds1307_time_t alarm_time;
        alarm_time.ds1307_year = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
        alarm_time.ds1307_month = (data[11] - '0') * 10 + (data[12] - '0');
        alarm_time.ds1307_date = (data[14] - '0') * 10 + (data[15] - '0');
        alarm_time.ds1307_hour = (data[17] - '0') * 10 + (data[18] - '0');
        alarm_time.ds1307_minute = (data[20] - '0') * 10 + (data[21] - '0');
        alarm_time.ds1307_second = (data[23] - '0') * 10 + (data[24] - '0');
        alarm_time.ds1307_day = 1; // Default to Monday or adjust if needed

        // Set the alarm time on the DS1307 RTC
        ds1307_set_alarm(&alarm_time);

        _alarm_time = alarm_time;
        _alarm_set = 1; // Set the alarm flag

        // Send success message
        const char *success_msg = "Config alarm success\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)success_msg, strlen(success_msg), HAL_MAX_DELAY);
    }
    else
    {
        const char *error_msg = "Unknown mode\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
    }
}
#endif

void uart_process_received_data_config_time(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    if (size != 25 || data[5] != '-' || data[10] != '-' || data[13] != '-' || data[16] != '-' || data[19] != '-' || data[22] != '-')
    {
        const char *error_msg = "Wrong format\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return; // Incorrect format
    }

    d_rtc_t time;
    // time.year = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
    time.year = (data[8] - '0') * 10 + (data[9] - '0');
    time.date = (data[11] - '0') * 10 + (data[12] - '0');
    time.day = 1;
    time.hour = (data[17] - '0') * 10 + (data[18] - '0');
    time.min = (data[20] - '0') * 10 + (data[21] - '0');
    time.sec = (data[23] - '0') * 10 + (data[24] - '0');
    time.month = (data[14] - '0') * 10 + (data[15] - '0');

    //    time.year = 24;
    //    time.month = 8;
    //    time.day = 2;
    //    time.hour = 10;
    //    time.min = 10;
    //    time.sec = 10;
    //    time.date = 7; // Default to Monday or adjust if needed
    // drv_rtc_get_rtc_ds1307();
    // Set the time on the DS1307 RTC
    drv_rtc_set_time(&time, D_RTC_24_FORMAT);

    // Send success message
    const char *success_msg = "Config time success\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)success_msg, strlen(success_msg), HAL_MAX_DELAY);
}

#ifdef VER_1_ALARM
void uart_process_received_data_config_alarm(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    if (size != 25 || data[5] != '-' || data[10] != '-' || data[13] != '-' || data[16] != '-' || data[19] != '-' || data[22] != '-')
    {
        const char *error_msg = "Wrong format\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return;
    }
    d_rtc_t alarm_time;

    // alarm_time.year = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
    alarm_time.year = (data[8] - '0') * 10 + (data[9] - '0');
    alarm_time.date = (data[11] - '0') * 10 + (data[12] - '0');
    alarm_time.day = 1;
    alarm_time.hour = (data[17] - '0') * 10 + (data[18] - '0');
    alarm_time.min = (data[20] - '0') * 10 + (data[21] - '0');
    alarm_time.sec = (data[23] - '0') * 10 + (data[24] - '0');
    alarm_time.month = (data[14] - '0') * 10 + (data[15] - '0');

    // Set the alarm time on the DS1307 RTC
    drv_rtc_set_alarm(&alarm_time);

    _alarm_time = alarm_time;
    _alarm_set = 1; // Set the alarm flag

    // Send success message
    const char *success_msg = "Config alarm success\r\n";
    HAL_UART_Transmit(huart, (uint8_t *)success_msg, strlen(success_msg), HAL_MAX_DELAY);
}
#endif

void uart_process_received_data_config_alarm(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    if (size != 25 || data[5] != '-' || data[10] != '-' || data[13] != '-' || data[16] != '-' || data[19] != '-' || data[22] != '-')
    {
        const char *error_msg = "Wrong format\r\n";
        // memset(error_msg, 0, sizeof(error_msg));
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return;
    }

    if (alarm_count >= MAX_ALARMS)
    {
        const char *error_msg = "Alarm list full\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return;
    }

    uint8_t alarm_index = alarm_count; // Use the current count as the index
    d_rtc_alarm_t new_alarm;
    new_alarm.hour = (data[17] - '0') * 10 + (data[18] - '0');
    new_alarm.min = (data[20] - '0') * 10 + (data[21] - '0');
    new_alarm.sec = (data[23] - '0') * 10 + (data[24] - '0');

    // Set the alarm on the RTC
    uint32_t result = drv_rtc_set_alarm(alarm_index, &new_alarm);

    if (result != D_RTC_OK)
    {
        const char *error_msg = "Failed to set alarm\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
        return;
    }

    // Save the alarm in the list
    alarms[alarm_index].alarm_time = new_alarm;
    alarms[alarm_index].is_set = 1;
    alarm_count++;

    // Send a success message indicating which alarm was configured
    char success_msg[50];
    int len = snprintf(success_msg, sizeof(success_msg),
                       "Config alarm %d success\r\n", alarm_index + 1); // +1 to make it 1-based index

    if (len < 0 || len >= sizeof(success_msg))
    {
        // Handle error: message was truncated or formatting failed
        const char *error_msg = "Message format error\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)error_msg, strlen(error_msg), HAL_MAX_DELAY);
    }
    else
    {
        // Send the success message
        HAL_UART_Transmit(huart, (uint8_t *)success_msg, len, HAL_MAX_DELAY);
    }
}

void uart_process_transmit_data_get_time(UART_HandleTypeDef *huart, uint8_t *data, uint16_t size)
{
    d_rtc_t *rtc = drv_rtc_get_rtc_ds1307();
    drv_rtc_get_time();
    char buffer[27];
    int len = snprintf(buffer, sizeof(buffer),
                       "Time: %04d-%02d-%02d %02d:%02d:%02d\r\n",
                       rtc->year,
                       rtc->month,
                       rtc->date,
                       rtc->hour,
                       rtc->min,
                       rtc->sec);
    HAL_UART_Transmit(huart, (uint8_t *)buffer, len, HAL_MAX_DELAY);
}

#ifdef VER_1_ALARM
void ds1307_notify_alarm(UART_HandleTypeDef *huart)
{
    if (!_alarm_set)
        return; // If no alarm is set, return

    //    ds1307_time_t current_time;
    //    ds1307_get_time(&current_time);
    d_rtc_t *current_time = drv_rtc_get_rtc_ds1307();

    if (current_time->year == _alarm_time.year &&
        current_time->month == _alarm_time.month &&
        current_time->date == _alarm_time.date &&
        current_time->hour == _alarm_time.hour &&
        current_time->min == _alarm_time.min &&
        current_time->sec == _alarm_time.sec)
    {
        const char *alarm_msg = "Toi gio com roi, di an thoai\r\n";
        HAL_UART_Transmit(huart, (uint8_t *)alarm_msg, strlen(alarm_msg), HAL_MAX_DELAY);
        _alarm_set = 0; // Clear the alarm after it rings
    }
}
#endif

uint8_t ds1307_notify_alarm()
{
    d_rtc_t *current_time = drv_rtc_get_rtc_ds1307();

    for (uint8_t i = 1; i < alarm_count; i++)
    {
        if (alarms[i].is_set &&
            current_time->hour == alarms[i].alarm_time.hour &&
            current_time->min == alarms[i].alarm_time.min &&
            current_time->sec == alarms[i].alarm_time.sec)
        {

            char alarm_msg[50]; // Adjust the size as needed
            sprintf(alarm_msg, "Alarm %d triggered!\r\n", i + 1);
            // HAL_UART_Transmit(huart, (uint8_t *)alarm_msg, strlen(alarm_msg), HAL_MAX_DELAY);
            bsp_uart_pc_control_send((uint8_t *)alarm_msg, strlen(alarm_msg));
            alarms[i].is_set = 0; // Clear the alarm after it rings
            return i;
        }
    }
    return 0;
}
/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
