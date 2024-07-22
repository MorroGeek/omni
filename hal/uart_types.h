/**
  * @file    uart_types.h
  * @author  MorroMaker
  * @brief   UART HAL types
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
#ifndef OMNI_HAL_UART_TYPES_H
#define OMNI_HAL_UART_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal/device.h"

/**
 * @brief UART mode
 */
typedef enum {
    UART_MODE_UART,
} uart_mode_t;

/**
 * @brief UART data bits
 */
typedef enum {
    UART_DATA_BITS_8 = 0x00,
    UART_DATA_BITS_9 = 0x01,
} uart_data_bits_t;

/**
 * @brief UART stop bits
 */
typedef enum {
    UART_STOP_BITS_0_5 = 0x00,
    UART_STOP_BITS_1 = 0x01,
    UART_STOP_BITS_1_5 = 0x02,
    UART_STOP_BITS_2 = 0x03,
} uart_stop_bits_t;

/**
 * @brief UART parity
 */
typedef enum {
    UART_PARITY_DISABLE = 0x00,
    UART_PARITY_TYPE_EVEN = 0x01,
    UART_PARITY_TYPE_ODD = 0x02,
} uart_parity_t;

/**
 * @brief UART flow control
 */
typedef enum {
    UART_FLOW_CTRL_DISABLE = 0x00,
    UART_FLOW_CTRL_RTS = 0x01,
    UART_FLOW_CTRL_CTS = 0x02,
    UART_FLOW_CTRL_RTS_CTS = 0x03,
} uart_flow_ctrl_t;

/**
 * @brief UART port number
 */
typedef enum {
#ifdef CONFIG_UART_NUM_1
    UART_NUM_1 = 0x01,
#endif /* CONFIG_UART_NUM_1 */
#ifdef CONFIG_UART_NUM_2
    UART_NUM_2 = 0x02,
#endif /* CONFIG_UART_NUM_2 */
#ifdef CONFIG_UART_NUM_3
    UART_NUM_3 = 0x03,
#endif /* CONFIG_UART_NUM_3 */
#ifdef CONFIG_UART_NUM_4
    UART_NUM_4 = 0x04,
#endif /* CONFIG_UART_NUM_4 */
#ifdef CONFIG_UART_NUM_5
    UART_NUM_5 = 0x05,
#endif /* CONFIG_UART_NUM_5 */
#ifdef CONFIG_UART_NUM_6
    UART_NUM_6 = 0x06,
#endif /* CONFIG_UART_NUM_6 */
#ifdef CONFIG_UART_NUM_7
    UART_NUM_7 = 0x07,
#endif /* CONFIG_UART_NUM_7 */
#ifdef CONFIG_UART_NUM_8
    UART_NUM_8 = 0x08,
#endif /* CONFIG_UART_NUM_8 */
#ifdef CONFIG_UART_NUM_9
    UART_NUM_9 = 0x09,
#endif /* CONFIG_UART_NUM_9 */
#ifdef CONFIG_UART_NUM_10
    UART_NUM_10 = 0x10,
#endif /* CONFIG_UART_NUM_10 */
    UART_NUM_MAX,
} uart_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_UART_TYPES_H */
