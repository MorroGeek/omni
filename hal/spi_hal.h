/**
  * @file    spi_hal.h
  * @author  MorroMaker
  * @brief   Header for spi_hal.c file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_SPI_HAL_H
#define OMNI_SPI_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "device.h"
#include "common.h"

/**
 * @brief SPI mode
 */
typedef enum {
    OMNI_SPI_MODE_INVALID = 0,
    OMNI_SPI_MODE_FD_MASTER = 1,   // Full-duplex master
    OMNI_SPI_MODE_FD_SLAVE = 2,    // Full-duplex slave
} spi_mode_t;

/**
 * @brief SPI clock polarity
 */
typedef enum {
    OMNI_SPI_CPOL_LOW = 0U,
    OMNI_SPI_CPOL_HIGH = 1U,
} spi_clock_polarity_t;

/**
 * @brief SPI clock phase
 */
typedef enum {
    OMNI_SPI_CPHA_1EDGE = 0U,
    OMNI_SPI_CPHA_2EDGE = 1U,
} spi_clock_phase_t;

/**
 * @brief SPI first bit
 */
typedef enum {
    OMNI_SPI_FIRSTBIT_MSB = 0U,
    OMNI_SPI_FIRSTBIT_LSB = 1U,
} spi_first_bit_t;

/**
 * @brief SPI handle structure
 */
typedef struct {
    uint32_t mode;
    uint32_t freq_num;
    uint32_t clock_polarity;
    uint32_t clock_phase;
    uint32_t first_bit;
    struct spi_s spi;           // SPI object
    void (*init_callback)();    // SPI init callback
} spi_t;

/**
 * @brief SPI driver APIs structure
 */
struct spi_driver_api {
    int (*init)(spi_t *obj);
    int (*deinit)(spi_t *obj);
    int (*write)(spi_t *obj, uint8_t *data, uint16_t size, uint32_t timeout);
    int (*read)(spi_t *obj, uint8_t *data, uint16_t size, uint32_t timeout);
    int (*transfer)(spi_t *obj, uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout);
};

struct spi_driver_api *spi_driver(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_SPI_HAL_H */