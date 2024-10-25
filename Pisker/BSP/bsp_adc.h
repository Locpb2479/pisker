/**
 * @file       bsp_adc.h
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    @1
 * @date       2024-08-06
 * @authors
 * @brief      Header file for bsp_adc.c
 *
 * @note
 */

#ifndef BSP_ADC_H_
#define BSP_ADC_H_

/* Includes ------------------------------------------------------------------ */
#include "main.h"

/* Public defines ------------------------------------------------------------ */
/* Public enumerations/structures -------------------------------------------- */
typedef enum
{
  BSP_ADC_SUCCESS,
  BSP_ADC_READ_SUCCESS,
  BSP_ADC_ERROR,
  BSP_ADC_TIMEOUT
} bsp_adc_result_t;

/* Public macros ------------------------------------------------------------- */
/* Public variables ---------------------------------------------------------- */
/* Public function prototypes ------------------------------------------------ */
uint8_t bsp_adc_init(ADC_HandleTypeDef *hadc, DMA_HandleTypeDef *hdma);
uint8_t bsp_adc_start(uint16_t* adc_buffer, uint32_t lenght);
uint8_t bsp_adc_stop();
uint16_t* bsp_get_adc_buffer(void);
#endif /* BSP_ADC_H_ */
