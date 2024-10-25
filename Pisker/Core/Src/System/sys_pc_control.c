/**
 * @file       sys_pc_control.c
 * @copyright
 * @license
 * @version    1.0.0
 * @date
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 * @brief      System Manager for GPIO Project

 * @note       None
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef SYS_PC_CONTROL_H_
#define SYS_PC_CONTROL_H_
/* Includes ----------------------------------------------------------- */
#include "sys_pc_control.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/* Private function prototypes -----------------------------------------*/
/*Function definition --------------------------------------------------*/
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart->Instance == USART2)
  {
    bsp_uart_pc_control_handle_it(Size);
  }
}
#endif /* SYS_PC_CONTROL_H_ */
/* End of file -------------------------------------------------------- */
