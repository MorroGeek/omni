/**
  * @file    uart.h
  * @author  MorroMaker
  * @brief   UART driver for omni
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
#ifndef OMNI_DRIVERS_UART_H
#define OMNI_DRIVERS_UART_H

/* Includes ------------------------------------------------------------------*/
#include "hal/uart_hal.h"

#if defined(CONFIG_OMNI_DRIVERS_UART)

#ifdef __cplusplus
extern "C" {
#endif

#define UART_PIN_DEFAULT    (-1)

/**
 * @brief UART driver configuration
 */
typedef struct uart_driver_config {
    uart_mode_t mode;               /**< UART mode */
    uint32_t baudrate;              /**< Baudrate setting in bps */
    uart_data_bits_t data_bits;     /**< Data bits */
    uart_stop_bits_t stop_bits;     /**< Stop bits */
    uart_parity_t parity;           /**< Parity */
    uart_flow_ctrl_t flow_ctrl;     /**< Flow control setting */
} uart_driver_config_t;

/**
 * @brief Initialize UART driver
 */
typedef int (*uart_init_t)(uart_num_t uart_num, uart_driver_config_t *config);

/**
 * @brief Deinitialize UART driver
 */
typedef int (*uart_deinit_t)(uart_num_t uart_num);

/**
 * @brief Write bytes to UART port
 */
typedef int (*uart_write_bytes_t)(uart_num_t uart_num, uint8_t *data, uint32_t len);

/**
 * @brief Read bytes from UART port
 */
typedef int (*uart_read_bytes_t)(uart_num_t uart_num, uint8_t *data, uint32_t len);

/**
 * @brief UART driver API
 */
struct uart_driver_api {
    uart_init_t init;
    uart_deinit_t deinit;
    uart_write_bytes_t write_bytes;
    uart_read_bytes_t read_bytes;
};

extern struct uart_driver_api uart_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONFIG_OMNI_DRIVERS_UART */

#endif /* OMNI_DRIVERS_UART_H */
