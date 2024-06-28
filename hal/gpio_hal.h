/**
  * @file    gpio_hal.h
  * @author  MorroMaker
  * @brief   Header for gpio_hal.c file
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
#ifndef OMNI_GPIO_HAL_H
#define OMNI_GPIO_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "device.h"
#include "common.h"

/**
 * @brief GPIO output mode
 */
typedef enum {
    OMNI_GPIO_PP_PULLNONE = 0,
    OMNI_GPIO_PP_PULLUP = 1,
    OMNI_GPIO_PP_PULLDOWN = 2,
    OMNI_GPIO_OD_PULLNONE = 3,
    OMNI_GPIO_OD_PULLUP = 4,
    OMNI_GPIO_OD_PULLDOWN = 5,
    OMNI_GPIO_ANALOG = 6,
    OMNI_GPIO_AF_PP = 7,
    OMNI_GPIO_AF_OD = 8,
} gpio_mode_t;

/**
 * @brief GPIO pull
 */
typedef enum
{
    OMNI_GPIO_PULL_NONE = 0,
    OMNI_GPIO_PULL_UP = 1,
    OMNI_GPIO_PULL_DOWN = 2,
} gpio_pull_t;

/**
 * @brief GPIO output speed
 */
typedef enum {
    OMNI_GPIO_SPEED_LOW = 0,
    OMNI_GPIO_SPEED_MEDIUM = 1,
    OMNI_GPIO_SPEED_HIGH = 2,
    OMNI_GPIO_SPEED_VERYHIGH = 3,
} gpio_speed_t;

/**
 * @brief GPIO direction
 */
typedef enum {
    OMNI_GPIO_INPUT = 0,
    OMNI_GPIO_OUTPUT = 1,
    OMNI_GPIO_INOUT = 2,
} gpio_dir_t;

/**
 * @brief GPIO status
 */
typedef enum {
    OMNI_GPIO_LOW = 0,
    OMNI_GPIO_HIGH = 1,
} gpio_status_t;

/**
 * @brief GPIO inverted
 */
typedef enum {
    OMNI_GPIO_NONINVERTED = 0,
    OMNI_GPIO_INVERTED = 1,
} gpio_inverted_t;

/**
 * @brief GPIO driver APIs structure
 */
struct gpio_driver_api {
    int (*init)(gpio_t *obj, pin_map_t map);
    int (*mode)(gpio_t *obj, gpio_mode_t mode);
    int (*dir)(gpio_t *obj, gpio_dir_t dir);
    int (*speed)(gpio_t *obj, gpio_speed_t speed);
    int (*write)(gpio_t *obj, int value);
    int (*toggle)(gpio_t *obj);
    int (*read)(gpio_t *obj, uint32_t *value);
};

struct gpio_driver_api *gpio_driver(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_GPIO_HAL_H */
