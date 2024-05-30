# Copyright (C) 2024 Golioth, Inc.
# SPDX-License-Identifier: Apache-2.0

zephyr_library()
zephyr_library_sources(pwm_buzzer.c)
zephyr_library_sources_ifdef(CONFIG_PWM_BUZZER_SONGS pwm_buzzer_songs.c)
