/**
 * @file        bsp_i2c.c
 * @copyright
 * @license
 * @version     0.0.0
 * @date
 * @author      Lu Trung Tin
 *              Nguyen Duc Tri
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
#include <bsp_i2c.h>

/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
static bsp_i2c_data_t bi2c_data;
/* Private variables -------------------------------------------------- */

/* Private function prototypes ---------------------------------------- */

/* Function definitions ----------------------------------------------- */

bsp_i2c_status_t bsp_i2c_init(I2C_HandleTypeDef *hi2c)
{
    bi2c_data.bsp_hi2c = hi2c;
    return BSP_I2C_OK;
}


I2C_HandleTypeDef* bsp_get_i2c_handle(void)
{
  return bi2c_data.bsp_hi2c;
}

bsp_i2c_status_t bsp_i2c_write_buffer(uint8_t DEV_ADDR, uint8_t sizebuf)
{
    d_rtc_t *rtc = drv_rtc_get_rtc_ds1307();
    HAL_StatusTypeDef hal_status;
    uint32_t retry_count = 0;
    const uint32_t max_retries = 3;
    do
    {
     	hal_status = HAL_I2C_Master_Transmit(bi2c_data.bsp_hi2c, (uint16_t)DEV_ADDR, (uint8_t*)&rtc->i2c_buf, (uint16_t)sizebuf, HAL_TIMEOUT);
     	if (hal_status == HAL_OK)
     	{
     	  return BSP_I2C_OK;
     	}
     	retry_count++;
    }
    while (hal_status != HAL_OK && retry_count < max_retries);
    if (HAL_I2C_GetError(bi2c_data.bsp_hi2c) != BSP_I2C_ERROR_ACK_FAILURE)
    {
      return BSP_I2C_ERROR;
    }

    // If we've reached here, it means we've had repeated AF errors
    return BSP_I2C_ERROR_ACK_FAILURE;
}

bsp_i2c_status_t bsp_i2c_read_buffer(uint8_t DEV_ADDR, uint8_t sizebuf)
{
    d_rtc_t *rtc = drv_rtc_get_rtc_ds1307();
    HAL_StatusTypeDef hal_status;
    uint32_t retry_count = 0;
    const uint32_t max_retries = 3;

    do
    {
        hal_status = HAL_I2C_Master_Receive(bi2c_data.bsp_hi2c, (uint16_t)DEV_ADDR, (uint8_t*)&rtc->i2c_buf, (uint16_t)sizebuf, HAL_TIMEOUT);
        if (hal_status == HAL_OK) {
            return BSP_I2C_OK;
        }
        retry_count++;
    } while (hal_status != HAL_OK && retry_count < max_retries);

    if (HAL_I2C_GetError(bi2c_data.bsp_hi2c) != BSP_I2C_ERROR_ACK_FAILURE) {
        // Serious error occurred
        return BSP_I2C_ERROR;
    }

    // If we've reached here, it means we've had repeated AF errors
    return BSP_I2C_ERROR_ACK_FAILURE;
}

/* Private definitions ----------------------------------------------- */

/* End of file -------------------------------------------------------- */


