/**
 * @file       bsp_adc.c
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    @1
 * @date       2024-08-06
 * @authors
 * @brief      ADC BSP (Board Support Package) functions implementation
 *
 * @note
 */

/* Includes ------------------------------------------------------------------ */
#include "bsp_adc.h"

/* Private macros ----------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static ADC_HandleTypeDef *_hadc = NULL;
static DMA_HandleTypeDef *_hdma = NULL;
static uint16_t *adc_buffer = NULL;
static uint32_t adc_length = 0;

/* Private function prototypes ---------------------------------------------- */
/* Public functions ---------------------------------------------------------- */

/**
 * @brief  Initialize the ADC and DMA.
 * @param  hadc: Pointer to ADC handle.
 * @param  hdma: Pointer to DMA handle.
 * @retval Result of the initialization.
 */
uint8_t bsp_adc_init(ADC_HandleTypeDef *hadc, DMA_HandleTypeDef *hdma)
{
    if (hadc == NULL || hdma == NULL)
    {
        return BSP_ADC_ERROR;
    }
    _hadc = hadc;
    _hdma = hdma;

    return BSP_ADC_SUCCESS;
}

/**
 * @brief  Start ADC conversion with DMA.
 * @param  hadc: Pointer to ADC handle.
 * @param  adc_buffer: Pointer to buffer where ADC values will be stored.
 * @param  length: Number of ADC samples to be read.
 * @retval Result of the start operation.
 */
uint8_t bsp_adc_start(uint16_t* buffer, uint32_t length)
{
    adc_buffer = buffer;
    adc_length = length;

    // Start ADC DMA
    if (HAL_ADC_Start_DMA(_hadc, (uint32_t*)adc_buffer, adc_length) != HAL_OK)
    {
        return BSP_ADC_ERROR;
    }

    return BSP_ADC_SUCCESS;
}

/**
 * @brief  Stop ADC conversion and DMA.
 * @retval Result of the stop operation.
 */
uint8_t bsp_adc_stop(void)
{
    if (_hadc == NULL || _hdma == NULL)
    {
        return BSP_ADC_ERROR;
    }
    if (HAL_ADC_Stop_DMA(_hadc) != HAL_OK)
    {
        return BSP_ADC_ERROR;
    }

    return BSP_ADC_SUCCESS;
}
/**
 * @brief  from ADC_DMA get adc_buffer.
 * @retval return adc_buffer.
 */
uint16_t* bsp_get_adc_buffer(void)
{
    if (adc_buffer == NULL)
    {
      return BSP_ADC_ERROR;
    }
    return adc_buffer;
}