/*
 * Copyright (c) 2024 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PWM_BUZZER_SONGS_H__
#define __PWM_BUZZER_SONGS_H__

#include <stddef.h> /* for size_t */
#include <zephyr/drivers/pwm.h>

// clang-format off

// Note durations
#define sixteenth 38
#define eigth	  75
#define quarter	  150
#define half	  300
#define whole	  600

// Notes
#define C4  262
#define Db4 277
#define D4  294
#define Eb4 311
#define E4  330
#define F4  349
#define Gb4 370
#define G4  392
#define Ab4 415
#define A4  440
#define Bb4 466
#define B4  494
#define C5  523
#define Db5 554
#define D5  587
#define Eb5 622
#define E5  659
#define F5  698
#define Gb5 740
#define G5  784
#define Ab5 831
#define A5  880
#define Bb5 932
#define B5  988
#define C6  1046
#define Db6 1109
#define D6  1175
#define Eb6 1245
#define E6  1319
#define F6  1397
#define Gb6 1480
#define G6  1568
#define Ab6 1661
#define A6  1760
#define Bb6 1865
#define B6  1976

#define REST 1

// clang-format on

struct note_duration
{
    int note;      // hz
    int duration;  // msec
};

struct song
{
    char *name;
    struct note_duration *notes;
    size_t notes_len;
};

void pwm_buzzer_play_note(const struct pwm_dt_spec *buzzer,
                          const struct note_duration *note_duration);
void pwm_buzzer_play_song(const struct pwm_dt_spec *buzzer, const struct song *song);
void pwm_buzzer_play_funkytown(const struct pwm_dt_spec *buzzer);
void pwm_buzzer_play_mario(const struct pwm_dt_spec *buzzer);
void pwm_buzzer_play_golioth(const struct pwm_dt_spec *buzzer);

#endif /* __PWM_BUZZER_SONGS_H__ */
