/**
  * @file    uart_hal.h
  * @author  MorroMaker
  * @brief   Header for uart_hal.c file
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
#ifndef OMNI_HAL_UART_H
#define OMNI_HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal/uart_types.h"

#define UART_TX_TIMEOUT_MS 10
#define UART_RX_TIMEOUT_MS 10

typedef struct uart_hal_context {
    uart_dev_t dev;
    uart_mode_t mode;
    uart_num_t uart_num;
    uint32_t tx_count;
    uint32_t rx_count;
    bool is_initiated;
} uart_hal_context_t;

/**
 * @brief UART controller HAL API structure
 */
struct uart_hal_api {
    int (*init)(uart_hal_context_t *context);
    int (*deinit)(uart_hal_context_t *context);
    int (*set_baud_rate)(uart_hal_context_t *context, uint32_t baudrate);
    int (*set_data_bits)(uart_hal_context_t *context, uart_data_bits_t data_bits);
    int (*set_stop_bits)(uart_hal_context_t *context, uart_stop_bits_t stop_bits);
    int (*set_parity)(uart_hal_context_t *context, uart_parity_t parity);
    int (*set_flow_ctrl)(uart_hal_context_t *context, uart_flow_ctrl_t flow_ctrl);
    int (*start)(uart_hal_context_t *context);
    int (*stop)(uart_hal_context_t *context);
    int (*write)(uart_hal_context_t *context, uint8_t *data, uint32_t len);
    int (*read)(uart_hal_context_t *context, uint8_t *data, uint32_t len);
};

extern const struct uart_hal_api uart_hal;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_UART_H */
