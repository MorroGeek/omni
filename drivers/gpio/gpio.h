/**
  * @file    gpio.h
  * @author  MorroMaker
  * @brief   GPIO driver for omni
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
#ifndef OMNI_DRIVERS_GPIO_H
#define OMNI_DRIVERS_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "hal/gpio_hal.h"

#if defined(CONFIG_OMNI_DRIVERS_GPIO)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief GPIO driver configuration
 */
typedef struct gpio_driver_config {
    gpio_mode_t mode;       /**< GPIO mode */
    gpio_pull_t pull;       /**< GPIO pull */
    uint32_t alternate;     /**< GPIO alternate */
    gpio_speed_t speed;     /**< GPIO speed */
    gpio_level_t level;     /**< GPIO level */
} gpio_driver_config_t;

/**
 * @brief Callback function upon initialing GPIO
 */
typedef int (*gpio_init_t)(gpio_num_t gpio_num, gpio_driver_config_t *config);

/**
 * @brief Callback function upon deinitialing GPIO
 */
typedef int (*gpio_deinit_t)(gpio_num_t gpio_num);

/**
 * @brief Callback function upon setting GPIO mode
 */
typedef int (*gpio_set_mode_t)(gpio_num_t gpio_num, gpio_mode_t mode);

/**
 * @brief Callback function upon setting GPIO pull
 */
typedef int (*gpio_set_pull_t)(gpio_num_t gpio_num, gpio_pull_t pull);

/**
 * @brief Callback function upon setting GPIO speed
 */
typedef int (*gpio_set_speed_t)(gpio_num_t gpio_num, gpio_speed_t speed);

/**
 * @brief Callback function upon setting GPIO level
 */
typedef int (*gpio_set_level_t)(gpio_num_t gpio_num, uint32_t level);

/**
 * @brief Callback function upon getting GPIO level
 */
typedef int (*gpio_get_level_t)(gpio_num_t gpio_num, uint32_t *level);

/**
 * @brief Callback function upon toggling GPIO level
 */
typedef int (*gpio_toggle_t)(gpio_num_t gpio_num);

/**
 * @brief GPIO driver API
 */
struct gpio_driver_api {
    gpio_init_t init;
    gpio_deinit_t deinit;
    gpio_set_mode_t set_mode;
    gpio_set_pull_t set_pull;
    gpio_set_speed_t set_speed;
    gpio_set_level_t set_level;
    gpio_get_level_t get_level;
    gpio_toggle_t toggle;
};

extern struct gpio_driver_api gpio_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONFIG_OMNI_DRIVERS_GPIO */

#endif /* OMNI_DRIVERS_GPIO_H */
