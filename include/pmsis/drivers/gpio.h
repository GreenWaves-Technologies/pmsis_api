/*
 * Copyright (C) 2018 GreenWaves Technologies
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

#include "pmsis/pmsis_types.h"

/**
* @ingroup groupDrivers
*/



/**
 * @defgroup GPIO GPIO
 *
 * The GPIO driver provides support for controlling GPIOs.
 *
 */

/**
 * @addtogroup GPIO
 * @{
 */

/**@{*/


/**
 * \enum pi_gpio_pin_e
 * \brief GPIO pins.
 *
 * List of available GPIO pins.
 */
typedef enum
{
    PI_GPIO_A0_PAD_8_A4        = 0,
    PI_GPIO_A1_PAD_9_B3        = 1,
    PI_GPIO_A2_PAD_10_A5       = 2,
    PI_GPIO_A3_PAD_11_B4       = 3,
    PI_GPIO_A0_PAD_12_A3       = 0,
    PI_GPIO_A1_PAD_13_B2       = 1,
    PI_GPIO_A2_PAD_14_A2       = 2,
    PI_GPIO_A3_PAD_15_B1       = 3,
    PI_GPIO_A4_PAD_16_A44      = 4,
    PI_GPIO_A5_PAD_17_B40      = 5,
    PI_GPIO_A4_PAD_18_A43      = 4,
    PI_GPIO_A5_PAD_19_A37      = 5,
    PI_GPIO_A6_PAD_20_B39      = 6,
    PI_GPIO_A7_PAD_21_A42      = 7,
    PI_GPIO_A8_PAD_22_B38      = 8,
    PI_GPIO_A9_PAD_23_A41      = 9,
    PI_GPIO_A10_PAD_24_B37     = 10,
    PI_GPIO_A11_PAD_25_A40     = 11,
    PI_GPIO_A12_PAD_26_B36     = 12,
    PI_GPIO_A13_PAD_27_A38     = 13,
    PI_GPIO_A14_PAD_28_A36     = 14,
    PI_GPIO_A15_PAD_29_B34     = 15,
    PI_GPIO_A16_PAD_30_D1      = 16,
    PI_GPIO_A17_PAD_31_B11     = 17,
    PI_GPIO_A18_PAD_32_A13     = 18,
    PI_GPIO_A19_PAD_33_B12     = 19,
    PI_GPIO_A20_PAD_34_A14     = 20,
    PI_GPIO_A21_PAD_35_B13     = 21,
    PI_GPIO_A22_PAD_36_A15     = 22,
    PI_GPIO_A23_PAD_37_B14     = 23,
    PI_GPIO_A24_PAD_38_B6      = 24,
    PI_GPIO_A25_PAD_39_A7      = 25,
    PI_GPIO_A26_PAD_42_B10     = 26,
    PI_GPIO_A27_PAD_43_A10     = 27,
    PI_GPIO_A28_PAD_45_A8      = 28,
    PI_GPIO_A29_PAD_47_A9      = 29,
    PI_GPIO_A30_PAD_48_B15     = 30,
    PI_GPIO_A31_PAD_49_A16     = 31
} pi_gpio_pin_e;

#define PI_GPIO_PULL_OFFSET  0
#define PI_GPIO_DRIVE_OFFSET 1
#define PI_GPIO_MODE_OFFSET  2
/**
 * \enum pi_gpio_flags_e
 * \brief GPIO configuration flags.
 *
 * Flags to configure gpio : input/output mode, drive strength, pull activation.
 */
typedef enum
{
    PI_GPIO_PULL_DISABLE        = (0 << PI_GPIO_PULL_OFFSET),  /*!< Disable pull. */
    PI_GPIO_PULL_ENABLE         = (1 << PI_GPIO_PULL_OFFSET),  /*!< Enable pull. */
    PI_GPIO_DRIVE_STRENGTH_LOW  = (0 << PI_GPIO_DRIVE_OFFSET), /*!< Low drive strength. */
    PI_GPIO_DRIVE_STRENGTH_HIGH = (1 << PI_GPIO_DRIVE_OFFSET), /*!< High drive strength. */
    PI_GPIO_INPUT               = (0 << PI_GPIO_MODE_OFFSET),  /*!< GPIO is an input. */
    PI_GPIO_OUTPUT              = (1 << PI_GPIO_MODE_OFFSET)   /*!< GPIO is an output. */
} pi_gpio_flags_e;

/** \enum pi_gpio_notif_e
 * \brief Sensitivity of a GPIO for notifications.
 *
 * This is used to tell which GPIO value modification will trigger a
 * notification.
 */
typedef enum
{
    PI_GPIO_NOTIF_FALL = 0x0,    /*!< Notifications are sent when there is both
      a rising edge or a falling edge on the GPIO value. */
    PI_GPIO_NOTIF_RISE = 0x1,    /*!< Notifications are sent when there is a
      rising edge on the GPIO value. */
    PI_GPIO_NOTIF_EDGE = 0x2,    /*!< Notifications are sent when there is a
      falling edge on the GPIO value. */
    PI_GPIO_NOTIF_NONE = 0x3     /*!< No notification is sent. */
} pi_gpio_notif_e;


