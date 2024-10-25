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
#include "drv_matrix_led.h"

/* Private defines ---------------------------------------------------- */
#define PI 3.14159265
#define ALARM_SET_HOUR 0
#define ALARM_SET_MINUTE 1
#define ALARM_SET_SECOND 2
#define MATRIX_WIDTH 16
#define MATRIX_HEIGHT 16
#define MAX_ALARMS 3

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */

TIM_HandleTypeDef *htim;
TIM_HandleTypeDef *btim_data;

int data_sent_flag = 0;
uint8_t led_data[MAX_LED][4];
uint8_t led_mod[MAX_LED][4]; // for brightness
uint16_t pwm_data[(24 * MAX_LED) + 50];

// static uint8_t alarm_hours = 0;
// static uint8_t alarm_minutes = 0;
// static uint8_t alarm_seconds = 0;

static uint8_t set_time_hours = 0;
static uint8_t set_time_minutes = 0;
static uint8_t set_time_seconds = 0;
static uint8_t set_time_date = 1;
static uint8_t set_time_month = 1;
static uint8_t set_time_year = 20;

uint8_t blink_state = 0;
uint8_t current_setting = ALARM_SET_HOUR;

static uint32_t current_time;
static uint32_t last_blink_time;
const uint32_t BLINK_INTERVAL = 500; // 500ms blink interval

static d_led_matrix_alarm_t alarms[MAX_ALARMS];
// static uint8_t alarm_count = 0;
static uint8_t current_alarm_index = 1;
uint32_t count = 0;

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */

void bsp_tim_init(TIM_HandleTypeDef *htim)
{
    btim_data = htim;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    HAL_TIM_PWM_Stop_DMA(btim_data, TIM_CHANNEL_1);
    data_sent_flag = 1;
}

// TODO: Find another solution to avoid using these get function

uint8_t *get_set_time_hour()
{
    return &set_time_hours;
}

uint8_t *get_set_time_minutes()
{
    return &set_time_minutes;
}

uint8_t *get_set_time_seconds()
{
    return &set_time_seconds;
}

uint8_t *get_set_time_date()
{
    return &set_time_date;
}

uint8_t *get_set_time_month()
{
    return &set_time_month;
}

uint8_t *get_set_time_year()
{
    return &set_time_year;
}

