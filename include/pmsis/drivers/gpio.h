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
#include "pmsis/drivers/pad.h"

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
 * \brief Macro used to retrieve GPIO pin number.
 *
 * Right shift to do to get GPIO's pin number(needed to set the pin for GPIO mode).
 */
#define PI_GPIO_NUM_SHIFT  8
/**
 * \brief Macro used to retrieve GPIO number.
 *
 * Mask to apply to get GPIO's number.
 */
#define PI_GPIO_NUM_MASK   0xFF

/**
 * \enum pi_gpio_e
 * \brief GPIO pins.
 *
 * List of available GPIO pins.
 */
typedef enum
{
    PI_GPIO_A0_PAD_8_A4    = ((PI_PAD_8_A4_RF_SPIM1_MISO << PI_GPIO_NUM_SHIFT) | 0), /*!< GPIO_A0 */
    PI_GPIO_A1_PAD_9_B3    = ((PI_PAD_9_B3_RF_SPIM1_MOSI << PI_GPIO_NUM_SHIFT) | 1), /*!< GPIO_A1 */
    PI_GPIO_A2_PAD_10_A5   = ((PI_PAD_10_A5_RF_SPIM1_CSN << PI_GPIO_NUM_SHIFT) | 2), /*!< GPIO_A2 */
    PI_GPIO_A3_PAD_11_B4   = ((PI_PAD_11_B4_RF_SPIM1_SCK << PI_GPIO_NUM_SHIFT) | 3), /*!< GPIO_A3 */
    PI_GPIO_A0_PAD_12_A3   = ((PI_PAD_12_A3_RF_PACTRL0   << PI_GPIO_NUM_SHIFT) | 0), /*!< GPIO_A0 */
    PI_GPIO_A1_PAD_13_B2   = ((PI_PAD_13_B2_RF_PACTRL1   << PI_GPIO_NUM_SHIFT) | 1), /*!< GPIO_A1 */
    PI_GPIO_A2_PAD_14_A2   = ((PI_PAD_14_A2_RF_PACTRL2   << PI_GPIO_NUM_SHIFT) | 2), /*!< GPIO_A2 */
    PI_GPIO_A3_PAD_15_B1   = ((PI_PAD_15_B1_RF_PACTRL3   << PI_GPIO_NUM_SHIFT) | 3), /*!< GPIO_A3 */
    PI_GPIO_A4_PAD_16_A44  = ((PI_PAD_16_A44_RF_PACTRL4  << PI_GPIO_NUM_SHIFT) | 4), /*!< GPIO_A4 */
    PI_GPIO_A5_PAD_17_B40  = ((PI_PAD_17_B40_RF_PACTRL5  << PI_GPIO_NUM_SHIFT) | 5), /*!< GPIO_A5 */
    PI_GPIO_A4_PAD_18_A43  = ((PI_PAD_18_A43_CAM_PCLK    << PI_GPIO_NUM_SHIFT) | 4), /*!< GPIO_A4 */
    PI_GPIO_A5_PAD_19_A37  = ((PI_PAD_19_A37_CAM_HSYNC   << PI_GPIO_NUM_SHIFT) | 5), /*!< GPIO_A5 */
    PI_GPIO_A6_PAD_20_B39  = ((PI_PAD_20_B39_CAM_DATA0   << PI_GPIO_NUM_SHIFT) | 6), /*!< GPIO_A6 */
    PI_GPIO_A7_PAD_21_A42  = ((PI_PAD_21_A42_CAM_DATA1   << PI_GPIO_NUM_SHIFT) | 7), /*!< GPIO_A7 */
    PI_GPIO_A8_PAD_22_B38  = ((PI_PAD_22_B38_CAM_DATA2   << PI_GPIO_NUM_SHIFT) | 8), /*!< GPIO_A8 */
    PI_GPIO_A9_PAD_23_A41  = ((PI_PAD_23_A41_CAM_DATA3   << PI_GPIO_NUM_SHIFT) | 9), /*!< GPIO_A9 */
    PI_GPIO_A10_PAD_24_B37 = ((PI_PAD_24_B37_CAM_DATA4   << PI_GPIO_NUM_SHIFT) | 10), /*!< GPIO_A10 */
    PI_GPIO_A11_PAD_25_A40 = ((PI_PAD_25_A40_CAM_DATA5   << PI_GPIO_NUM_SHIFT) | 11), /*!< GPIO_A11 */
    PI_GPIO_A12_PAD_26_B36 = ((PI_PAD_26_B36_CAM_DATA6   << PI_GPIO_NUM_SHIFT) | 12), /*!< GPIO_A12 */
    PI_GPIO_A13_PAD_27_A38 = ((PI_PAD_27_A38_CAM_DATA7   << PI_GPIO_NUM_SHIFT) | 13), /*!< GPIO_A13 */
    PI_GPIO_A14_PAD_28_A36 = ((PI_PAD_28_A36_CAM_VSYNC   << PI_GPIO_NUM_SHIFT) | 14), /*!< GPIO_A14 */
    PI_GPIO_A15_PAD_29_B34 = ((PI_PAD_29_B34_CAM_SDA     << PI_GPIO_NUM_SHIFT) | 15), /*!< GPIO_A15 */
    PI_GPIO_A16_PAD_30_D1  = ((PI_PAD_30_D1_CAM_SCL      << PI_GPIO_NUM_SHIFT) | 16), /*!< GPIO_A16 */
    PI_GPIO_A17_PAD_31_B11 = ((PI_PAD_31_B11_TIMER0_CH0  << PI_GPIO_NUM_SHIFT) | 17), /*!< GPIO_A17 */
    PI_GPIO_A18_PAD_32_A13 = ((PI_PAD_32_A13_TIMER0_CH1  << PI_GPIO_NUM_SHIFT) | 18), /*!< GPIO_A18 */
    PI_GPIO_A19_PAD_33_B12 = ((PI_PAD_33_B12_TIMER0_CH2  << PI_GPIO_NUM_SHIFT) | 19), /*!< GPIO_A19 */
    PI_GPIO_A20_PAD_34_A14 = ((PI_PAD_34_A14_TIMER0_CH3  << PI_GPIO_NUM_SHIFT) | 20), /*!< GPIO_A20 */
    PI_GPIO_A21_PAD_35_B13 = ((PI_PAD_35_B13_I2S1_SCK    << PI_GPIO_NUM_SHIFT) | 21), /*!< GPIO_A21 */
    PI_GPIO_A22_PAD_36_A15 = ((PI_PAD_36_A15_I2S1_WS     << PI_GPIO_NUM_SHIFT) | 22), /*!< GPIO_A22 */
    PI_GPIO_A23_PAD_37_B14 = ((PI_PAD_37_B14_I2S1_SDI    << PI_GPIO_NUM_SHIFT) | 23), /*!< GPIO_A23 */
    PI_GPIO_A24_PAD_38_B6  = ((PI_PAD_38_B6_UART_RX      << PI_GPIO_NUM_SHIFT) | 24), /*!< GPIO_A24 */
    PI_GPIO_A25_PAD_39_A7  = ((PI_PAD_39_A7_UART_TX      << PI_GPIO_NUM_SHIFT) | 25), /*!< GPIO_A25 */
    PI_GPIO_A26_PAD_42_B10 = ((PI_PAD_42_B10_SPIM0_SDIO2 << PI_GPIO_NUM_SHIFT) | 26), /*!< GPIO_A26 */
    PI_GPIO_A27_PAD_43_A10 = ((PI_PAD_43_A10_SPIM0_SDIO3 << PI_GPIO_NUM_SHIFT) | 27), /*!< GPIO_A27 */
    PI_GPIO_A28_PAD_45_A8  = ((PI_PAD_45_A8_SPIM0_CSN1   << PI_GPIO_NUM_SHIFT) | 28), /*!< GPIO_A28 */
    PI_GPIO_A29_PAD_47_A9  = ((PI_PAD_47_A9_SPIS0_CSN    << PI_GPIO_NUM_SHIFT) | 29), /*!< GPIO_A29 */
    PI_GPIO_A30_PAD_48_B15 = ((PI_PAD_48_B15_SPIS0_MISO  << PI_GPIO_NUM_SHIFT) | 30), /*!< GPIO_A30 */
    PI_GPIO_A31_PAD_49_A16 = ((PI_PAD_49_A16_SPIS0_MOSI  << PI_GPIO_NUM_SHIFT) | 31) /*!< GPIO_A31 */
} pi_gpio_e;

