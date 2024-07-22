/**
  * @file    device.h
  * @author  MorroMaker
  * @brief   Device header file
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
#ifndef OMNI_HAL_DEVICE_H
#define OMNI_HAL_DEVICE_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>

#include "omni_board.h"
#include "omni_config.h"

/* OMNI status */
#define OMNI_OK 0
#define OMNI_FAIL -1

/**
 * @brief Runtime device state structure for device instance
 */
struct device_state {
    uint8_t init_result;            // Device initialization result
    bool is_initialized : 1;        // Device initialization status
};

/**
 * @brief Runtime device structure for device instance
 */
struct device {
    struct device_state *state;     // Address of device instance state information
    const char *name;               // Name of the device instance
    const void *config;             // Address of device instance config information
    const void *api;                // Address of device instance API
    void *data;                     // Address of device instance private data
};

/**
 * @brief Pin map structure
 */
typedef struct {
    pin_name_t pin;
    uint32_t peripheral;
    union {
        struct {
            uint32_t mode       : 4;
            uint32_t dir        : 2;
            uint32_t speed      : 2;
            uint32_t alternate  : 4;
            uint32_t channel    : 5;
            uint32_t inverted   : 1;
            uint32_t status     : 1;
            uint32_t reserved   : 13;
        } feature;

        uint32_t _feature;
    };
} pin_map_t;

/**
 * @brief Buffer structure
 */
typedef struct {
    void *buffer;    /**< Pointer to the buffer */
    size_t size;     /**< Size of the buffer */
    size_t pos;      /**< Actual position in the buffer */
    uint8_t width;   /**< The buffer unit width (8, 16, 32, 64 bits) */
} buffer_t;

#endif /* OMNI_HAL_DEVICE_H */
