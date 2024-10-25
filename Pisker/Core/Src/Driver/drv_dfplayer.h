/**
 * @file        drv_dfplayer.h
 * @brief       Header file for RTC driver
 * @version     1.0.0
 * @date        [Insert Date]
 * @author      Lu Trung Tin
 *              Nguyen Nhat Tri
 *              Pham Bao Loc
 *
 * This file contains definitions and function prototypes for interfacing with the RTC (Real-Time Clock).
 */
/* Define to prevent recursive inclusion ------------------------------ */
#ifndef INC_DRV_DFPLAYER_H_
#define INC_DRV_DFPLAYER_H_
/* Includes ------------------------------------------------------------------ */
#include "bsp_uart.h"
#include "stdio.h"
#include "main.h"
/* Public defines ------------------------------------------------------------ */

/* Public enumerate/structure ----------------------------------------- */
typedef enum
{
  DRV_DFPLAYER_OK,
  DRV_DFPLAYER_ERROR
} drv_dfplayer_status_t;
/* Public macros ------------------------------------------------------ */

/* Public variables --------------------------------------------------- */

/* Public function prototypes ----------------------------------------- */
/**
 * @brief Initializes the DFPlayer module.
 *
 * This function sets up the DFPlayer with the specified volume.
 * It should be called once during system initialization.
 *
 * @param volume Initial volume level (0-30).
 * @return Status of the initialization operation.
 */
drv_dfplayer_status_t drv_df_init(uint8_t volume);

/**
 * @brief Starts playback from the beginning.
 *
 * This function commands the DFPlayer to start playback from the
 * first track.
 *
 * @return Status of the playback operation.
 */
drv_dfplayer_status_t drv_df_playfromstart(void);

/**
 * @brief Skips to the next track.
 *
 * This function commands the DFPlayer to skip to the next track
 * in the playlist.
 *
 * @return Status of the skip operation.
 */
drv_dfplayer_status_t drv_df_next(void);

/**
 * @brief Pauses the current playback.
 *
 * This function pauses the playback of the current track.
 *
 * @return Status of the pause operation.
 */
drv_dfplayer_status_t drv_df_pause(void);

/**
 * @brief Skips to the previous track.
 *
 * This function commands the DFPlayer to skip to the previous track
 * in the playlist.
 *
 * @return Status of the skip operation.
 */
drv_dfplayer_status_t drv_df_previous(void);

/**
 * @brief Resumes playback of the current track.
 *
 * This function resumes playback of the track that was playing
 * before it was paused.
 *
 * @return Status of the playback operation.
 */
drv_dfplayer_status_t drv_df_playback(void);

/**
 * @brief Plays a random track.
 *
 * This function commands the DFPlayer to play a random track
 * from the playlist.
 *
 * @return Status of the playback operation.
 */
drv_dfplayer_status_t drv_df_playrandom(void);

/**
 * @brief Plays a specific file.
 *
 * This function commands the DFPlayer to play a specific file
 * based on its file number.
 *
 * @param file_number The number of the file to play.
 * @return Status of the playback operation.
 */
drv_dfplayer_status_t drv_df_playfile(uint8_t file_number);

drv_dfplayer_status_t drv_df_up_volume();

drv_dfplayer_status_t drv_df_down_volume();

/* End of file -------------------------------------------------------- */
#endif /* INC_DRV_DFPLAYER_H_ */
