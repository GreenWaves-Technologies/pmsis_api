/*
 * Copyright (C) 2018 ETH Zurich, University of Bologna and GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PI_DRIVERS_GPIO_H__
#define __PI_DRIVERS_GPIO_H__

#include "pmsis_types.h"

typedef enum
{
    PI_GPIO_A0_PAD_8_A4     = 0,
    PI_GPIO_A0_PAD_12_A3    = 0,
    PI_GPIO_A1_PAD_9_B3     = 1,
    PI_GPIO_A1_PAD_13_B2    = 1,
    PI_GPIO_A2_PAD_10_A5    = 2,
    PI_GPIO_A2_PAD_14_A2    = 2,
    PI_GPIO_A3_PAD_11_B4    = 3,
    PI_GPIO_A3_PAD_15_B1    = 3,
    PI_GPIO_A4_PAD_16_A44   = 4,
    PI_GPIO_A4_PAD_18_A43   = 4,
    PI_GPIO_A5_PAD_17_B40   = 5,
    PI_GPIO_A5_PAD_19_A37   = 5,
    PI_GPIO_A6_PAD_20_B39   = 6,
    PI_GPIO_A7_PAD_21_A42   = 7,
    PI_GPIO_A8_PAD_22_B38   = 8,
    PI_GPIO_A9_PAD_23_A41   = 9,
    PI_GPIO_A10_PAD_24_B37  = 10,
    PI_GPIO_A11_PAD_25_A40  = 11,
    PI_GPIO_A12_PAD_26_B36  = 12,
    PI_GPIO_A13_PAD_27_A38  = 13,
    PI_GPIO_A14_PAD_28_A36  = 14,
    PI_GPIO_A15_PAD_29_B34  = 15,
    PI_GPIO_A16_PAD_30_D1   = 16,
    PI_GPIO_A17_PAD_31_B11  = 17,
    PI_GPIO_A18_PAD_32_A13  = 18,
    PI_GPIO_A19_PAD_33_B12  = 19,
    PI_GPIO_A20_PAD_34_A14  = 20,
    PI_GPIO_A21_PAD_35_B13  = 21,
    PI_GPIO_A22_PAD_36_A15  = 22,
    PI_GPIO_A23_PAD_37_B14  = 23,
    PI_GPIO_A24_PAD_38_B6   = 24,
    PI_GPIO_A25_PAD_39_A7   = 25,
    PI_GPIO_A26_PAD_42_B10  = 26,
    PI_GPIO_A27_PAD_43_A10  = 27,
    PI_GPIO_A28_PAD_45_A8   = 28,
    PI_GPIO_A29_PAD_47_A9   = 29,
    PI_GPIO_A30_PAD_48_B15  = 30,
    PI_GPIO_A31_PAD_49_A16  = 31
} pi_gpio_e;

typedef enum
{
    PI_GPIO_INPUT = 0,   /*!< The GPIO is an output, the chip can transmit a value. */
    PI_GPIO_OUTPUT = 1    /*!< The GPIO is an input, the chip can receive a value. */
} pi_gpio_dir_e;

typedef enum
{
    PI_GPIO_PULL_DISABLE = 0,   /*!< Disable pull.  */
    PI_GPIO_PULL_ENABLE  = 1    /*!< Enable pull.  */
} pi_gpio_pe_e;

typedef enum
{
    PI_GPIO_DRIVE_STRENGTH_LOW  = 0, /*!< Low drive strength.  */
    PI_GPIO_DRIVE_STRENGTH_HIGH = 1  /*!< High drive strength. */
} pi_gpio_ds_e;

typedef enum
{
    PI_GPIO_NOTIF_FALL = 0x0,    /*!< IRQ on falling edge. */
    PI_GPIO_NOTIF_RISE = 0x1,    /*!< IRQ on rising edge. */
    PI_GPIO_NOTIF_EDGE = 0x2,    /*!< IRQ on a rising edge or a falling edge. */
    PI_GPIO_NOTIF_NONE = 0x3
} pi_gpio_notif_e;

struct pi_gpio_conf
{
    uint8_t port;
};

void pi_gpio_conf_init(struct pi_gpio_conf *conf);

int32_t pi_gpio_open(struct pi_device *device);

int32_t pi_gpio_pin_configure(struct pi_device *device, uint8_t pin, pi_gpio_dir_e dir,
                              pi_gpio_pe_e pe, pi_gpio_ds_e ds);

void pi_gpio_pin_write(struct pi_device *device, uint8_t pin, uint32_t value);

int32_t pi_gpio_pin_read(struct pi_device *device, uint8_t pin, uint32_t *value);

int32_t pi_gpio_pin_task_add(struct pi_device *device, uint8_t pin, pi_task_t *task, pi_gpio_notif_e irq_type);

int32_t pi_gpio_pin_task_remove(struct pi_device *device, uint8_t pin);

int32_t pi_gpio_mask_configure(struct pi_device *device, uint32_t mask, pi_gpio_dir_e dir,
                               pi_gpio_pe_e pe, pi_gpio_ds_e ds);

void pi_gpio_mask_write(struct pi_device *device, uint32_t mask, uint32_t value);

int32_t pi_gpio_mask_read(struct pi_device *device, uint32_t mask, uint32_t *value);

int32_t pi_gpio_mask_task_add(struct pi_device *device, uint32_t mask, pi_task_t *task, pi_gpio_notif_e irq_type);

int32_t pi_gpio_mask_task_remove(struct pi_device *device, uint32_t mask);

void pi_gpio_pin_notif_configure(struct pi_device *device, uint8_t pin, pi_gpio_notif_e irq_type);

void pi_gpio_pin_notif_clear(struct pi_device *device, uint8_t pin);

int32_t pi_gpio_pin_notif_get(struct pi_device *device, uint8_t pin);

#endif  /* __PI_DRIVERS_GPIO_H__ */
