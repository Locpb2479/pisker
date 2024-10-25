/**
 * @file       fft.c
 * @version    1.0.0
 * @date       2024-07-06
 * @brief      FFT Driver
 *             The driver for FFT processing in STM32F411
 * @author      Lu Trung Tin
 *              Nguyen Nhat Tri
 *              Pham Bao Loc
 *
 */

/* Includes ----------------------------------------------------------- */
#include "fft_handle.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
float32_t input_fft[SAMPLE];            // Input array for FFT
float32_t output_fft[SAMPLE];           // Output array for FFT results
uint32_t band_values[NUM_BANDS];        // Array to store values for each frequency band
uint32_t old_bar_heights[NUM_BANDS];    // Array to store previous heights of bars in LED display
uint32_t peak[NUM_BANDS];               // Array to store peak values for each frequency band
arm_rfft_fast_instance_f32 fftInstance; // FFT instance for ARM CMSIS DSP

// RGB color values for each frequency band
const uint8_t colors[NUM_BANDS][3] = {
    {255, 0, 0},     // Red
    {0, 255, 0},     // Green
    {0, 0, 255},     // Blue
    {255, 255, 0},   // Yellow
    {0, 255, 255},   // Cyan
    {255, 0, 255},   // Magenta
    {255, 128, 0},   // Orange
    {128, 0, 255},   // Purple
    {0, 128, 128},   // Teal
    {128, 128, 0},   // Olive
    {255, 105, 180}, // Hot Pink
    {102, 32, 192},  // Light Gray
    {160, 120, 32},  // Tri-color
    {0, 5, 255},     // White
    {141, 0, 100},   // Maroon
    {0, 128, 128}    // Dark Cyan
};

/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */

/**
 * @brief Processes the FFT from the ADC buffer
 * @param doConvert Flag to indicate whether conversion is needed
 * @param adc_buffer Pointer to ADC buffer containing sampled data
 */
void fft_process(uint32_t *doConvert, uint16_t *adc_buffer)
{
    if (*doConvert == 0)
    {
        *doConvert = SAMPLE;

        // Copy ADC buffer to input FFT array and initialize output FFT array
        for (int i = 0; i < SAMPLE; i++)
        {
            input_fft[i] = (float32_t)adc_buffer[i];
            output_fft[i] = 0;
        }

        // Initialize FFT instance
        arm_rfft_fast_init_f32(&fftInstance, SAMPLE);

        // Perform FFT
        arm_rfft_fast_f32(&fftInstance, input_fft, output_fft, 0);

        // Calculate magnitude of complex numbers
        arm_cmplx_mag_f32(output_fft, input_fft, SAMPLE / 2);

        // Initialize band values to zero
        for (int i = 0; i < NUM_BANDS; i++)
        {
            band_values[i] = 0;
        }

        // Sum FFT values into frequency bands
        for (int i = 2; i < (SAMPLE / 2); i++)
        {
            if (input_fft[i] > NOISE_THRESHOLD)
            {
                if (i > 2 && i <= 5)
                    band_values[0] += (int)input_fft[i];
                else if (i > 5 && i <= 8)
                    band_values[1] += (int)input_fft[i];
                else if (i > 8 && i <= 12)
                    band_values[2] += (int)input_fft[i];
                else if (i > 12 && i <= 16)
                    band_values[3] += (int)input_fft[i];
                else if (i > 16 && i <= 22)
                    band_values[4] += (int)input_fft[i];
                else if (i > 22 && i <= 30)
                    band_values[5] += (int)input_fft[i];
                else if (i > 30 && i <= 40)
                    band_values[6] += (int)input_fft[i];
                else if (i > 40 && i <= 52)
                    band_values[7] += (int)input_fft[i];
                else if (i > 52 && i <= 65)
                    band_values[8] += (int)input_fft[i];
                else if (i > 65 && i <= 80)
                    band_values[9] += (int)input_fft[i];
                else if (i > 80 && i <= 98)
                    band_values[10] += (int)input_fft[i];
                else if (i > 98 && i <= 118)
                    band_values[11] += (int)input_fft[i];
                else if (i > 118 && i <= 140)
                    band_values[12] += (int)input_fft[i];
                else if (i > 140 && i <= 165)
                    band_values[13] += (int)input_fft[i];
                else if (i > 165 && i <= 195)
                    band_values[14] += (int)input_fft[i];
                else if (i > 195 && i <= 255)
                    band_values[15] += (int)input_fft[i];
            }
        }
    }
}

/**
 * @brief Displays the FFT results on the LED matrix
 */
void fft_display(void)
{
    for (int band = 0; band < NUM_BANDS; band++)
    {
        int bar_height = band_values[band] / AMPLITUDE;
        if (bar_height > 16)
            bar_height = 16;

        // Smooth the bar height changes
        bar_height = ((old_bar_heights[band] * 1) + bar_height) / 2;

        // Update peak values
        if (bar_height > peak[band])
        {
            peak[band] = min(16, bar_height);
        }

        // Set the LEDs for the current bar height
        for (int y = 0; y < bar_height; y++)
        {
            drv_led_matrix_set_led(y, band, colors[band][0], colors[band][1], colors[band][2]);
        }

        // Turn off LEDs above the bar height
        for (int y = bar_height; y < 16; y++)
        {
            drv_led_matrix_set_led(y, band, 0, 0, 0);
        }

        // Highlight the peak value
        if (peak[band] > 0)
        {
            drv_led_matrix_set_led(peak[band] - 1, band, 255, 255, 255);
        }

        // Store the current bar height for smoothing in the next iteration
        old_bar_heights[band] = bar_height;
    }

    // Decrease peak values over time
    for (int band = 0; band < NUM_BANDS; band++)
    {
        if (peak[band] > 0)
            peak[band] -= 1;
    }

    // Set brightness and send data to the LED matrix
    drv_led_matrix_set_brightness(2);
    drv_led_matrix_ws2812_send();
}
