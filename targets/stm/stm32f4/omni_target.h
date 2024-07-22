/**
  * @file    omni_target.h
  * @author  MorroMaker
  * @brief   Target specific header file
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
#ifndef OMNI_TARGETS_H
#define OMNI_TARGETS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx_ll_cortex.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/

/**
 * @brief  Port name type definition
 */
typedef enum {
    PORTA = 0x00,
    PORTB = 0x10,
    PORTC = 0x20,
    PORTD = 0x30,
    PORTE = 0x40,
    PORTF = 0x50,
    PORTG = 0x60,
    PORTH = 0x70,
    PORTI = 0x80,
    PORTJ = 0x90,
    PORTK = 0xA0,
} port_name_t;

struct serial_s {
    UART_HandleTypeDef *handle;
    USART_TypeDef *ins;
    uint32_t max_speed;   // Maximum speed (Unit: Kbps)
};

struct i2c_s {
    I2C_HandleTypeDef *handle;
    I2C_TypeDef *ins;
    uint32_t max_freq;   // Maximum frequency (Unit: KHz)
};

struct spi_s {
    SPI_HandleTypeDef *handle;
    SPI_TypeDef *ins;
    uint32_t max_freq;   // Maximum frequency (Unit: KHz)
};

typedef struct gpio_pin {
    uint32_t index;
    uint32_t alternate;
} gpio_pin_t;

typedef struct gpio_dev {
    GPIO_TypeDef *ins;
    uint32_t pin;
} gpio_dev_t;

typedef struct uart_dev {
    USART_TypeDef *ins;
    gpio_pin_t tx_pin;
    gpio_pin_t rx_pin;
} uart_dev_t;

#ifdef __cplusplus
}
#endif

#endif /* OMNI_TARGETS_H */
