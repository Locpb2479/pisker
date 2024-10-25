/**
 * @file       sys_sound.h
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
#ifndef SYS_SOUND_H_
#define SYS_SOUND_H_
/* Includes ----------------------------------------------------------- */
#include "drv_dfplayer.h"
#include "drv_btn.h"
/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  SYS_SOUND_IDLE_STATE,
  SYS_SOUND_PLAY_STATE,
  SYS_SOUND_PAUSE_STATE,
} sys_sound_state_t;

typedef enum
{
  SYS_SOUND_OK,
  SYS_SOUND_ERROR
} sys_sound_result_t;
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the sound system.
 *
 * This function sets up the sound system, initializing the
 * DFPlayer module and any other necessary hardware or software
 * components. It should be called once during system
 * initialization.
 *
 * @return Status of the initialization operation.
 */
sys_sound_result_t sys_sound_init();

/**
 * @brief Handles sound system operations in the main loop.
 *
 * This function should be called regularly in the main loop to
 * manage sound playback based on button events. It checks the
 * state of the buttons and performs the appropriate actions,
 * such as play, pause, next, or previous track.
 *
 * @param button_state Pointer to a btn_info_t structure that holds
 *                     the current state of the buttons.
 * @return Status of the sound system operation.
 */
sys_sound_result_t sys_sound_loop(btn_info_t *button_state);
#endif /* SYS_SOUND_H_ */
/* End of file -------------------------------------------------------- */