/** \struct pi_gpio_conf
 * \brief GPIO configuration structure.
 *
 * This structure is used to pass the desired GPIO configuration to the
 * runtime when opening the device.
 */
struct pi_gpio_conf
{
    pi_device_e device; /*!< Interface type. */
    int32_t port;       /*!< GPIO port. Each port can contain up to 32 GPIOs. */
};

/** \brief Initialize a GPIO configuration with default values.
 *
 * The structure containing the configuration must be kept alive until the
 * device is opened.
 *
 * \param conf A pointer to the GPIO configuration.
 */
void pi_gpio_conf_init(struct pi_gpio_conf *conf);

/** \brief Open a GPIO device.
 *
 * This function must be called before the GPIO device can be used.
 * It will do all the needed configuration to make it usable and initialize
 * the handle used to refer to this opened device when calling other functions.
 * This operation must be done once for each GPIO port, i.e. for every group
 * of 32 GPIOs. The opened device can then be used to drive the 32 GPIOs.
 *
 * \param device    A pointer to the device structure of the device to open.
 *   This structure is allocated by the called and must be kept alive until the
 *   device is closed.
 * \return          0 if the operation is successfull, -1 if there was an error.
 */
int pi_gpio_open(struct pi_device *device);

/** \brief Configure a GPIO.
 *
 * This function can be used to configure several aspects of a GPIO, like
 * the direction.
 *
 * \param device A pointer to the device structure this GPIO belongs to.
 * \param pin    The GPIO number within the port (from 0 to 31).
 * \param flags  A bitfield of flags specifying how to configure the GPIO.
 */
int pi_gpio_pin_configure(struct pi_device *device, int pin,
    pi_gpio_flags_e flags);

/** \brief Set value of a single GPIO.
 *
 * This function can be used to change the value of a single GPIO.
 *
 * \param device A pointer to the device structure this GPIO belongs to.
 * \param pin    The GPIO number within the port (from 0 to 31).
 * \param value  The value to be set. This can be either 0 or 1.
 */
int pi_gpio_pin_write(struct pi_device *device, int pin, uint32_t value);

/** \brief Get value of a single GPIO.
 *
 * This function can be used to get the value of a single GPIO.
 *
 * \param device A pointer to the device structure this GPIO belongs to.
 * \param pin   The GPIO number. Must be between 0 and 31.
 * \param value   A pointer to the variable where the GPIO value should be
 *   returned. The value will be either 0 or 1.
 * \return          0 if the operation is successfull, -1 if there was an error.
 */
int pi_gpio_pin_read(struct pi_device *device, int pin, uint32_t *value);

/** \brief Configure notifications for a GPIO.
 *
 * This function can be used to configure how to be notified
 * by GPIO value modifications. By default, notifications will be buffered
 * and can be read and cleared.
 *
 * \param device A pointer to the device structure this GPIO belongs to.
 * \param pin   The GPIO number. Must be between 0 and 31.
 * \param flags  The flags to configure how the notification should be
 *   triggered.
 */
void pi_gpio_pin_notif_configure(struct pi_device *device, int pin,
    pi_gpio_notif_e flags);

/** \brief Clear notification for a GPIO.
 *
 * This function can be used to clear the notification of a GPIO. A GPIO
 * notification is buffered and ths function must be called to clear it so
 * that a new one can be seen.
 *
 * \param device A pointer to the device structure this GPIO belongs to.
 * \param pin   The GPIO number. Must be between 0 and 31.
 */
void pi_gpio_pin_notif_clear(struct pi_device *device, int pin);

/** \brief Get the value of a notification for a GPIO.
 *
 * This function can be used to get the value of a notification of a GPIO.
 * It returns 1 if at least one notification was received since the last time
 * it was cleared.
 * Reading the notification does not clear it.
 *
 * \param device A pointer to the device structure this GPIO belongs to.
 * \param pin   The GPIO number. Must be between 0 and 31.
 * \return       1 if a notification was received, otherwise 0.
 */
int pi_gpio_pin_notif_get(struct pi_device *device, int pin);

//!@}

/**
 * @} end of GPIO
 */



/// @cond IMPLEM

int pi_gpio_mask_configure(struct pi_device *device, uint32_t mask,
    pi_gpio_flags_e flags);

int pi_gpio_mask_write(struct pi_device *device, uint32_t mask, uint32_t value);

int pi_gpio_mask_read(struct pi_device *device, uint32_t mask, uint32_t *value);

int pi_gpio_mask_task_add(struct pi_device *device, uint32_t mask,
    pi_task_t *task, pi_gpio_notif_e flags);

int pi_gpio_mask_task_remove(struct pi_device *device, uint32_t mask);

int pi_gpio_pin_task_add(struct pi_device *device, int pin, pi_task_t *task,
    pi_gpio_notif_e flags);

int pi_gpio_pin_task_remove(struct pi_device *device, int pin);

/// @endcond


#endif  /* __PI_DRIVERS_GPIO_H__ */
