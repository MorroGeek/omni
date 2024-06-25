/**
  * @file    spi_hal.c
  * @author  MorroMaker
  * @brief   SPI HAL for STM32F4
  * @attention
  *
  * Copyright (c) 2024 MorroMaker
  * All rights reserved.
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

/* Includes ------------------------------------------------------------------*/
#include "spi_hal.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define GET_OBJ_HANDLE(obj) ((SPI_HandleTypeDef *)obj->spi.handle)

/* Private variables ---------------------------------------------------------*/

// Baudrate prescaler table
static const uint32_t baudrate_prescaler_table[] = {
    SPI_BAUDRATEPRESCALER_2,
    SPI_BAUDRATEPRESCALER_4,
    SPI_BAUDRATEPRESCALER_8,
    SPI_BAUDRATEPRESCALER_16,
    SPI_BAUDRATEPRESCALER_32,
    SPI_BAUDRATEPRESCALER_64,
    SPI_BAUDRATEPRESCALER_128,
    SPI_BAUDRATEPRESCALER_256,
};

/* Private function prototypes -----------------------------------------------*/
static int spi_init(spi_t *obj);
static int spi_deinit(spi_t *obj);
static int spi_write(spi_t *obj, uint8_t *data, uint16_t size, uint32_t timeout);
static int spi_read(spi_t *obj, uint8_t *data, uint16_t size, uint32_t timeout);
static int spi_transfer(spi_t *obj, uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout);

/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/

static struct spi_driver_api spi_stm32_driver = {
    .init = spi_init,
    .deinit = spi_deinit,
    .write = spi_write,
    .read = spi_read,
    .transfer = spi_transfer,
};

struct spi_driver_api *spi_driver(void)
{
    return &spi_stm32_driver;
}

/**
 * @brief Initialize the SPI bus
 * @param obj SPI handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int spi_init(spi_t *obj)
{
    SPI_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    switch (obj->mode) {
        case OMNI_SPI_MODE_FD_MASTER:
            handle->Init.Mode = SPI_MODE_MASTER;
            break;

        case OMNI_SPI_MODE_FD_SLAVE:
            handle->Init.Mode = SPI_MODE_SLAVE;
            break;

        default:
            return OMNI_FAIL;
    }

    // Set SPI bus frequency
    handle->Init.BaudRatePrescaler = baudrate_prescaler_table[obj->freq_num];

    handle->Init.Direction = SPI_DIRECTION_2LINES;
    handle->Init.DataSize = SPI_DATASIZE_8BIT;
    handle->Init.NSS = SPI_NSS_SOFT;
    handle->Init.TIMode = SPI_TIMODE_DISABLE;
    handle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    handle->Init.CRCPolynomial = 10;

    switch (obj->clock_phase) {
        case OMNI_SPI_CPHA_1EDGE:
            handle->Init.CLKPhase = SPI_PHASE_1EDGE;
            break;

        case OMNI_SPI_CPHA_2EDGE:
            handle->Init.CLKPhase = SPI_PHASE_2EDGE;
            break;

        default:
            break;
    }

    switch (obj->clock_polarity) {
        case OMNI_SPI_CPOL_LOW:
            handle->Init.CLKPolarity = SPI_POLARITY_LOW;
            break;

        case OMNI_SPI_CPOL_HIGH:
            handle->Init.CLKPolarity = SPI_POLARITY_HIGH;
            break;

        default:
            break;
    }

    switch (obj->first_bit) {
        case OMNI_SPI_FIRSTBIT_MSB:
            handle->Init.FirstBit = SPI_FIRSTBIT_MSB;
            break;

        case OMNI_SPI_FIRSTBIT_LSB:
            handle->Init.FirstBit = SPI_FIRSTBIT_LSB;
            break;

        default:
            break;
    }

    if (HAL_SPI_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Deinitialize the SPI bus
 * @param obj SPI handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int spi_deinit(spi_t *obj)
{
    SPI_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    if (HAL_SPI_DeInit(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Write data to the SPI bus
 * @param obj SPI handle structure
 * @param data Data buffer
 * @param size Data size
 * @param timeout Timeout
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int spi_write(spi_t *obj, uint8_t *data, uint16_t size, uint32_t timeout)
{
    SPI_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    if (HAL_SPI_Transmit(handle, data, size, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Read data from the SPI bus
 * @param obj SPI handle structure
 * @param data Data buffer
 * @param size Data size
 * @param timeout Timeout
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int spi_read(spi_t *obj, uint8_t *data, uint16_t size, uint32_t timeout)
{
    SPI_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    if (HAL_SPI_Receive(handle, data, size, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Transfer data to and from the SPI bus
 * @param obj SPI handle structure
 * @param txData Data buffer to write
 * @param rxData Data buffer to read
 * @param size Data size
 * @param timeout Timeout
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int spi_transfer(spi_t *obj, uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout)
{
    SPI_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    if (HAL_SPI_TransmitReceive(handle, txData, rxData, size, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/* Private functions ---------------------------------------------------------*/
