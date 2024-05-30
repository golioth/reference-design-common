/*
 * Copyright (c) 2024 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(pwm_buzzer, LOG_LEVEL_DBG);

#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

#include <pwm_buzzer.h>

int pwm_buzzer_init(const struct pwm_dt_spec *buzzer)
{
    LOG_DBG("Initializing PWM buzzer");

    if (!device_is_ready(buzzer->dev))
    {
        LOG_ERR("Buzzer PWM device not ready");
        return -ENODEV;
    }
    return 0;
}

void pwm_buzzer_beep(const struct pwm_dt_spec *buzzer)
{
    LOG_DBG("Playing beep sound");

    pwm_set_dt(buzzer, PWM_HZ(1000), PWM_HZ(1000) / 2);

    k_msleep(100);

    // turn the buzzer off
    pwm_set_pulse_dt(buzzer, 0);
}
