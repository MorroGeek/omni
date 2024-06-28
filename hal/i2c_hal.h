/**
  * @file    i2c_hal.h
  * @author  MorroMaker
  * @brief   Header for i2c_hal.c file
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
#ifndef OMNI_I2C_HAL_H
#define OMNI_I2C_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "device.h"
#include "common.h"

/**
 * @brief I2C mode
 */
typedef enum {
    OMNI_I2C_MODE_INVALID = 0U,
    OMNI_I2C_MODE_MASTER = 1U,
    OMNI_I2C_MODE_SLAVE = 2U,
} i2c_mode_t;

/**
 * @brief I2C handle structure
 */
typedef struct {
    uint32_t mode;
    uint32_t frequency;
    uint32_t address1;
    uint32_t address2;
    struct i2c_s i2c;           // I2C object
    void (*init_callback)();    // I2C init callback
} i2c_t;

/**
 * @brief  I2C driver APIs structure
 */
struct i2c_driver_api {
    int (*init)(i2c_t *obj);
    int (*deinit)(i2c_t *obj);
    int (*write)(i2c_t *obj, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout);
    int (*read)(i2c_t *obj, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout);
    int (*listen)(i2c_t *obj);
    int (*listen_stop)(i2c_t *obj);
};

struct i2c_driver_api *i2c_driver(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_I2C_HAL_H */