uint32_t drv_led_matrix_clear()
{
    for (int i = 0; i < MAX_LED; i++)
    {
        drv_led_matrix_set_led(i / 16, i % 16, 0, 0, 0);
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_set_led(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue)
{
    int led_num;
    if (row % 2 == 0)
    {
        // Even row (0-indexed), straight order
        led_num = row * 16 + col;
    }
    else
    {
        // Odd row (0-indexed), reverse order
        led_num = row * 16 + (15 - col);
    }
    if (led_num < 0 || led_num >= MAX_LED)
    {
        return D_LED_MATRIX_ERROR;
    } // Ensure led_num is within bounds
    led_data[led_num][0] = led_num;
    led_data[led_num][1] = green;
    led_data[led_num][2] = red;
    led_data[led_num][3] = blue;

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_set_brightness(uint8_t brightness)
{
#if USE_BRIGHTNESS

    if (brightness > 100)
        brightness = 100;

    for (int i = 0; i < MAX_LED; i++)
    {
        led_mod[i][0] = led_data[i][0];
        for (int j = 1; j < 4; j++)
        {
            // Adjust brightness based on percentage
            led_mod[i][j] = (led_data[i][j] * brightness) / 100;
        }
    }
#endif
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_ws2812_send()
{
    uint32_t indx = 0;
    uint32_t color;

    for (int i = 0; i < MAX_LED; i++)
    {
        color = ((led_mod[i][1] << 16) | (led_mod[i][2] << 8) | (led_mod[i][3]));
        for (int i = 23; i >= 0; i--)
        {
            if (color & (1 << i))
            {
                pwm_data[indx] = 33;
            }
            else
                pwm_data[indx] = 17;

            indx++;
        }
    }

    for (int i = 0; i < 50; i++)
    {
        pwm_data[indx] = 0;
        indx++;
    }

    HAL_TIM_PWM_Start_DMA(btim_data, TIM_CHANNEL_1, (uint32_t *)pwm_data, indx);
    while (!data_sent_flag)
    {
    };
    data_sent_flag = 0;

    return D_LED_MATRIX_SENT_OK;
}

uint32_t drv_led_matrix_draw_colon(uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue)
{
    // Draw the colon (two vertical dots)
    drv_led_matrix_set_led(row_offset + 1, col_offset, red, green, blue);
    drv_led_matrix_set_led(row_offset + 3, col_offset, red, green, blue);

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_digit(uint8_t num, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue)
{
    if (num < 0 || num > 9)
    {
        return D_LED_MATRIX_ERROR;
    }

    for (int y = 0; y < 5; y++)
    {
        // Reverse the x-axis position when drawing characters to handle mirror display issues.
        for (int x = 0; x < 3; x++)
        {
            int col = col_offset + (2 - x);
            int row = row_offset + y;
            if (number_patterns[num][y][x] == 1)
            {
                drv_led_matrix_set_led(row, col, red, green, blue);
            }
        }
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_letter(char letter, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue)
{
    if (letter < 'A' || letter > 'Z')
    {
        return D_LED_MATRIX_ERROR;
    }

    uint8_t index = letter - 'A';

    for (int y = 0; y < 5; y++)
    {
        // Reverse the x-axis position when drawing characters to handle mirror display issues.
        for (int x = 0; x < 3; x++)
        {
            int col = col_offset + (2 - x);
            int row = row_offset + y;
            if (letter_patterns[index][y][x] == 1)
            {
                drv_led_matrix_set_led(row, col, red, green, blue);
            }
        }
    }
    return D_LED_MATRIX_OK;
}

void drv_led_matrix_draw_string(const char *str, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t current_col_offset = col_offset;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
        {
            drv_led_matrix_draw_letter(str[i], row_offset, current_col_offset, red, green, blue);
            current_col_offset += 4; // Space between characters
        }
        else
        {
            current_col_offset += 2; // Space between characters when they meet a space
        }

        if (current_col_offset >= MATRIX_WIDTH)
        {
            break;
        }
    }
}

uint32_t drv_led_matrix_draw_frame(void)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            drv_led_matrix_set_led(row, col, clock_icon[row][col][0], clock_icon[row][col][1], clock_icon[row][col][2]);
        }
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_clock_icon(void)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            drv_led_matrix_set_led(row, col, clock_icon[row][col][0], clock_icon[row][col][1], clock_icon[row][col][2]);
        }
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_alarm_clock_icon(void)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            drv_led_matrix_set_led(row, col, alarm_clock_icon[row][col][0], alarm_clock_icon[row][col][1], alarm_clock_icon[row][col][2]);
        }
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_number(uint8_t number, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue)
{
    if (number < 0 || number > 99)
    {
        return D_LED_MATRIX_ERROR;
    }

    int tens = number / 10;
    int units = number % 10;

    drv_led_matrix_draw_digit(tens, row_offset, col_offset + 4, red, green, blue);
    drv_led_matrix_draw_digit(units, row_offset, col_offset, red, green, blue); // Adjust column offset for the second digit

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_number_sec(uint8_t number, uint8_t row_offset, uint8_t col_offset, uint8_t red, uint8_t green, uint8_t blue)
{
    if (number < 0 || number > 99)
    {
        return D_LED_MATRIX_ERROR;
    }
    int tens = number / 10;
    int units = number % 10;

    drv_led_matrix_draw_digit(tens, row_offset, col_offset + 5, red, green, blue);
    drv_led_matrix_draw_digit(units, row_offset, col_offset, red, green, blue); // Adjust column offset for the second digit

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_draw_time(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t red, uint8_t green, uint8_t blue)
{
    // Clear the matrix before drawing the new time
    for (int i = 0; i < MAX_LED; i++)
    {
        drv_led_matrix_set_led(i / 16, i % 16, 0, 0, 0);
    }

    // Draw hours
    drv_led_matrix_draw_number(hours, 2, 9, red, green, blue);

    // Draw first colon
    // draw_colon(3, 7, red, green, blue);

    // Draw minutes
    drv_led_matrix_draw_number(minutes, 2, 0, red, green, blue);

    // Draw second colon

    // Draw seconds
    drv_led_matrix_draw_number_sec(seconds, 9, 4, red, green, blue);

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_update_first_row(uint8_t seconds, uint8_t red, uint8_t green, uint8_t blue)
{
    for (int col = 0; col < 16; col++)
    {
        if (col < seconds)
        {
            drv_led_matrix_set_led(0, col, red, green, blue); // Light up the LED with the specified color
        }
        else
        {
            drv_led_matrix_set_led(0, col, 0, 0, 0); // Turn off the LED
        }
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_update_last_row(uint8_t seconds, uint8_t red, uint8_t green, uint8_t blue)
{
    for (int col = 15; col > 0; col--)
    {
        if (col > seconds)
        {
            drv_led_matrix_set_led(15, col, red, green, blue); // Light up the LED with the specified color
        }
        else
        {
            drv_led_matrix_set_led(15, col, 0, 0, 0); // Turn off the LED
        }
    }
    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_display_rtc_setting(uint8_t set_rtc, uint8_t blink_state)
{
    drv_led_matrix_clear();

    uint8_t red, green, blue;

    // Display hours
    red = ((set_rtc == D_LED_MATRIX_SET_TIME) && blink_state) ? 0 : 255;
    green = (set_rtc == D_LED_MATRIX_SET_TIME) ? 255 : 0;
    blue = (set_rtc == D_LED_MATRIX_SET_TIME) ? 255 : 0;
    drv_led_matrix_draw_string("EMIT", 2, 0, red, green, blue);
    // drv_led_matrix_draw_number(hours, 2, 9, red, green, blue);

    // Display minutes
    red = ((set_rtc == D_LED_MATRIX_SET_DATE) && blink_state) ? 0 : 255;
    green = (set_rtc == D_LED_MATRIX_SET_DATE) ? 255 : 0;
    blue = (set_rtc == D_LED_MATRIX_SET_DATE) ? 255 : 0;
    drv_led_matrix_draw_string("ETAD", 9, 0, red, green, blue);
    // drv_led_matrix_draw_number(minutes, 2, 0, red, green, blue);

    return D_LED_MATRIX_OK;
}

// TODO: Write a reusable function for display setting

uint32_t drv_led_matrix_display_alarm_setting(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t set_alarm, uint8_t blink_state)
{
    drv_led_matrix_clear();

    uint8_t red, green, blue;

    // Display hours
    red = ((set_alarm == D_LED_MATRIX_ALARM_HOUR || set_alarm == D_LED_MATRIX_ALARM_HOUR_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_alarm == D_LED_MATRIX_ALARM_HOUR || set_alarm == D_LED_MATRIX_ALARM_HOUR_PLUS_ONE) ? 255 : 0;
    blue = (set_alarm == D_LED_MATRIX_ALARM_HOUR || set_alarm == D_LED_MATRIX_ALARM_HOUR_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(hours, 2, 9, red, green, blue);

    // Display minutes
    red = ((set_alarm == D_LED_MATRIX_ALARM_MIN || set_alarm == D_LED_MATRIX_ALARM_MIN_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_alarm == D_LED_MATRIX_ALARM_MIN || set_alarm == D_LED_MATRIX_ALARM_MIN_PLUS_ONE) ? 255 : 0;
    blue = (set_alarm == D_LED_MATRIX_ALARM_MIN || set_alarm == D_LED_MATRIX_ALARM_MIN_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(minutes, 2, 0, red, green, blue);

    // Display seconds
    red = ((set_alarm == D_LED_MATRIX_ALARM_SEC || set_alarm == D_LED_MATRIX_ALARM_SEC_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_alarm == D_LED_MATRIX_ALARM_SEC || set_alarm == D_LED_MATRIX_ALARM_SEC_PLUS_ONE) ? 255 : 0;
    blue = (set_alarm == D_LED_MATRIX_ALARM_SEC || set_alarm == D_LED_MATRIX_ALARM_SEC_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number_sec(seconds, 9, 4, red, green, blue);

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_display_set_time_setting(uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t set_time, uint8_t blink_state)
{
    drv_led_matrix_clear();

    uint8_t red, green, blue;

    // Display hours
    red = (((set_time == D_LED_MATRIX_SET_TIME_HOUR) || (set_time == D_LED_MATRIX_SET_TIME_HOUR_PLUS_ONE)) && blink_state) ? 0 : 255;
    green = (set_time == D_LED_MATRIX_SET_TIME_HOUR || set_time == D_LED_MATRIX_SET_TIME_HOUR_PLUS_ONE) ? 255 : 0;
    blue = (set_time == D_LED_MATRIX_SET_TIME_HOUR || set_time == D_LED_MATRIX_SET_TIME_HOUR_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(hours, 2, 9, red, green, blue);

    // Display minutes
    red = ((set_time == D_LED_MATRIX_SET_TIME_MIN || set_time == D_LED_MATRIX_SET_TIME_MIN_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_time == D_LED_MATRIX_SET_TIME_MIN || set_time == D_LED_MATRIX_SET_TIME_MIN_PLUS_ONE) ? 255 : 0;
    blue = (set_time == D_LED_MATRIX_SET_TIME_MIN || set_time == D_LED_MATRIX_SET_TIME_MIN_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(minutes, 2, 0, red, green, blue);

    // Display seconds
    red = ((set_time == D_LED_MATRIX_SET_TIME_SEC || set_time == D_LED_MATRIX_SET_TIME_SEC_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_time == D_LED_MATRIX_SET_TIME_SEC || set_time == D_LED_MATRIX_SET_TIME_SEC_PLUS_ONE) ? 255 : 0;
    blue = (set_time == D_LED_MATRIX_SET_TIME_SEC || set_time == D_LED_MATRIX_SET_TIME_SEC_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number_sec(seconds, 9, 4, red, green, blue);

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_display_set_date_setting(uint8_t date, uint8_t month, uint8_t year, uint8_t set_date, uint8_t blink_state)
{
    drv_led_matrix_clear();

    uint8_t red, green, blue;

    // Display hours
    red = (((set_date == D_LED_MATRIX_SET_TIME_DATE) || (set_date == D_LED_MATRIX_SET_TIME_DATE_PLUS_ONE)) && blink_state) ? 0 : 255;
    green = (set_date == D_LED_MATRIX_SET_TIME_DATE || set_date == D_LED_MATRIX_SET_TIME_DATE_PLUS_ONE) ? 255 : 0;
    blue = (set_date == D_LED_MATRIX_SET_TIME_DATE || set_date == D_LED_MATRIX_SET_TIME_DATE_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(date, 2, 9, red, green, blue);

    // Display minutes
    red = ((set_date == D_LED_MATRIX_SET_TIME_MONTH || set_date == D_LED_MATRIX_SET_TIME_MONTH_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_date == D_LED_MATRIX_SET_TIME_MONTH || set_date == D_LED_MATRIX_SET_TIME_MONTH_PLUS_ONE) ? 255 : 0;
    blue = (set_date == D_LED_MATRIX_SET_TIME_MONTH || set_date == D_LED_MATRIX_SET_TIME_MONTH_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(month, 2, 0, red, green, blue);

    // Display seconds
    red = ((set_date == D_LED_MATRIX_SET_TIME_YEAR || set_date == D_LED_MATRIX_SET_TIME_YEAR_PLUS_ONE) && blink_state) ? 0 : 255;
    green = (set_date == D_LED_MATRIX_SET_TIME_YEAR || set_date == D_LED_MATRIX_SET_TIME_YEAR_PLUS_ONE) ? 255 : 0;
    blue = (set_date == D_LED_MATRIX_SET_TIME_YEAR || set_date == D_LED_MATRIX_SET_TIME_YEAR_PLUS_ONE) ? 255 : 0;
    drv_led_matrix_draw_number(20, 9, 8, red, green, blue);
    drv_led_matrix_draw_number(year, 9, 0, red, green, blue);

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_set_alarm_interactive(d_led_matrix_alarm_status_t set_alarm)
{
    current_time = HAL_GetTick();

    if (current_time - last_blink_time >= BLINK_INTERVAL)
    {
        blink_state = !blink_state;
        last_blink_time = current_time;
    }
    switch (set_alarm)
    {
    case D_LED_MATRIX_ALARM_HOUR:
        current_setting = D_LED_MATRIX_ALARM_HOUR;
        break;
    case D_LED_MATRIX_ALARM_MIN:
        current_setting = D_LED_MATRIX_ALARM_MIN;
        break;
    case D_LED_MATRIX_ALARM_SEC:
        current_setting = D_LED_MATRIX_ALARM_SEC;
        break;
    case D_LED_MATRIX_ALARM_HOUR_PLUS_ONE:
        alarms[current_alarm_index].hour = (alarms[current_alarm_index].hour + 1) % 24;
        break;
    case D_LED_MATRIX_ALARM_MIN_PLUS_ONE:
        alarms[current_alarm_index].min = (alarms[current_alarm_index].min + 1) % 60;
        break;
    case D_LED_MATRIX_ALARM_SEC_PLUS_ONE:
        alarms[current_alarm_index].sec = (alarms[current_alarm_index].sec + 1) % 60;
        break;
    case D_LED_MATRIX_ALARM_NEXT:
        current_alarm_index = (current_alarm_index + 1) % MAX_ALARMS;
        break;
    }
    drv_led_matrix_display_alarm_setting(
        alarms[current_alarm_index].hour,
        alarms[current_alarm_index].min,
        alarms[current_alarm_index].sec,
        set_alarm,
        blink_state);
    drv_led_matrix_set_brightness(1);
    drv_led_matrix_ws2812_send();

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_set_rtc_interactive(d_led_matrix_set_time_status_t set_rtc)
{
    current_time = HAL_GetTick();

    if (current_time - last_blink_time >= BLINK_INTERVAL)
    {
        blink_state = !blink_state;
        last_blink_time = current_time;
    }
    drv_led_matrix_display_rtc_setting(set_rtc, blink_state);
    drv_led_matrix_set_brightness(1);
    drv_led_matrix_ws2812_send();

    return D_LED_MATRIX_OK;
}

uint32_t drv_led_matrix_set_time_interactive(d_led_matrix_set_time_status_t set_time)
{
    current_time = HAL_GetTick();

    if (current_time - last_blink_time >= BLINK_INTERVAL)
    {
        blink_state = !blink_state;
        last_blink_time = current_time;
    }
    switch (set_time)
    {
    case D_LED_MATRIX_SET_TIME_HOUR:
        current_setting = D_LED_MATRIX_SET_TIME_HOUR;
        break;
    case D_LED_MATRIX_SET_TIME_MIN:
        current_setting = D_LED_MATRIX_SET_TIME_MIN;
        break;
    case D_LED_MATRIX_SET_TIME_SEC:
        current_setting = D_LED_MATRIX_SET_TIME_SEC;
        break;
    case D_LED_MATRIX_SET_TIME_HOUR_PLUS_ONE:
        set_time_hours = (set_time_hours + 1) % 24;
        break;
    case D_LED_MATRIX_SET_TIME_MIN_PLUS_ONE:
        set_time_minutes = (set_time_minutes + 1) % 60;
        break;
    case D_LED_MATRIX_SET_TIME_SEC_PLUS_ONE:
        set_time_seconds = (set_time_seconds + 1) % 60;
        break;
    case D_LED_MATRIX_SET_TIME:
        break;
    }
    drv_led_matrix_display_set_time_setting(set_time_hours, set_time_minutes, set_time_seconds, set_time, blink_state);
    drv_led_matrix_set_brightness(1);
    drv_led_matrix_ws2812_send();

    return D_LED_MATRIX_OK;
}

int drv_days_in_month(int month, int year)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        // Leap year check
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    default:
        return 30; // Default case (should not happen)
    }
}

uint32_t drv_led_matrix_set_date_interactive(d_led_matrix_set_date_status_t set_date)
{
    current_time = HAL_GetTick();

    if (current_time - last_blink_time >= BLINK_INTERVAL)
    {
        blink_state = !blink_state;
        last_blink_time = current_time;
    }
    switch (set_date)
    {
    case D_LED_MATRIX_SET_TIME_DATE:
        current_setting = D_LED_MATRIX_SET_TIME_DATE;
        break;
    case D_LED_MATRIX_SET_TIME_MONTH:
        current_setting = D_LED_MATRIX_SET_TIME_MONTH;
        break;
    case D_LED_MATRIX_SET_TIME_YEAR:
        current_setting = D_LED_MATRIX_SET_TIME_YEAR;
        break;
    case D_LED_MATRIX_SET_TIME_DATE_PLUS_ONE:
        if (set_time_date == drv_days_in_month(set_time_month, set_time_year))
        {
            set_time_date = 1;
        }
        else
        {
            set_time_date++;
        }
        break;
    case D_LED_MATRIX_SET_TIME_MONTH_PLUS_ONE:
        set_time_month++;
        if (set_time_month > 12)
        {
            set_time_month = 1;
        }
        break;
    case D_LED_MATRIX_SET_TIME_YEAR_PLUS_ONE:
        set_time_year = (set_time_year + 1) % 100;
        break;
    case D_LED_MATRIX_SET_DATE:
        break;
    }
    drv_led_matrix_display_set_date_setting(set_time_date, set_time_month, set_time_year, set_date, blink_state);
    drv_led_matrix_set_brightness(1);
    drv_led_matrix_ws2812_send();

    return D_LED_MATRIX_OK;
}

void drv_led_matrix_update_rgb_effect(uint32_t time)
{
    uint8_t red, green, blue;

    // RGB effect
    red = (time % 256);
    green = ((time + 85) % 256);
    blue = ((time + 170) % 256);

    for (uint8_t col = 0; col < MATRIX_WIDTH; col++)
    {
        // Update row 0
        drv_led_matrix_set_led(0, col, red, green, blue);
        // Update row 1
        drv_led_matrix_set_led(1, col, red, green, blue);
        // Update row 14
        drv_led_matrix_set_led(14, col, red, green, blue);
        // Update row 15
        drv_led_matrix_set_led(15, col, red, green, blue);
    }
}

void drv_matrix_led_digital_clock(void)
{
    drv_rtc_get_time();

    d_rtc_t *rtc = drv_rtc_get_rtc_ds1307();

    drv_led_matrix_draw_time(rtc->hour, rtc->min, rtc->sec, 0, 255, 0);
    drv_led_matrix_update_rgb_effect(count);
    count += 10;
    drv_led_matrix_set_brightness(1);
    drv_led_matrix_ws2812_send();
}

void drv_matrix_led_date_time(void)
{
    drv_led_matrix_clear();
    drv_rtc_get_time();

    d_rtc_t *rtc = drv_rtc_get_rtc_ds1307();

    drv_led_matrix_draw_number(rtc->date, 2, 9, 255, 0, 0);
    drv_led_matrix_draw_number(rtc->month, 2, 0, 0, 255, 0);
    drv_led_matrix_draw_number(20, 9, 8, 0, 0, 255);
    drv_led_matrix_draw_number(rtc->year, 9, 0, 255, 255, 255);
    drv_led_matrix_update_rgb_effect(count);
    count += 10;
    drv_led_matrix_set_brightness(1);
    drv_led_matrix_ws2812_send();
}

void drv_matrix_led_trigger_alarm(uint8_t alarm_index)
{
    drv_led_matrix_clear();
    drv_led_matrix_draw_string("GMO", 1, 4, 255, 0, 0);
    drv_led_matrix_draw_string("MRALA", 4, 0, 0, 0, 255);
    drv_led_matrix_draw_digit(alarm_index, 9, 9, 255, 255, 0);
    drv_led_matrix_set_brightness(10);
    drv_led_matrix_ws2812_send();
}

uint8_t drv_matrix_led_check_alarms(uint8_t current_hour, uint8_t current_minute, uint8_t current_second)
{
    for (uint8_t i = 1; i < MAX_ALARMS; i++)
    {
        if (alarms[i].hour == current_hour &&
            alarms[i].min == current_minute &&
            alarms[i].sec == current_second)
        {
            return i;
        }
    }
    return 0;
}
uint32_t drv_led_matrix_draw_icon(arr icon_struct)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            drv_led_matrix_set_led(row, col, icon_struct[row][col][0], icon_struct[row][col][1], icon_struct[row][col][2]);
        }
    }
    return D_LED_MATRIX_OK;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */
