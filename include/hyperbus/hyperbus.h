/*
 * Copyright (c) 2019, GreenWaves Technologies, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of GreenWaves Technologies, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _PMSIS_HYPERBUS_H_
#define _PMSIS_HYPERBUS_H_

#include "pmsis.h"
#include "udma_core.h"
#include "udma_ctrl.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Type of device connected to the hyperbus interface. */
typedef enum
{
    PI_HYPER_TYPE_FLASH,  /*!< Device is a flash. */
    PI_HYPER_TYPE_RAM     /*!< Device is a RAM. */
} pi_hyper_type_e;

/* Hyperbus configuration structure. */
struct pi_hyper_conf
{
    pi_device_e device;   /*!< Device type. */
    uint32_t cs;          /*!< Chip select where the device is connected. */
    pi_hyper_type_e type; /*!< Device to use, ram of flash. */
    int8_t id;            /*!< Hyperbus device ID. */
    int32_t ram_size;     /*!< Size of the ram. */
};


struct hyper_transfer_s
{
    uint32_t hyper_addr;
    void *buffer;
    uint32_t size;
    uint32_t stride;
    uint32_t length;
    udma_channel_e channel;
    int8_t device_id;
};

struct hyper_cb_args_s
{
    struct pi_task *cb;
    struct hyper_transfer_s transfer;
};

#if (FEATURE_CLUSTER == 1)
struct pi_cl_hyper_req_s
{
    struct pi_device *device;
    struct hyper_transfer_s transfer;
    struct pi_cl_hyper_req_s *next;
    pi_task_t task_done;
    uint8_t cid;
    uint8_t is_2d;
};

struct pi_cl_hyper_alloc_req_s
{
    struct pi_device *device;
    uint32_t result;
    uint32_t size;
    pi_task_t task_done;
    uint8_t cid;
};

struct pi_cl_hyper_free_req_s
{
    struct pi_device *device;
    uint32_t result;
    uint32_t size;
    uint32_t chunk;
    pi_task_t task_done;
    uint8_t cid;
};
#endif  /* (FEATURE_CLUSTER == 1) */

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Initialize an Hyperbus configuration with default values.
 *
 * The structure containing the configuration must be kept alive until the hyper is opened.
 *
 * @param conf A pointer to the Hyperbus configuration.
 */
void pi_hyper_conf_init(struct pi_hyper_conf *conf);

/*!
 * @brief Open an Hyperbus device.
 *
 * This function must be called before the Hyperbus device can be used.
 * It will do all the needed configuration to make it usable and also return
 * a handle used to refer to this opened device when calling other functions.
 * This operation is asynchronous and its termination can be managed through an event.
 *
 * @param device         The device structure of the device to open.
 *
 * @return               0 if the operation is successfull, -1 if there was an error.
 */
int32_t pi_hyper_open(struct pi_device *device);

/*!
 * @brief Close an opened Hyperbus device.
 *
 * This function can be called to close an opened Hyperbus device once it is not
 * needed anymore, in order to free all allocated resources.
 * Once this function is called, the device is not accessible anymore and
 * must be opened again before being used.
 * This operation is asynchronous and its termination can be managed through an event.
 *
 * @param device         The device structure of the device to close.
 */
void pi_hyper_close(struct pi_device *device);

/*!
 * @brief Enqueue a read copy to the Hyperbus (from Hyperbus to processor).
 *
 * This function will make a synchronous transfer between the Hyperbus and L2 memory.
 * The caller is blocked until the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 */
void pi_hyper_read(struct pi_device *device, uint32_t hyper_addr,
                   void *buffer, uint32_t size);

/*
 * @brief Enqueue an asynchronous read copy to the Hyperbus (from Hyperbus to processor).
 *
 * This function will make an asynchronous transfer between the Hyperbus and L2 memory.
 * It returns once the transfer is enqueued. A task can be specified in order
 * to be notified when the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param task           The task used to notify the end of transfer.
 *                       See the documentation of pi_task for more details.
 */
void pi_hyper_read_async(struct pi_device *device, uint32_t hyper_addr,
                         void *buffer, uint32_t size, struct pi_task *callback);

/*!
 * @brief Enqueue a write copy to the Hyperbus (from processor to Hyperbus).
 *
 * This function will make a synchronous transfer between the Hyperbus and L2 memory.
 * The calller is blocked until the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 */
void pi_hyper_write(struct pi_device *device, uint32_t hyper_addr,
                    void *buffer, uint32_t size);

