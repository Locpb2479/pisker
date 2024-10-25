/**
 * @file       fft_handle.h
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    @1
 * @date       2024-08-06
 * @authors
 * @brief      Header file for FFT processing functions
 *
 * @author      Lu Trung Tin
 *              Nguyen Nhat Tri
 *              Pham Bao Loc
 *
 */

#ifndef FFT_HANDLE_H_
#define FFT_HANDLE_H_

/* Includes ----------------------------------------------------------- */
#include "main.h"
#include "arm_math.h"
/* Public defines ----------------------------------------------------- */
#define SAMPLE_FFT 2048
#define SAMPLE 2048
#define NUM_BANDS 16
#define NOISE_THRESHOLD 10
#define AMPLITUDE 1000
/* Public macros ------------------------------------------------------ */
#define min(a, b) (((a) < (b)) ? (a) : (b))
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Processes the FFT from the ADC buffer
 * @param doConvert Flag to indicate whether conversion is needed
 * @param adc_buffer Pointer to ADC buffer containing sampled data
 */
void fft_process(uint32_t *do_convert, uint16_t *adc_buffer);
/**
 * @brief Displays the FFT results on the LED matrix
 */
void fft_display(void);
#endif /* FFT_HANDLE_H_ */
