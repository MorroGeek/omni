/**
  * @file    gpio.c
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

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>

#include "drivers/gpio/gpio.h"
#include "drivers/assert.h"

#if defined(CONFIG_OMNI_DRIVERS_GPIO)

/**
 * @brief GPIO driver data
 */
typedef struct gpio_driver_data {
    bool is_initiated;
} gpio_driver_data_t;

/**
 * @brief GPIO object structure
 */
typedef struct {
    gpio_hal_context_t hal_context;
    gpio_driver_data_t driver_data;
} gpio_obj_t;

// static gpio_obj_t *p_gpio_obj[GPIO_NUM_MAX];

static gpio_obj_t p_gpio_obj;

static int gpio_open(gpio_num_t gpio_num, gpio_driver_config_t *config);
static int gpio_close(gpio_num_t gpio_num);
static int gpio_set_mode(gpio_num_t gpio_num, gpio_mode_t mode);
static int gpio_set_pull(gpio_num_t gpio_num, gpio_pull_t pull);
static int gpio_set_speed(gpio_num_t gpio_num, gpio_speed_t speed);
static int gpio_set_level(gpio_num_t gpio_num, uint32_t level);
static int gpio_get_level(gpio_num_t gpio_num, uint32_t *level);
static int gpio_toggle(gpio_num_t gpio_num);

struct gpio_driver_api gpio_driver = {
    .open = gpio_open,
    .close = gpio_close,
    .set_mode = gpio_set_mode,
    .set_pull = gpio_set_pull,
    .set_speed = gpio_set_speed,
    .set_level = gpio_set_level,
    .get_level = gpio_get_level,
    .toggle = gpio_toggle,
};

/**
 * @brief Open GPIO
 * 
 * @param gpio_num GPIO number
 * @param config Pointer to UART driver configuration structure
 * @return Operation status
 */
static int gpio_open(gpio_num_t gpio_num, gpio_driver_config_t *config) {
    int res;
    // p_gpio_obj[gpio_num] = (gpio_obj_t *)malloc(sizeof(gpio_obj_t));
    // uint32_t size = sizeof(gpio_obj_t);

    // gpio_hal.init(&p_gpio_obj[gpio_num]->driver_data.dev, gpio_num);

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.init(&p_gpio_obj.hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    res = gpio_hal.write(&p_gpio_obj.hal_context, config->level);
    if (res != OMNI_OK) {
        return res;
    }

    res = gpio_hal.speed(&p_gpio_obj.hal_context, config->speed);
    if (res != OMNI_OK) {
        return res;
    }

    res = gpio_hal.pull(&p_gpio_obj.hal_context, config->pull);
    if (res != OMNI_OK) {
        return res;
    }

    if (config->mode == GPIO_MODE_PP_AF || config->mode == GPIO_MODE_OD_AF) {
        res = gpio_hal.alternate(&p_gpio_obj.hal_context, config->alternate);
        if (res != OMNI_OK) {
            return res;
        }
    }

    res = gpio_hal.mode(&p_gpio_obj.hal_context, config->mode);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Close GPIO
 * 
 * @param gpio_num GPIO number
 * @return Operation status
 */
static int gpio_close(gpio_num_t gpio_num) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.deinit(&p_gpio_obj.hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO mode
 * 
 * @param gpio_num GPIO number
 * @param mode GPIO mode
 * @return Operation status
 */
static int gpio_set_mode(gpio_num_t gpio_num, gpio_mode_t mode) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.mode(&p_gpio_obj.hal_context, mode);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO pull
 * 
 * @param gpio_num GPIO number
 * @param pull GPIO pull
 * @return Operation status
 */
static int gpio_set_pull(gpio_num_t gpio_num, gpio_pull_t pull) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.pull(&p_gpio_obj.hal_context, pull);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO speed
 * 
 * @param gpio_num GPIO number
 * @param speed GPIO speed
 * @return Operation status
 */
static int gpio_set_speed(gpio_num_t gpio_num, gpio_speed_t speed) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.speed(&p_gpio_obj.hal_context, speed);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO level
 * 
 * @param gpio_num GPIO number
 * @param level GPIO level
 * @return Operation status
 */
static int gpio_set_level(gpio_num_t gpio_num, uint32_t level) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.write(&p_gpio_obj.hal_context, level);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Get GPIO level
 * 
 * @param gpio_num GPIO number
 * @param level Pointer to GPIO level
 * @return Operation status
 */
static int gpio_get_level(gpio_num_t gpio_num, uint32_t *level) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.read(&p_gpio_obj.hal_context, level);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Toggle GPIO level
 * 
 * @param gpio_num GPIO number
 * @return Operation status
 */
static int gpio_toggle(gpio_num_t gpio_num) {
    int res;

    p_gpio_obj.hal_context.gpio_num = gpio_num;

    res = gpio_hal.toggle(&p_gpio_obj.hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

#endif /* CONFIG_OMNI_DRIVERS_GPIO */
