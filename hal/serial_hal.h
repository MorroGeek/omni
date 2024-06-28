/**
  * @file    serial_hal.h
  * @author  MorroMaker
  * @brief   Header for serial_hal.c file
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
#ifndef OMNI_SERIAL_HAL_H
#define OMNI_SERIAL_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "device.h"
#include "common.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/

/**
 * @brief Serial mode
 */
typedef enum {
    OMNI_SERIAL_MODE_INVALID = 0U,
    OMNI_SERIAL_MODE_BASE = 1U,
} serial_mode_t;

/**
 * @brief Serial word length
 */
typedef enum {
    OMNI_SERIAL_WORDLENGTH_8B = 0U,
    OMNI_SERIAL_WORDLENGTH_9B = 1U,
} serial_word_length_t;

/**
 * @brief Serial stop bits
 */
typedef enum {
    OMNI_SERIAL_STOPBITS_1 = 0U,
    OMNI_SERIAL_STOPBITS_2 = 1U,
} serial_stop_bits_t;

/**
 * @brief Serial parity
 */
typedef enum {
    OMNI_SERIAL_PARITY_NONE = 0U,
    OMNI_SERIAL_PARITY_EVEN = 1U,
    OMNI_SERIAL_PARITY_ODD = 2U,
} serial_parity_t;

/**
 * @brief Serial handle structure
 */
typedef struct {
    uint32_t mode;
    uint32_t baud_rate;
    uint32_t data_bits;
    uint32_t stop_bits;
    uint32_t parity;
    struct serial_s serial;     // Serial object
    void (*init_callback)();    // Serial init callback
} serial_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief Serial driver APIs structure
 */
struct serial_driver_api {
    int (*init)(serial_t *obj);
    int (*deinit)(serial_t *obj);
    int (*write)(serial_t *obj, uint8_t *data, uint32_t size, uint32_t timeout);
    int (*read)(serial_t *obj, uint8_t *data, uint32_t size, uint32_t timeout);
};

struct serial_driver_api *serial_driver(void);

#ifdef __cplusplus
}
#endif

#endif /* OMNI_SERIAL_HAL_H */