/**
 * \brief Macro used to set pull activation.
 *
 * Right shift to do to set pull activation of a GPIO.
 */
#define PI_GPIO_PULL_OFFSET  0
/**
 * \brief Macro used to set drive strength.
 *
 * Right shift to do to set drive strength of a GPIO.
 */
#define PI_GPIO_DRIVE_OFFSET 1
/**
 * \brief Macro used to set direction.
 *
 * Right shift to do to set input/output mode of a GPIO.
 */
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

/**
 * \enum pi_gpio_notif_e
 * \brief Sensitivity of a GPIO for notifications.
 *
 * This is used to tell which GPIO value modification will trigger a
 * notification(IRQ).
 */
typedef enum
{
    PI_GPIO_NOTIF_FALL = 0x0, /*!< IRQ are sent on a falling edge on the GPIO value. */
    PI_GPIO_NOTIF_RISE = 0x1, /*!< IRQ are sent on a rising edge on the GPIO value. */
    PI_GPIO_NOTIF_EDGE = 0x2, /*!< IRQ are sent on a rising or a falling edge on the GPIO value. */
    PI_GPIO_NOTIF_NONE = 0x3  /*!< No IRQ. */
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
 * \param conf           A pointer to the GPIO configuration.
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
 * \param device         A pointer to the device structure of the device to open.
 *
 * \note The device structure is allocated by the caller and must be kept alive
 * until the device is closed.
 *
 * \retval               0 if the operation is successfull,
 * \retval               ERROR_CODE if there was an error.
 */
int pi_gpio_open(struct pi_device *device);

/** \brief Configure a GPIO.
 *
 * This function can be used to configure several aspects of a GPIO, like
 * the direction.
 *
 * \param device         A pointer to the device structure this GPIO belongs to.
 * \param gpio           The GPIO number within the port (from 0 to 31).
 * \param flags          A bitfield of flags specifying how to configure the GPIO.
 *
 * \retval               0 if the operation is successfull,
 * \retval               ERROR_CODE if there was an error.
 */
int pi_gpio_pin_configure(struct pi_device *device, pi_gpio_e gpio,
                          pi_gpio_flags_e flags);

/** \brief Set value of a single GPIO.
 *
 * This function can be used to change the value of a single GPIO.
 *
 * \param device         A pointer to the device structure this GPIO belongs to.
 * \param pin            The GPIO number within the port (from 0 to 31).
 * \param value          The value to be set. This can be either 0 or 1.
 *
 * \retval               0 if the operation is successfull,
 * \retval               ERROR_CODE if there was an error.
 */
int pi_gpio_pin_write(struct pi_device *device, uint32_t pin, uint32_t value);

/** \brief Get value of a single GPIO.
 *
 * This function can be used to get the value of a single GPIO.
 *
 * \param device         A pointer to the device structure this GPIO belongs to.
 * \param pin            The GPIO number. Must be between 0 and 31.
 * \param value          A pointer to the variable where the GPIO value should be
 *                       returned. The value will be either 0 or 1.
 *
 * \retval               0 if the operation is successfull,
 * \retval               ERROR_CODE if there was an error.
 */
int pi_gpio_pin_read(struct pi_device *device, uint32_t pin, uint32_t *value);

/** \brief Configure notifications for a GPIO.
 *
 * This function can be used to configure how to be notified
 * by GPIO value modifications. By default, notifications will be buffered
 * and can be read and cleared.
 *
 * \param device         A pointer to the device structure this GPIO belongs to.
 * \param pin            The GPIO number. Must be between 0 and 31.
 * \param flags          The flags to configure how the notification should be
 *   triggered.
 */
void pi_gpio_pin_notif_configure(struct pi_device *device, uint32_t pin,
                                 pi_gpio_notif_e flags);

/** \brief Clear notification for a GPIO.
 *
 * This function can be used to clear the notification of a GPIO. A GPIO
 * notification is buffered and ths function must be called to clear it so
 * that a new one can be seen.
 *
 * \param device         A pointer to the device structure this GPIO belongs to.
 * \param pin            The GPIO number. Must be between 0 and 31.
 */
void pi_gpio_pin_notif_clear(struct pi_device *device, uint32_t pin);

/** \brief Get the value of a notification for a GPIO.
 *
 * This function can be used to get the value of a notification of a GPIO.
 * It returns 1 if at least one notification was received since the last time
 * it was cleared.
 * Reading the notification does not clear it.
 *
 * \param device         A pointer to the device structure this GPIO belongs to.
 * \param pin            The GPIO number. Must be between 0 and 31.
 * \return               1 if a notification was received, otherwise 0.
 *
 * \retval               0 if the operation is successfull,
 * \retval               ERROR_CODE if there was an error.
 */
int pi_gpio_pin_notif_get(struct pi_device *device, uint32_t pin);

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

int pi_gpio_pin_task_add(struct pi_device *device, uint32_t pin, pi_task_t *task,
                         pi_gpio_notif_e flags);

int pi_gpio_pin_task_remove(struct pi_device *device, uint32_t pin);

/// @endcond


#endif  /* __PI_DRIVERS_GPIO_H__ */
