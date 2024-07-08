/**
  * @file    gpio.c
  * @author  MorroMaker
  * @brief   GPIO driver for STM32F4
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
#include "hal/gpio_hal.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

// Low level pin number
static const uint32_t ll_pin[] = {
    LL_GPIO_PIN_0,
    LL_GPIO_PIN_1,
    LL_GPIO_PIN_2,
    LL_GPIO_PIN_3,
    LL_GPIO_PIN_4,
    LL_GPIO_PIN_5,
    LL_GPIO_PIN_6,
    LL_GPIO_PIN_7,
    LL_GPIO_PIN_8,
    LL_GPIO_PIN_9,
    LL_GPIO_PIN_10,
    LL_GPIO_PIN_11,
    LL_GPIO_PIN_12,
    LL_GPIO_PIN_13,
    LL_GPIO_PIN_14,
    LL_GPIO_PIN_15,
};
/* Private function prototypes -----------------------------------------------*/
static void set_gpio_clock(pin_name_t pin);
static GPIO_TypeDef *get_gpio_port(pin_name_t pin);
static uint32_t get_gpio_pin(pin_name_t pin);

static int gpio_init(gpio_t *obj, pin_map_t map);
static int gpio_mode(gpio_t *obj, gpio_mode_t mode);
static int gpio_dir(gpio_t *obj, gpio_dir_t dir);
static int gpio_speed(gpio_t *obj, gpio_speed_t speed);
static int gpio_write(gpio_t *obj, int value);
static int gpio_toggle(gpio_t *obj);
static int gpio_read(gpio_t *obj, uint32_t *value);

/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/

static struct gpio_driver_api gpio_stm32_driver = {
    .init = gpio_init,
    .mode = gpio_mode,
    .dir = gpio_dir,
    .speed = gpio_speed,
    .write = gpio_write,
    .toggle = gpio_toggle,
    .read = gpio_read,
};

struct gpio_driver_api *gpio_driver(void) {
    return &gpio_stm32_driver;
}

/**
 * @brief Initialize the GPIO
 * @param obj: GPIO handle structure
 * @param map: GPIO pin map
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_init(gpio_t *obj, pin_map_t map) {
    int res;

    if (map.pin == NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    obj->ins = get_gpio_port(map.pin);

    // Get GPIO pin
    obj->pin = get_gpio_pin(map.pin);

    // Enable GPIO clock
    set_gpio_clock(map.pin);

    // Set GPIO initial value
    res = gpio_write(obj, map.feature.status);
    if (res != OMNI_OK) {
        return res;
    }

    // GPIO configuration
    res = gpio_speed(obj, map.feature.speed);
    if (res != OMNI_OK) {
        return res;
    }

    res = gpio_dir(obj, map.feature.dir);
    if (res != OMNI_OK) {
        return res;
    }

    res = gpio_mode(obj, map.feature.mode);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO mode
 * @param obj: GPIO handle structure
 * @param mode: GPIO mode
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_mode(gpio_t *obj, gpio_mode_t mode) {
    // Set GPIO output type
    if ((mode == OMNI_GPIO_PP_PULLNONE) || (mode == OMNI_GPIO_PP_PULLUP) || (mode == OMNI_GPIO_PP_PULLDOWN)) {
        LL_GPIO_SetPinOutputType(obj->ins, obj->pin, LL_GPIO_OUTPUT_PUSHPULL);
    } else {
        LL_GPIO_SetPinOutputType(obj->ins, obj->pin, LL_GPIO_OUTPUT_OPENDRAIN);
    }

    // Set GPIO pull
    if ((mode == OMNI_GPIO_PP_PULLUP) || (mode == OMNI_GPIO_OD_PULLUP)) {
        LL_GPIO_SetPinPull(obj->ins, obj->pin, LL_GPIO_PULL_UP);
    } else if ((mode == OMNI_GPIO_PP_PULLDOWN) || (mode == OMNI_GPIO_OD_PULLDOWN)) {
        LL_GPIO_SetPinPull(obj->ins, obj->pin, LL_GPIO_PULL_DOWN);
    } else {
        LL_GPIO_SetPinPull(obj->ins, obj->pin, LL_GPIO_PULL_NO);
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO direction
 * @param obj: GPIO handle structure
 * @param dir: GPIO direction
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_dir(gpio_t *obj, gpio_dir_t dir) {
    // Set GPIO direction
    if (dir == OMNI_GPIO_INPUT) {
        LL_GPIO_SetPinMode(obj->ins, obj->pin, LL_GPIO_MODE_INPUT);
    } else {
        LL_GPIO_SetPinMode(obj->ins, obj->pin, LL_GPIO_MODE_OUTPUT);
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO speed
 * @param obj: GPIO handle structure
 * @param speed: GPIO speed
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_speed(gpio_t *obj, gpio_speed_t speed) {
    LL_GPIO_SetPinSpeed(obj->ins, obj->pin, speed);

    return OMNI_OK;
}

/**
 * @brief Set GPIO value
 * @param obj: GPIO handle structure
 * @param value: GPIO value
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_write(gpio_t *obj, int value) {
    if (value) {
        LL_GPIO_SetOutputPin(obj->ins, obj->pin);
    } else {
        LL_GPIO_ResetOutputPin(obj->ins, obj->pin);
    }

    return OMNI_OK;
}

/**
 * @brief Toggle GPIO value
 * @param obj: GPIO handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_toggle(gpio_t *obj) {
    LL_GPIO_TogglePin(obj->ins, obj->pin);

    return OMNI_OK;
}

/**
 * @brief Get GPIO value
 * @param obj: GPIO handle structure
 * @param value: GPIO value
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int gpio_read(gpio_t *obj, uint32_t *value) {
    *value = LL_GPIO_IsInputPinSet(obj->ins, obj->pin);

    return OMNI_OK;
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Get GPIO pin
 * @param pin: GPIO pin
 * @return GPIO pin
 */
