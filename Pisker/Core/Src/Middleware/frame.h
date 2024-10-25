/*
 * frame.h
 *
 *  Created on: Jul 31, 2024
 *      Author: PC
 */
#include <stdint.h>

#ifndef MIDDLEWARE_FRAME_H_
#define MIDDLEWARE_FRAME_H_

#define ROWS 16
#define COLS 16

extern const uint8_t number_patterns[10][5][3];

extern const uint8_t letter_patterns[26][5][3];

extern const uint8_t alarm_clock_icon[ROWS][COLS][3];

extern const uint8_t clock_icon[ROWS][COLS][3];

extern const uint8_t music_note_icon[ROWS][COLS][3];

typedef uint8_t arr[ROWS][COLS][3];

#endif /* MIDDLEWARE_FRAME_H_ */
