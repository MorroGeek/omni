/**
  * @file    omni_board.c
  * @author  MorroMaker
  * @brief   Board support package for OmniOS
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
#include "omni_board.h"
#include "hal/gpio_hal.h"

/* Private variables ---------------------------------------------------------*/

// // GPIO map for ADC
// const pin_map_t adc_gpio_map[] = {
//         {PA0, OMNI_ADC1, {OMNI_GPIO_ANALOG, OMNI_GPIO_INPUT, OMNI_GPIO_SPEED_LOW, 0, 0,  OMNI_GPIO_NONINVERTED, OMNI_GPIO_LOW}},
//         {PA1, OMNI_ADC1, {OMNI_GPIO_ANALOG, OMNI_GPIO_INPUT, OMNI_GPIO_SPEED_LOW, 0, 1,  OMNI_GPIO_NONINVERTED, OMNI_GPIO_LOW}},
//         //{PA2, OMNI_ADC1, {OMNI_GPIO_ANALOG, OMNI_GPIO_INPUT, OMNI_GPIO_SPEED_LOW, 0, 2,  0, 0}},
//         //{PA3, OMNI_ADC1, {OMNI_GPIO_ANALOG, OMNI_GPIO_INPUT, OMNI_GPIO_SPEED_LOW, 0, 3,  0, 0}},
// };

// const pin_map_t uart_tx_gpio_map[] = {
//         {PA2, OMNI_UART2, {OMNI_GPIO_AF_PP, OMNI_GPIO_OUTPUT, OMNI_GPIO_SPEED_HIGH, GPIO_AF7_USART2, 0,  OMNI_GPIO_NONINVERTED, OMNI_GPIO_LOW}},
//         {PA9, OMNI_UART1, {OMNI_GPIO_AF_PP, OMNI_GPIO_OUTPUT, OMNI_GPIO_SPEED_HIGH, GPIO_AF7_USART1, 0,  OMNI_GPIO_NONINVERTED, OMNI_GPIO_LOW}}
// };

// const pin_map_t uart_rx_gpio_map[] = {
//         {PA3, OMNI_UART2, {OMNI_GPIO_AF_PP, OMNI_GPIO_INPUT, OMNI_GPIO_SPEED_HIGH, GPIO_AF7_USART2, 0,  OMNI_GPIO_NONINVERTED, OMNI_GPIO_LOW}},
//         {PA10, OMNI_UART1, {OMNI_GPIO_AF_PP, OMNI_GPIO_INPUT, OMNI_GPIO_SPEED_HIGH, GPIO_AF7_USART1, 0,  OMNI_GPIO_NONINVERTED, OMNI_GPIO_LOW}}
// };