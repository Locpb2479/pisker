/**
 * @file       button_system.c
 * @copyright  Copyright (C) 2024 ITRVN. All rights reserved.
 * @version    1.0.0
 * @date       2024-07-06
 * @author     Tin Lu Trung
 * @author     Loc Pham Bao
 * @author     Tri Nguyen Nhat
 *             
 * @brief      Button System
 *             The code for manage button system in GPIO_Project
 *             
 * @note       
 */
/* Includes ----------------------------------------------------------- */
#include <sys_btn.h>
/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */

/* Private variables -------------------------------------------------- */
uint8_t sbtn_input = 0;
uint8_t sbtn_pre_input = 0;
uint32_t sbtn_timeup = 0;
uint32_t sbtn_timedown = 0;
sys_btn_event_t sbtn_event = SYS_BTN_EVENT_RELEASE;
sys_btn_state_t sbtn_state = SYS_BTN_STATE_RELEASE;
/* Private function prototypes ---------------------------------------- */
void sys_btn_reset();
/**
 * @brief  Determining the event of the button
 *
 * @param[in]     None
 * @return				Event of the button
 *  - NO_PRESS: No thing happened in button
 *  - SINGLE_CLICK: There is a single-click event
 *  - LONG_PRESS: There is a holing event
 *  - DOUBLE_CLICK: Ther is a double-click event
 */
sys_btn_event_t sys_btn_get_event()
{
  uint32_t now = HAL_GetTick();
  //Check change
//  if(sbtn_input != btn_read())
//    {
//      sbtn_pre_input = sbtn_input;
//      sbtn_input = !sbtn_input;
//      switch(sbtn_input)
//      {
//        case GPIO_PIN_RESET:
//          {
//          sbtn_timedown = now;
//          }
//          break;
//        case GPIO_PIN_SET:
//          {
//          sbtn_timeup = now;
//          }
//          break;
//        default:
//          break;
//      }
//    }
//
//  switch(sbtn_state)
//  {
//  case SYS_BTN_STATE_RELEASE:
//    {
//      if(sbtn_pre_input == sbtn_input)
//	{
//	  sbtn_state = SYS_BTN_STATE_RELEASE;
//	  sbtn_event = SYS_BTN_EVENT_RELEASE;
//	}
//    if((sbtn_pre_input) && (sbtn_timedown - sbtn_timeup < DEBOUNCE_MILIS))
//      {
//        sbtn_state = SYS_BTN_STATE_RELEASE;
//        sbtn_event = SYS_BTN_EVENT_RELEASE;
//      }
//    if((sbtn_pre_input) && (sbtn_timedown - sbtn_timeup > DEBOUNCE_MILIS) && (sbtn_timedown - sbtn_timeup < SINGLE_CLICK_MAX) )
//      {
//        sbtn_state = SYS_BTN_STATE_PRESSED;
//        sbtn_event = SYS_BTN_EVENT_RELEASE;
//      }
//    if((sbtn_input) && (now - sbtn_timeup > LONG_MILIS_MIN))
//      {
//        sbtn_state = SYS_BTN_STATE_HOLDING;
//        sbtn_event = SYS_BTN_EVENT_HOLD;
//      }
//    }
//    break;
//  case SYS_BTN_STATE_PRESSED:
//    {
//      if((!sbtn_input) && (now - sbtn_timedown > DOUBLE_GAP_MILIS_MAX))
//        {
//          sbtn_state = SYS_BTN_STATE_RELEASE;
//          sbtn_event = SYS_BTN_EVENT_SINGLE_CLICK;
//          sys_btn_reset();
//        }
//      if((!sbtn_pre_input) && (now - sbtn_timedown < DOUBLE_GAP_MILIS_MAX))
//        {
//          sbtn_state = SYS_BTN_STATE_MAYBE_2_CLICK;
//          sbtn_event = SYS_BTN_EVENT_RELEASE;
//        }
//    }
//    break;
//  case SYS_BTN_STATE_MAYBE_2_CLICK:
//  {
//    if((sbtn_pre_input) && (sbtn_timedown - sbtn_timeup < DEBOUNCE_MILIS ))
//      {
//        sbtn_state = SYS_BTN_STATE_RELEASE;
//        sbtn_event = SYS_BTN_EVENT_SINGLE_CLICK;
//        sys_btn_reset();
//      }
//    if((sbtn_pre_input) && (sbtn_timedown - sbtn_timeup > DEBOUNCE_MILIS) && (sbtn_timedown - sbtn_timeup < SINGLE_CLICK_MAX) )
//      {
//        sbtn_state = SYS_BTN_STATE_2_CLICK;
//        sbtn_event = SYS_BTN_EVENT_RELEASE;
//      }
//    if((sbtn_input) && (now - sbtn_timeup > LONG_MILIS_MIN ))
//      {
//        sbtn_state = SYS_BTN_STATE_HOLDING;
//        sbtn_event = SYS_BTN_EVENT_HOLD;
//      }
//  }
//  break;
//  case SYS_BTN_STATE_2_CLICK:
//    {
//      if((!sbtn_input) && (now - sbtn_timedown) > DOUBLE_GAP_MILIS_MAX)
//        {
//          sbtn_state = SYS_BTN_STATE_RELEASE;
//          sbtn_event = SYS_BTN_EVENT_DOUBLE_CLICK;
//          sys_btn_reset();
//        }
//
//    }
//    break;
//  case SYS_BTN_STATE_HOLDING:
//    {
//      if((!sbtn_input))
//        {
//          sbtn_state = SYS_BTN_STATE_RELEASE;
//          sbtn_event = SYS_BTN_EVENT_RELEASE;
//        }
//    }
//    break;
//  }
  //return sbtn_event;
}
void sys_btn_reset()
{
  sbtn_pre_input = 0;
  sbtn_timeup = 0;
  sbtn_timedown = 0;
}
//  //Static variable
//  static uint32_t button_down_ts = 0 ;
//  static uint32_t button_up_ts = 0 ;
//  static bool double_pending = false ;
//  static bool long_press_pending = false ;
//  static bool button_down = 0;
//  //Initailaize the button event
//  button_event_t button_event = RELEASE ;
//  uint32_t now = HAL_GetTick();
//
//  // If state changed
//  if (button_down != sys_btn_state())
//    {
//      button_down = !button_down ;
//
//		//If the button state is Pressed, save the time
//		if (button_down)
//		{
//	  	// Timestamp button-down
//	  	button_down_ts = now ;
//		}
//		//If the button has released
//		else
//		{
//			// Save the time
//			button_up_ts = now ;
//			// If double decision pending
//			if (double_pending)
//			{
//				button_event = DOUBLE_CLICK ;
//				double_pending = false ;
//			}
//			// If long press
//			else if (long_press_pending)
//			{
//				button_event = RELEASE;
//			}
//			else
//			{
//				double_pending = true ;
//			}
//			// Cancel any long press pending
//			long_press_pending = false ;
//		}
//	}
//
//	// If button-up and double-press gap time expired, it was a single press
//	if ((!button_down) && (double_pending) && (now - button_up_ts > DOUBLE_GAP_MILIS_MAX))
//	{
//	  double_pending = false ;
//	  button_event = SINGLE_CLICK ;
//	}
//	// else if button-down for long-press...
//	else if ((!long_press_pending) && (button_down) && (now - button_down_ts > LONG_MILIS_MIN))
//	{
//	  button_event = HOLD;
//	  long_press_pending = true;
//	  double_pending = false;
//	}
//	return button_event;
//}

