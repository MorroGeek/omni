/**
  * @file    gpio_hal.c
  * @author  MorroMaker
  * @brief   GPIO HAL for STM32
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

// Low level pin alternate function
static const uint32_t ll_pin_af[] = {
    LL_GPIO_AF_0,
    LL_GPIO_AF_1,
    LL_GPIO_AF_2,
    LL_GPIO_AF_3,
    LL_GPIO_AF_4,
    LL_GPIO_AF_5,
    LL_GPIO_AF_6,
    LL_GPIO_AF_7,
    LL_GPIO_AF_8,
    LL_GPIO_AF_9,
    LL_GPIO_AF_10,
    LL_GPIO_AF_11,
    LL_GPIO_AF_12,
    LL_GPIO_AF_13,
    LL_GPIO_AF_14,
    LL_GPIO_AF_15,
};

/* Private function prototypes -----------------------------------------------*/
static void enable_gpio_clock(gpio_num_t gpio_num);
static GPIO_TypeDef *get_gpio_port(gpio_num_t gpio_num);
static uint32_t get_gpio_pin(gpio_num_t gpio_num);

static int gpio_hal_init(gpio_hal_context_t *context);
static int gpio_hal_deinit(gpio_hal_context_t *context);
static int gpio_hal_mode(gpio_hal_context_t *context, gpio_mode_t mode);
static int gpio_hal_alternate(gpio_hal_context_t *context, uint32_t alternate);
static int gpio_hal_pull(gpio_hal_context_t *context, gpio_pull_t pull);
static int gpio_hal_speed(gpio_hal_context_t *context, gpio_speed_t speed);
static int gpio_hal_write(gpio_hal_context_t *context, uint32_t value);
static int gpio_hal_read(gpio_hal_context_t *context, uint32_t *value);
static int gpio_hal_toggle(gpio_hal_context_t *context);

const struct gpio_hal_api gpio_hal = {
    .init = gpio_hal_init,
    .deinit = gpio_hal_deinit,
    .mode = gpio_hal_mode,
    .alternate = gpio_hal_alternate,
    .pull = gpio_hal_pull,
    .speed = gpio_hal_speed,
    .write = gpio_hal_write,
    .read = gpio_hal_read,
    .toggle = gpio_hal_toggle,
};

/**
 * @brief Initialize GPIO
 * @param context: Pointer to GPIO HAL context structure
 * @return Operation status
 */
static int gpio_hal_init(gpio_hal_context_t *context) {
    int res;

    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // if (context->gpio_num != gpio_num) {
    //     // Get GPIO port
    //     context->dev.ins = get_gpio_port(gpio_num);

    //     // Get GPIO pin
    //     context->dev.pin = get_gpio_pin(gpio_num);
    // }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    // Enable GPIO clock
    enable_gpio_clock(context->gpio_num);

    context->is_initiated = true;

    return OMNI_OK;
}

/**
 * @brief Deinitialize GPIO
 * @param context: Pointer to GPIO HAL context structure
 * @return Operation status
 */
static int gpio_hal_deinit(gpio_hal_context_t *context) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    context->is_initiated = false;

    return OMNI_OK;
}

/**
 * @brief Set GPIO mode
 * @param context: Pointer to GPIO HAL context structure
 * @param mode: GPIO mode
 * @return Operation status
 */
