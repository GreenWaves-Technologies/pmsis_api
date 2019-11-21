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

#ifndef __PMSIS_DRIVERS_I2S_H__
#define __PMSIS_DRIVERS_I2S_H__

#include <stdint.h>

typedef uint8_t pi_i2s_fmt_t;

/** Data Format bit field position. */
#define PI_I2S_FMT_DATA_FORMAT_SHIFT           0
/** Data Format bit field mask. */
#define PI_I2S_FMT_DATA_FORMAT_MASK            (0x7 << PI_I2S_FMT_DATA_FORMAT_SHIFT)

/** @brief Standard I2S Data Format.
 *
 * Serial data is transmitted in two's complement with the MSB first. Both
 * Word Select (WS) and Serial Data (SD) signals are sampled on the rising edge
 * of the clock signal (SCK). The MSB is always sent one clock period after the
 * WS changes. Left channel data are sent first indicated by WS = 0, followed
 * by right channel data indicated by WS = 1.
 *
 *        -. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-. .-.
 *     SCK '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '-' '
 *        -.                               .-------------------------------.
 *     WS  '-------------------------------'                               '----
 *        -.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.---.
 *     SD  |   |MSB|   |...|   |LSB| x |...| x |MSB|   |...|   |LSB| x |...| x |
 *        -'---'---'---'---'---'---'---'---'---'---'---'---'---'---'---'---'---'
 *             | Left channel                  | Right channel                 |
 */
#define PI_I2S_FMT_DATA_FORMAT_I2S             (0 << PI_I2S_FMT_DATA_FORMAT_SHIFT)

#define PI_I2S_FMT_DATA_FORMAT_PDM             (1 << PI_I2S_FMT_DATA_FORMAT_SHIFT)


typedef uint8_t pi_i2s_opt_t;

/** Trigger command */
enum pi_i2s_ioctl_cmd {
    /** @brief Start the transmission / reception of data.
     *
     * If the interface is configured for TX, some data has to be queued for transmission by
     * the pi_i2s_write() function. This trigger can be used in READY state
     * only and changes the interface state to RUNNING.
     */
    PI_I2S_IOCTL_START,
    /** @brief Stop the transmission / reception of data.
     *
     * Stop the transmission / reception of data at the end of the current
     * memory block. This trigger can be used in RUNNING state only and at
     * first changes the interface state to STOPPING. When the current TX /
     * RX block is transmitted / received the state is changed to READY.
     * Subsequent START trigger will resume transmission / reception where
     * it stopped.
     */
    PI_I2S_IOCTL_STOP,
};

/** @struct i2s_config
 * @brief Interface configuration options.
 *
 * @param word_size Number of bits representing one data word.
 * @param channels Number of words per frame.
 * @param format Data stream format as defined by PI_I2S_FMT_* constants.
 * @param options Configuration options as defined by PI_I2S_OPT_* constants.
 * @param frame_clk_freq Frame clock (WS) frequency, this is sampling rate.
 * @param block_size Size of one RX/TX memory block (buffer) in bytes.

 */
struct pi_i2s_conf {
    uint16_t pdm_decimation_log2;
    uint8_t word_size;
    uint8_t channels;
    uint8_t itf;
    pi_i2s_fmt_t format;
    pi_i2s_opt_t options;
    uint32_t frame_clk_freq;
    size_t block_size;
    void *pingpong_buffers[2];
};

void pi_i2s_conf_init(struct pi_i2s_conf *conf);

int pi_i2s_open(struct pi_device *device);

void pi_i2s_close(struct pi_device *device);

int pi_i2s_ioctl(struct pi_device *device, uint32_t cmd, void *arg);

int pi_i2s_read(struct pi_device *dev, void **mem_block, size_t *size);

int pi_i2s_read_async(struct pi_device *dev, pi_task_t *task);

int pi_i2s_read_status(pi_task_t *task, void **mem_block, size_t *size);

int pi_i2s_write(struct pi_device *dev, void *mem_block, size_t size);





#endif