/*
 * @brief Enqueue an asynchronous write copy to the Hyperbus (from processor to Hyperbus).
 *
 * This function will make an asynchronous transfer between the Hyperbus and L2 memory.
 * It returns once the transfer is enqueued. A task can be specified in order
 * to be notified when the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param task           The task used to notify the end of transfer.
 *                       See the documentation of pi_task for more details.
 */
void pi_hyper_write_async(struct pi_device *device, uint32_t hyper_addr,
                          void *buffer, uint32_t size, struct pi_task *callback);

/*!
 * @brief Enqueue a 2D read copy (rectangle area) to the Hyperbus (from Hyperbus to processor).
 *
 * This function copy will make a synchronous transfer between the Hyperbus and L2 memory.
 * The caller is blocked until the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip on which to do the copy.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param stride         2D stride(number of bytes added to the beginning
 *                       of the current line to switch to the next one).
 * @param length         2D length(number of transfered bytes after which
 *                       the driver will switch to the next line).
 */
void pi_hyper_read_2d(struct pi_device *device, uint32_t hyper_addr,
                      void *buffer, uint32_t size,
                      uint32_t stride, uint32_t length);

/*!
 * @brief Enqueue an asynchronous 2D read copy (rectangle area)
 * to the Hyperbus (from Hyperbus to processor).
 *
 * This function will make an asynchronous transfer between the Hyperbus and L2 memory.
 * It returns once the transfer is enqueued. A task can be specified in order
 * to be notified when the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param stride         2D stride(number of bytes added to the beginning
 *                       of the current line to switch to the next one).
 * @param length         2D length(number of transfered bytes after which
 *                       the driver will switch to the next line).
 * @param task           The task used to notify the end of transfer.
 *                       See the documentation of pi_task for more details.
 */
void pi_hyper_read_2d_async(struct pi_device *device, uint32_t hyper_addr,
                            void *addr, uint32_t size,
                            uint32_t stride, uint32_t length, struct pi_task *task);

/*!
 * @brief Enqueue a 2D write copy (rectangle area) to the Hyperbus (from processor to Hyperbus).
 *
 * This function will make a synchronous transfer between the Hyperbus and L2 memory.
 * The caller is blocked until the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memeory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param stride         2D stride(number of bytes added to the beginning
 *                       of the current line to switch to the next one).
 * @param length         2D length(number of transfered bytes after which
 *                       the driver will switch to the next line).
 */
void pi_hyper_write_2d(struct pi_device *device, uint32_t hyper_addr,
                       void *addr, uint32_t size,
                       uint32_t stride, uint32_t length);

/*!
 * @brief Enqueue an asynchronous 2D write copy (rectangle area)
 * to the Hyperbus (from processor to Hyperbus).
 *
 * This function will make an asynchronous transfer between the Hyperbus and L2 memory.
 * It returns once the transfer is enqueued. A task can be specified in order
 * to be notified when the transfer is finished.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param stride         2D stride(number of bytes added to the beginning
 *                       of the current line to switch to the next one).
 * @param length         2D length(number of transfered bytes after which
 *                       the driver will switch to the next line).
 * @param task           The task used to notify the end of transfer.
 *                       See the documentation of pi_task for more details.
 */
void pi_hyper_write_2d_async(struct pi_device *device, uint32_t hyper_addr,
                             void *addr, uint32_t size,
                             uint32_t stride, uint32_t length, struct pi_task *task);

/*!
 * @brief Allocate Hyperram memory
 *
 * The allocated memory is 4-bytes aligned.
 * The allocator uses some meta-data stored in the fabric controller memory for
 * every allocation so it is advisable to do as few allocations as possible to
 * lower the memory overhead.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param size           The size in bytes of the memory to allocate.
 *
 * @return NULL if not enough memory was available, otherwise the address of the allocated chunk.
 */
uint32_t pi_hyperram_alloc(struct pi_device *device, uint32_t size);

/*!
 * @brief Free Hyperram memory
 *
 * The allocator does not store any information about the allocated chunks,
 * thus the size of the allocated chunk to be freed must be provided by the caller.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param chunk          The allocated chunk to free.
 * @param size           The size in bytes of the memory chunk which was allocated.
 *
 * @return 0 if the operation was successful, -1 otherwise.
 */
int32_t pi_hyperram_free(struct pi_device *device, uint32_t chunk, uint32_t size);


