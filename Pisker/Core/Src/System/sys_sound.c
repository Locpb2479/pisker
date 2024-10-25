/**
 * @file        sys_sound.c
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
#include "sys_sound.h"
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static sys_sound_state_t s_sound_state;
/* Private function prototypes ---------------------------------------- */
void sys_sound_fsm_update(btn_info_t *button_state);
void sys_sound_fsm_action();
/* Function definition ------------------------------------------------ */
sys_sound_result_t sys_sound_init()
{
	s_sound_state = SYS_SOUND_IDLE_STATE;
	return SYS_SOUND_OK;
}

void sys_sound_fsm(btn_info_t *button_state)
{
	switch (s_sound_state)
	{
	case SYS_SOUND_IDLE_STATE:
	{
		if (*button_state == SINGLE_CLICK_BUTTON)
		{
			s_sound_state = SYS_SOUND_PLAY_STATE;
			drv_df_playrandom();
		}
	}
	break;
	case SYS_SOUND_PLAY_STATE:
	{
		if (*button_state == SINGLE_CLICK_BUTTON)
		{
			s_sound_state = SYS_SOUND_PAUSE_STATE;
			drv_df_pause();
		}
		if (*button_state == DOUBLE_CLICK_BUTTON)
		{
			s_sound_state = SYS_SOUND_PLAY_STATE;
			drv_df_next();
		}
		sys_display_fft();
	}
	break;
	case SYS_SOUND_PAUSE_STATE:
	{
		if (*button_state == SINGLE_CLICK_BUTTON)
		{
			s_sound_state = SYS_SOUND_PLAY_STATE;
			drv_df_playback();
		}
	}
	}
}

sys_sound_result_t sys_sound_loop(btn_info_t *button_state)
{
	sys_sound_fsm(button_state);
}
