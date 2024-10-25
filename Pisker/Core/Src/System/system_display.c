/**
 * @file        system_set_time.c
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
#include <system_display.h>
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
sys_state_display_t s_state_display;
sys_state_display_t s_state_display_temp;

sys_state_set_alarm_t s_state_set_alarm_check;
sys_state_set_time_t s_state_set_time_check;

uint32_t blink_count = 0;

// Variable for FFT
static uint32_t do_convert_fft_flag = SAMPLE_FFT;
static uint16_t adc_buffer[SAMPLE_FFT];
static uint8_t fft_init_flag;
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
void sys_display_init(void)
{
  s_state_display = SYS_STATE_DISPLAY_DIGITAL_CLOCK;
  fft_init_flag = 0;
  bsp_adc_start(adc_buffer, SAMPLE_FFT);
}
void sys_display_music_icon(void)
{
  drv_led_matrix_clear();
  drv_led_matrix_draw_icon(music_note_icon);
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}

void sys_display_digital_clock_icon(void)
{
  drv_led_matrix_clear();
  drv_led_matrix_draw_clock_icon();
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}
void sys_display_set_rtc_icon(void)
{
  drv_led_matrix_clear();
  drv_led_matrix_draw_string("TES", 2, 3, 255, 0, 0);
  drv_led_matrix_draw_string("EM", 9, 0, 0, 0, 255);
  drv_led_matrix_draw_string("IT", 9, 9, 255, 255, 0);
  drv_led_matrix_update_rgb_effect(blink_count);
  blink_count += 10;
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}
void sys_display_set_alarm_icon(void)
{
  drv_led_matrix_clear();
  drv_led_matrix_draw_alarm_clock_icon();
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}
void sys_display_digital_clock(void)
{
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}
void sys_display_set_rtc(void)
{
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}
void sys_display_set_alarm(void)
{
  drv_led_matrix_update_rgb_effect(blink_count);
  blink_count += 10;
  drv_led_matrix_set_brightness(1);
  drv_led_matrix_ws2812_send();
}
void sys_display_fft(void)
{
  if (do_convert_fft_flag == 0)
  {
    fft_process(&do_convert_fft_flag, adc_buffer);
    fft_display();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM3)
  {
    if (do_convert_fft_flag > 0)
      do_convert_fft_flag--;
  }
}
