/*
 * Copyright (c) 2024 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(pwm_buzzer_songs, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

#include <pwm_buzzer_songs.h>

#define FUNKYTOWN_NOTES 13
#define MARIO_NOTES 36
#define GOLIOTH_NOTES 12

// clang-format off

struct note_duration funkytown_song_notes[FUNKYTOWN_NOTES] = {
    {.note = C5,   .duration = quarter},
    {.note = REST, .duration = eigth},
    {.note = C5,   .duration = quarter},
    {.note = Bb4,  .duration = quarter},
    {.note = C5,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = G4,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = G4,   .duration = quarter},
    {.note = C5,   .duration = quarter},
    {.note = F5,   .duration = quarter},
    {.note = E5,   .duration = quarter},
    {.note = C5,   .duration = quarter}
};

struct note_duration mario_song_notes[MARIO_NOTES] = {
    {.note = E6,   .duration = quarter},
    {.note = REST, .duration = eigth},
    {.note = E6,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = E6,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = C6,   .duration = quarter},
    {.note = E6,   .duration = half},
    {.note = G6,   .duration = half},
    {.note = REST, .duration = quarter},
    {.note = G4,   .duration = whole},
    {.note = REST, .duration = whole},
    /* break in sound */
    {.note = C6,   .duration = half},
    {.note = REST, .duration = quarter},
    {.note = G5,   .duration = half},
    {.note = REST, .duration = quarter},
    {.note = E5,   .duration = half},
    {.note = REST, .duration = quarter},
    {.note = A5,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = B5,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = Bb5,  .duration = quarter},
    {.note = A5,   .duration = half},
    {.note = G5,   .duration = quarter},
    {.note = E6,   .duration = quarter},
    {.note = G6,   .duration = quarter},
    {.note = A6,   .duration = half},
    {.note = F6,   .duration = quarter},
    {.note = G6,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = E6,   .duration = quarter},
    {.note = REST, .duration = quarter},
    {.note = C6,   .duration = quarter},
    {.note = D6,   .duration = quarter},
    {.note = B5,   .duration = quarter}
};

struct note_duration golioth_song_notes[GOLIOTH_NOTES] = {
    {.note = C6,   .duration = quarter},
    {.note = REST, .duration = 100},
    {.note = G5,   .duration = 100},
    {.note = A5,   .duration = 100},
    {.note = Bb5,  .duration = 100},
    {.note = REST, .duration = 100},
    {.note = Bb5,  .duration = 100},
    {.note = REST, .duration = quarter},
    {.note = C5,   .duration = half},
    {.note = REST, .duration = half},
    {.note = REST, .duration = quarter},
    {.note = C6,   .duration = quarter}
};

const struct song funkytown_song = {
    .name = "Funkytown song",
    .notes = funkytown_song_notes,
    .notes_len = FUNKYTOWN_NOTES
};

const struct song mario_song = {
    .name = "Mario song",
    .notes = mario_song_notes,
    .notes_len = MARIO_NOTES
};

const struct song golioth_song = {
    .name = "Golioth song",
    .notes = golioth_song_notes,
    .notes_len = GOLIOTH_NOTES
};

// clang-format on

void pwm_buzzer_play_note(const struct pwm_dt_spec *buzzer,
                          const struct note_duration *note_duration)
{
    if (note_duration->note < 10)
    {
        // Low frequency notes represent a 'pause' where the buzzer is shut off
        pwm_set_pulse_dt(buzzer, 0);
    }
    else
    {
        pwm_set_dt(buzzer, PWM_HZ(note_duration->note), PWM_HZ(note_duration->note) / 2);
    }
    k_msleep(note_duration->duration);
}

void pwm_buzzer_play_song(const struct pwm_dt_spec *buzzer, const struct song *song)
{
    LOG_DBG("Playing %s", song->name);

    for (int i = 0; i < song->notes_len; i++)
    {
        pwm_buzzer_play_note(buzzer, &song->notes[i]);
    }

    // turn the buzzer off
    pwm_set_pulse_dt(buzzer, 0);
}

void pwm_buzzer_play_funkytown(const struct pwm_dt_spec *buzzer)
{
    pwm_buzzer_play_song(buzzer, &funkytown_song);
}

void pwm_buzzer_play_mario(const struct pwm_dt_spec *buzzer)
{
    pwm_buzzer_play_song(buzzer, &mario_song);
}

void pwm_buzzer_play_golioth(const struct pwm_dt_spec *buzzer)
{
    pwm_buzzer_play_song(buzzer, &golioth_song);
}