#if (FEATURE_CLUSTER == 1)

typedef struct pi_cl_hyper_req_s pi_cl_hyper_req_t;

typedef struct pi_cl_hyper_alloc_req_s pi_cl_hyper_alloc_req_t;

typedef struct pi_cl_hyper_free_req_s pi_cl_hyper_free_req_t;

/*!
 * @brief Enqueue a read copy to the Hyperbus from cluster side (from Hyperbus to processor).
 *
 * This function is a remote call that the cluster can do to the fabric-controller
 * in order to ask for an HyperBus read copy.
 * The copy will make an asynchronous transfer between the Hyperbus and one of
 * the processor memory areas.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * @note This function can only be called from the cluster.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param req            A pointer to the Hyperbus request structure. It must be
 *                       allocated by the caller and kept alive until the copy is finished.
 */
void pi_cl_hyper_read(struct pi_device *device, uint32_t hyper_addr,
                      void *buffer, uint32_t size, pi_cl_hyper_req_t *req);

/*!
 * @brief Enqueue a 2D read copy (rectangle area) to the Hyperbus from cluster side (from Hyperbus to processor).
 *
 * This function is a remote call that the cluster can do to the fabric-controller
 * in order to ask for an HyperBus read copy.
 * The copy will make an asynchronous transfer between the Hyperbus and one of
 * the processor memory areas.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * @note This function can only be called from the cluster.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param stride         2D stride(number of bytes added to the beginning
 *                       of the current line to switch to the next one).
 * @param length         2D length(number of transfered bytes after which
 *                       the driver will switch to the next line).
 * @param req            A pointer to the Hyperbus request structure. It must be
 *                       allocated by the caller and kept alive until the copy is finished.
 */
void pi_cl_hyper_read_2d(struct pi_device *device, uint32_t hyper_addr,
                         void *buffer, uint32_t size,
                         uint32_t stride, uint32_t length, pi_cl_hyper_req_t *req);

/*!
 * @brief Wait until the specified hyperbus request has finished.
 *
 * This function blocks the calling core until the specified request is finished.
 *
 * @param req            A pointer to the Hyperbus request structure.
 */
void pi_cl_hyper_read_wait(pi_cl_hyper_req_t *req);

/*!
 * @brief Enqueue a write copy to the Hyperbus from cluster side (from Hyperbus to processor).
 *
 * This function is a remote call that the cluster can do to the fabric-controller
 * in order to ask for an HyperBus write copy.
 * The copy will make an asynchronous transfer between the Hyperbus and one of
 * the processor memory areas.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * @note This function can only be called from the cluster.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param buffer         The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param req            A pointer to the Hyperbus request structure. It must be
 *                       allocated by the caller and kept alive until the copy is finished.
 */
void pi_cl_hyper_write(struct pi_device *device, uint32_t hyper_addr,
                       void *buffer, uint32_t size, pi_cl_hyper_req_t *req);

/*!
 * @brief Enqueue a 2D write copy (rectangle area) to the Hyperbus from cluster side (from Hyperbus to processor).
 *
 * This function is a remote call that the cluster can do to the fabric-controller
 * in order to ask for an HyperBus write copy.
 * The copy will make an asynchronous transfer between the Hyperbus and one of
 * the processor memory areas.
 * A pointer to a request structure must be provided so that the runtime can
 * properly do the remote call.
 *
 * @note This function can only be called from the cluster.
 *
 * @param device         The device descriptor of the Hyperbus chip.
 * @param hyper_addr     The address of the buffer in the Hyperbus.
 * @param addr           The address of the L2 memory buffer.
 * @param size           The size in bytes of the buffer to copy.
 * @param stride         2D stride(number of bytes are added to the beginning
 *                       of the current line to switch to the next one).
 * @param length         2D length(number of transfered bytes after which
 *                       the driver will switch to the next line).
 * @param req            A pointer to the HyperBus request structure. It must be
 *                       allocated by the caller and kept alive until the copy is finished.
 */
void pi_cl_hyper_write_2d(struct pi_device *device, uint32_t hyper_addr,
                          void *buffer, uint32_t size,
                          uint32_t stride, uint32_t length, pi_cl_hyper_req_t *req);

/*!
 * @brief Wait until the specified hyperbus request has finished.
 *
 * This function blocks the calling core until the request is finished.
 *
 * @param req            A pointer to the Hyperbus request structure.
 */
void pi_cl_hyper_write_wait(pi_cl_hyper_req_t *req);

