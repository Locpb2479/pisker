/*
 * bsp_i2c.h
 *
 *  Created on: Jul 20, 2024
 *      Author: PC
 */

#ifndef BSP_BSP_I2C_H_
#define BSP_BSP_I2C_H_

/* Includes ------------------------------------------------------------------ */
#include "main.h"        // Main application header file
#include "drv_rtc.h"     // RTC driver header file
#include <stdint.h>      // Standard integer types

/* Public defines ------------------------------------------------------------ */

/* Public enumerations/structures -------------------------------------------- */
typedef struct
{
  I2C_HandleTypeDef *bsp_hi2c;
}
bsp_i2c_data_t;
/**
 * @brief I2C status enumeration
 */
typedef enum {
    BSP_I2C_OK = 0,
    BSP_I2C_ERROR,
    BSP_I2C_ERROR_ACK_FAILURE
}
bsp_i2c_status_t;

/* Public macros ------------------------------------------------------------- */

/* Public variables ---------------------------------------------------------- */

/* Public function prototypes ------------------------------------------------ */

/**
 * @brief       Initialize the I2C peripheral
 *
 * @param[in]   hi2c      Pointer to I2C handle structure
 */
bsp_i2c_status_t bsp_i2c_init(I2C_HandleTypeDef *hi2c);

/**
 * @brief       Get the I2C handle
 *
 * @return      Pointer to the I2C handle structure
 */
I2C_HandleTypeDef* bsp_get_i2c_handle(void);

/**
 * @brief       Write data buffer to I2C device
 *
 * @param[in]   hi          I2C handle structure
 * @param[in]   DEV_ADDR    Address of the I2C device
 * @param[in]   sizebuf     Size of the buffer to write
 */
bsp_i2c_status_t bsp_i2c_write_buffer(uint8_t DEV_ADDR, uint8_t sizebuf);

/**
 * @brief       Read data buffer from I2C device
 *
 * @param[in]   hi          I2C handle structure
 * @param[in]   DEV_ADDR    Address of the I2C device
 * @param[in]   sizebuf     Size of the buffer to read
 */
bsp_i2c_status_t bsp_i2c_read_buffer(uint8_t DEV_ADDR, uint8_t sizebuf);

#endif /* BSP_BSP_I2C_H_ */
