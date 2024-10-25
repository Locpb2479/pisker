/**
 * @file       system_manager.c
 * @copyright  Copyright (C) 2019 Fiot Co., Ltd. All rights reserved.
 * @license    This project is released under the Fiot License.
 * @version    1.0.0
 * @date       2024-08-03
 * @author     Tin Lu Trung
 *
 * @brief      System to manage manager all devices
 */
/* Includes ----------------------------------------------------------- */
#include "sys_manager.h"
/* Private defines ---------------------------------------------------- */

/* Private enumerate/structure ---------------------------------------- */
typedef enum
{
	DIGITAL_CLOCK_STATE,
	SET_RTC_STATE,
	SET_ALARM_STATE,
	MUSIC_STATE,
	MENU_STATE,
	ALARM_STATE,
	INVALID_STATE
} sys_state_t;

typedef enum
{
	DIGITAL_CLOCK,
	SET_RTC,
	SET_ALARM,
	MUSIC,
	INVALID_FEATURE
} sys_feature_t;

/* Private enumerate/structure ---------------------------------------- */

/* Private macros ----------------------------------------------------- */

/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static sys_state_t s_system_state = MENU_STATE;
static sys_feature_t s_system_feature = DIGITAL_CLOCK;
sys_state_set_time_t check_finish;
static uint8_t s_mng_index_clock;
static uint8_t s_mng_pc_index;
/* Private function prototypes ---------------------------------------- */
static sys_state_t sys_manager_update(btn_info_t *button_state);
static void sys_checking_alarm(void);
/* Function definitions ----------------------------------------------- */
sys_state_t sys_manager_update(btn_info_t *button_state)
{
	drv_btn_check_event(button_state);
	sys_checking_alarm();
	/* FSM */
	switch (s_system_state)
	{
	case MENU_STATE:
	{
		if (*button_state == SINGLE_CLICK_BUTTON)
		{
			// 1 click -> next feature
			s_system_feature++;
			// overwrite handle
			if (s_system_feature > MUSIC)
			{
				s_system_feature = DIGITAL_CLOCK;
			}
		}

		if ((*button_state == DOUBLE_CLICK_BUTTON) && (s_system_feature == DIGITAL_CLOCK))
		{
			s_system_state = DIGITAL_CLOCK_STATE;
		}

		else if ((*button_state == DOUBLE_CLICK_BUTTON) && (s_system_feature == SET_ALARM))
		{
			s_system_state = SET_ALARM_STATE;
		}

		else if ((*button_state == DOUBLE_CLICK_BUTTON) && (s_system_feature == SET_RTC))
		{
			s_system_state = SET_RTC_STATE;
		}
		else if ((*button_state == DOUBLE_CLICK_BUTTON) && (s_system_feature == MUSIC))
		{
			s_system_state = MUSIC_STATE;
		}
		break;
	}

	case DIGITAL_CLOCK_STATE:
	{
		if (*button_state == HOLD_BUTTON)
		{
			s_system_state = MENU_STATE;
		}
		break;
	}

	case SET_ALARM_STATE:
	{
		if (*button_state == HOLD_BUTTON)
		{
			s_system_state = MENU_STATE;
		}
		break;
	}

	case SET_RTC_STATE:
	{
		if ((*button_state == HOLD_BUTTON))
		{
			check_finish = 0;
			s_system_state = MENU_STATE;
		}
		break;
	}
	case MUSIC_STATE:
	{
		if (*button_state == HOLD_BUTTON)
		{
			s_system_state = MENU_STATE;
		}
		break;
	}
	case ALARM_STATE:
	{
		if (*button_state == HOLD_BUTTON)
		{
			s_system_state = MENU_STATE;
			drv_df_pause();
		}
		break;
	}
	case INVALID_STATE:
	  if (*button_state == HOLD_BUTTON)
	  		{
	  			s_system_state = MENU_STATE;
	  		}
	  		break;
	}
	return s_system_state;
}

sys_manger_error_t sys_manager_init(void)
{
	sys_display_init();
	sys_set_time_init();
	sys_set_alarm_init();
	drv_btn_init();
	drv_df_init(10);
	return SYS_MANAGER_OK;
}

sys_manger_error_t sys_manager_run(btn_info_t *button_state)
{
	sys_manger_error_t status = SYS_MANAGER_OK;
	sys_state_t s_state_check = MENU_STATE;
	while (status == SYS_MANAGER_OK)
	{
		/* code */
		s_state_check = sys_manager_update(button_state);

		if (s_state_check == MENU_STATE)
		{
			switch (s_system_feature)
			{
			case DIGITAL_CLOCK:
				sys_display_digital_clock_icon();
				break;
			case SET_RTC:
				sys_display_set_rtc_icon();
				break;
			case SET_ALARM:
				sys_display_set_alarm_icon();
				break;
			case MUSIC:
				sys_display_music_icon();
				break;
			case INVALID_FEATURE:
				break;
			}
		}
		else if (s_state_check == SET_RTC_STATE)
		{
			// do set_rtc
			if (check_finish != 1)
			{
				sys_display_set_rtc();
				check_finish = sys_set_time_loop(button_state);
			}
			else
			{
				s_system_state = MENU_STATE;
				check_finish = 0;
			}
		}

		else if (s_state_check == SET_ALARM_STATE)
		{
			// do set_alarm
			sys_display_set_alarm();
			sys_set_alarm_loop(button_state);
		}

		else if (s_state_check == DIGITAL_CLOCK_STATE)
		{
			// do set time
			sys_display_digital_clock();
			sys_digital_clock_loop(button_state);
		}
		else if (s_state_check == MUSIC_STATE)
		{
		    sys_sound_loop(button_state);
		}
		else if (s_state_check == ALARM_STATE)
		{
			drv_matrix_led_trigger_alarm(s_mng_index_clock);
			drv_df_playfile(1);
		}
	}

	return status;
}

void sys_checking_alarm(void)
{
	d_rtc_t *s_current_time;
	drv_rtc_get_time();
	s_current_time = drv_rtc_get_rtc_ds1307();
	s_mng_index_clock = drv_matrix_led_check_alarms(s_current_time->hour, s_current_time->min, s_current_time->sec);
	s_mng_pc_index = ds1307_notify_alarm();
	if (s_mng_index_clock || s_mng_pc_index)
		{
			s_system_state = ALARM_STATE;
		}
}
