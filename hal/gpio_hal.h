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
#ifndef OMNI_HAL_GPIO_H
#define OMNI_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal/gpio_types.h"

/**
 * @brief GPIO HAL context structure
 */
typedef struct gpio_hal_context {
    gpio_dev_t dev;
    gpio_num_t gpio_num;
    bool is_initiated;
} gpio_hal_context_t;

/**
 * @brief GPIO HAL APIs structure
 */
struct gpio_hal_api {
    int (*init)(gpio_hal_context_t *context);
    int (*deinit)(gpio_hal_context_t *context);
    int (*mode)(gpio_hal_context_t *context, gpio_mode_t mode);
    int (*alternate)(gpio_hal_context_t *context, uint32_t alternate);
    int (*pull)(gpio_hal_context_t *context, gpio_pull_t pull);
    int (*speed)(gpio_hal_context_t *context, gpio_speed_t speed);
    int (*write)(gpio_hal_context_t *context, uint32_t value);
    int (*read)(gpio_hal_context_t *context, uint32_t *value);
    int (*toggle)(gpio_hal_context_t *context);
};

extern const struct gpio_hal_api gpio_hal;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_GPIO_H */