/** \brief Enqueue a copy with the Hyperbus from cluster side.
 *
 * This function is a remote call that the cluster can do to the fabric-controller in order to ask
 * for an HyperBus copy.
 * The copy will make an asynchronous transfer between the Hyperbus and one of the processor memory areas.
 * A pointer to a request structure must be provided so that the runtime can properly do the remote call.
 * Can only be called from cluster side.
 *
 * \param device      The device descriptor of the Hyperbus chip on which to do the copy.
 * \param hyper_addr  The address of the copy in the Hyperbus.
 * \param addr        The address of the copy in the processor.
 * \param size        The size in bytes of the copy
 * \param ext2loc     1 if the copy is from HyperBus to the chip or 0 for the contrary.
 * \param req         A pointer to the HyperBus request structure. It must be allocated by the caller and kept alive until the copy is finished.
 */
void pi_cl_hyper_copy(struct pi_device *device, uint32_t hyper_addr,
                      void *addr, uint32_t size, int ext2loc, pi_cl_hyper_req_t *req);

/** \brief Enqueue a 2D copy (rectangle area) with the Hyperbus from cluster side.
 *
 * This function is a remote call that the cluster can do to the fabric-controller in order to ask
 * for an HyperBus copy.
 * The copy will make an asynchronous transfer between the Hyperbus and one of the processor memory areas.
 * A pointer to a request structure must be provided so that the runtime can properly do the remote call.
 * Can only be called from cluster side.
 *
 * \param device      The device descriptor of the Hyperbus chip on which to do the copy.
 * \param hyper_addr  The address of the copy in the Hyperbus.
 * \param addr        The address of the copy in the processor.
 * \param size        The size in bytes of the copy
 * \param stride      2D stride, which is the number of bytes which are added to the beginning of the current line to switch to the next one.
 * \param length      2D length, which is the number of transfered bytes after which the driver will switch to the next line.
 * \param ext2loc     1 if the copy is from HyperBus to the chip or 0 for the contrary.
 * \param req         A pointer to the HyperBus request structure. It must be allocated by the caller and kept alive until the copy is finished.
 */
void pi_cl_hyper_copy_2d(struct pi_device *device, uint32_t hyper_addr,
                         void *addr, uint32_t size,
                         uint32_t stride, uint32_t length, int ext2loc, pi_cl_hyper_req_t *req);

/** \brief Allocate Hyperram memory from cluster
 *
 * The allocated memory is 4-bytes aligned. The allocator uses some meta-data stored in the fabric controller memory
 * for every allocation so it is advisable to do as few allocations as possible to lower the memory overhead.
 *
 * \param device The device descriptor of the Hyperbus chip for which the memory must be allocated
 * \param size   The size in bytes of the memory to allocate
 * \param req    The request structure used for termination.
 */
void pi_cl_hyperram_alloc(struct pi_device *device, uint32_t size, pi_cl_hyper_alloc_req_t *req);

/** \brief Free Hyperram memory from cluster
 *
 * The allocator does not store any information about the allocated chunks, thus the size of the allocated
 * chunk to to be freed must be provided by the caller.
 * Can only be called from fabric-controller side.
 *
 * \param device The device descriptor of the Hyperbus chip for which the memory must be freed
 * \param chunk  The allocated chunk to free
 * \param size   The size in bytes of the memory chunk which was allocated
 * \param req    The request structure used for termination.
 */
void pi_cl_hyperram_free(struct pi_device *device, uint32_t chunk, uint32_t size, pi_cl_hyper_free_req_t *req);

/** \brief Wait until the specified hyperram alloc request has finished.
 *
 * This blocks the calling core until the specified cluster hyperbus allocation is finished.
 *
 * \param req       The request structure used for termination.
 * \return NULL     if not enough memory was available, otherwise the address of the allocated chunk
 */
uint32_t pi_cl_hyperram_alloc_wait(pi_cl_hyper_alloc_req_t *req);

/** \brief Wait until the specified hyperbus free request has finished.
 *
 * This blocks the calling core until the specified cluster hyperbus free is finished.
 *
 * \param req       The request structure used for termination.
 * \return 0        if the operation was successful, -1 otherwise
 */
void pi_cl_hyperram_free_wait(pi_cl_hyper_free_req_t *req);
#endif  /* (FEATURE_CLUSTER == 1) */

#endif  /* _PMSIS_HYPERBUS_H_ */