static uint32_t get_gpio_pin(pin_name_t pin) {
    return ll_pin[pin & 0x0F];
}

/**
 * @brief Get GPIO port
 * @param pin: GPIO pin
 * @return GPIO port
 */
static GPIO_TypeDef *get_gpio_port(pin_name_t pin) {
    switch (pin & 0xF0U) {
        case PORTA:
            return GPIOA;

        case PORTB:
            return GPIOB;

        case PORTC:
            return GPIOC;

#if defined(GPIOD)
        case PORTD:
            return GPIOD;
#endif /* GPIOD */

#if defined(GPIOE)
        case PORTE:
            return GPIOE;
#endif /* GPIOE */

#if defined(GPIOF)
        case PORTF:
            return GPIOF;
#endif /* GPIOF */

#if defined(GPIOG)
        case PORTG:
            return GPIOG;
#endif /* GPIOG */

#if defined(GPIOH)
        case PORTH:
            return GPIOH;
#endif /* GPIOH */

#if defined(GPIOI)
        case PORTI:
            return GPIOI;
#endif /* GPIOI */

#if defined(GPIOJ)
            case PORTJ:
            return GPIOJ;
#endif /* GPIOJ */

#if defined(GPIOK)
            case PORTK:
            return GPIOK;
#endif /* GPIOK */

        default:
            return 0;
    }
}

/**
 * @brief Set GPIO clock
 * @param pin: GPIO pin
 * @return GPIO port
 */
static void set_gpio_clock(pin_name_t pin) {
    switch (pin & 0xF0U) {
        case PORTA:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;

        case PORTB:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;

        case PORTC:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;

#if defined(GPIOD)
        case PORTD:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
#endif /* GPIOD */

#if defined(GPIOE)
        case PORTE:
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
#endif /* GPIOE */

#if defined(GPIOF)
        case PORTF:
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
#endif /* GPIOF */

#if defined(GPIOG)
        case PORTG:
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
#endif /* GPIOG */

#if defined(GPIOH)
        case PORTH:
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
#endif /* GPIOH */

#if defined(GPIOI)
        case PORTI:
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
#endif /* GPIOI */

#if defined(GPIOJ)
        case PORTJ:
            __HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
#endif /* GPIOJ */

#if defined(GPIOK)
        case PORTK:
            __HAL_RCC_GPIOK_CLK_ENABLE();
            break;
#endif /* GPIOK */

            default:
                break;
        }
}