static int gpio_hal_mode(gpio_hal_context_t *context, gpio_mode_t mode) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    // Set GPIO output type
    if ((mode == GPIO_MODE_OD_OUTPUT) || (mode == GPIO_MODE_OD_AF)) {
        LL_GPIO_SetPinOutputType(context->dev.ins, context->dev.pin, LL_GPIO_OUTPUT_OPENDRAIN);
    } else {
        LL_GPIO_SetPinOutputType(context->dev.ins, context->dev.pin, LL_GPIO_OUTPUT_PUSHPULL);
    }

    // Set GPIO mode
    if ((mode == GPIO_MODE_PP_OUTPUT) || (mode == GPIO_MODE_OD_OUTPUT)) {
        LL_GPIO_SetPinMode(context->dev.ins, context->dev.pin, LL_GPIO_MODE_OUTPUT);
    } else if ((mode == GPIO_MODE_PP_AF) || (mode == GPIO_MODE_OD_AF)) {
        LL_GPIO_SetPinMode(context->dev.ins, context->dev.pin, LL_GPIO_MODE_ALTERNATE);
    } else {
        LL_GPIO_SetPinMode(context->dev.ins, context->dev.pin, LL_GPIO_MODE_INPUT);
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO alternate function
 * @param context: Pointer to GPIO HAL context structure
 * @param alternate: GPIO alternate function
 * @return Operation status
 */
static int gpio_hal_alternate(gpio_hal_context_t *context, uint32_t alternate) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    if (POSITION_VAL(context->dev.pin) < 0x00000008U) {
        LL_GPIO_SetAFPin_0_7(context->dev.ins, context->dev.pin, ll_pin_af[alternate]);
    } else {
        LL_GPIO_SetAFPin_8_15(context->dev.ins, context->dev.pin, ll_pin_af[alternate]);
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO pull
 * @param context: Pointer to GPIO HAL context structure
 * @param pull: GPIO pull
 * @return Operation status
 */
static int gpio_hal_pull(gpio_hal_context_t *context, gpio_pull_t pull) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    // Set GPIO pull
    if (pull == GPIO_PULL_UP) {
        LL_GPIO_SetPinPull(context->dev.ins, context->dev.pin, LL_GPIO_PULL_UP);
    } else if (pull == GPIO_PULL_DOWN) {
        LL_GPIO_SetPinPull(context->dev.ins, context->dev.pin, LL_GPIO_PULL_DOWN);
    } else {
        LL_GPIO_SetPinPull(context->dev.ins, context->dev.pin, LL_GPIO_PULL_NO);
    }

    return OMNI_OK;
}

/**
 * @brief Set GPIO speed
 * @param context: Pointer to GPIO HAL context structure
 * @param speed: GPIO speed
 * @return Operation status
 */
static int gpio_hal_speed(gpio_hal_context_t *context, gpio_speed_t speed) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    LL_GPIO_SetPinSpeed(context->dev.ins, context->dev.pin, speed);

    return OMNI_OK;
}

/**
 * @brief Write GPIO
 * @param context: Pointer to GPIO HAL context structure
 * @param value: GPIO value
 * @return Operation status
 */
static int gpio_hal_write(gpio_hal_context_t *context, uint32_t value) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    if (value) {
        LL_GPIO_SetOutputPin(context->dev.ins, context->dev.pin);
    } else {
        LL_GPIO_ResetOutputPin(context->dev.ins, context->dev.pin);
    }

    return OMNI_OK;
}

/**
 * @brief Toggle GPIO
 * @param context: Pointer to GPIO HAL context structure
 * @return Operation status
 */
static int gpio_hal_toggle(gpio_hal_context_t *context) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    LL_GPIO_TogglePin(context->dev.ins, context->dev.pin);

    return OMNI_OK;
}

/**
 * @brief Read GPIO
 * @param context: Pointer to GPIO HAL context structure
 * @param value: Pointer to GPIO value
 * @return Operation status
 */
static int gpio_hal_read(gpio_hal_context_t *context, uint32_t *value) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->gpio_num == GPIO_NUM_NC) {
        return OMNI_FAIL;
    }

    // Get GPIO port
    context->dev.ins = get_gpio_port(context->gpio_num);

    // Get GPIO pin
    context->dev.pin = get_gpio_pin(context->gpio_num);

    *value = LL_GPIO_IsInputPinSet(context->dev.ins, context->dev.pin);

    return OMNI_OK;
}

/**
 * @brief Get GPIO pin
 * 
 * @param gpio_num: GPIO pin number
 * @return GPIO pin
 */
static uint32_t get_gpio_pin(gpio_num_t gpio_num) {
    return ll_pin[gpio_num & 0x0F];
}

/**
 * @brief Get GPIO port
 * 
 * @param gpio_num: GPIO pin number
 * @return GPIO port
 */
static GPIO_TypeDef *get_gpio_port(gpio_num_t gpio_num) {
    switch (gpio_num & 0xF0U) {
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
            return NULL;
    }
}

/**
 * @brief Enable GPIO clock
 * 
 * @param gpio_num: GPIO pin number
 */
static void enable_gpio_clock(gpio_num_t gpio_num) {
    switch (gpio_num & 0xF0U) {
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
