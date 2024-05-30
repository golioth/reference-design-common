/*
 * Copyright (c) 2024 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __PWM_BUZZER_H__
#define __PWM_BUZZER_H__

#include <zephyr/drivers/pwm.h>

int pwm_buzzer_init(const struct pwm_dt_spec *buzzer);
void pwm_buzzer_beep(const struct pwm_dt_spec *buzzer);

#endif /* __PWM_BUZZER_H__ */
