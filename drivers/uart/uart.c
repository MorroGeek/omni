/**
  * @file    uart.c
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

/* Includes ------------------------------------------------------------------*/
#include "drivers/uart/uart.h"
#include "drivers/gpio/gpio.h"
#include "drivers/assert.h"

// #include "cmsis_os2.h"

#if defined(CONFIG_OMNI_DRIVERS_UART)

/**
 * @brief UART driver data structure
 */
typedef struct uart_driver_data {
    // void *rx_buffer;            /**< Pointer to RX buffer */
    // void *tx_buffer;            /**< Pointer to TX buffer */
    bool is_initiated;          /**< Flag indicating if the UART port is initiated */
} uart_driver_data_t;

/**
 * @brief UART object structure
 */
typedef struct {
    uart_hal_context_t hal_context;     /**< UART HAL context */
    uart_driver_data_t driver_data;     /**< UART driver data */
    // osSemaphoreId_t tx_mux;             /**< UART TX mutex */
    // osSemaphoreId_t rx_mux;             /**< UART RX mutex */
} uart_obj_t;

static uart_obj_t *p_uart_obj[UART_NUM_MAX];

static int uart_open(uart_num_t uart_num, uart_driver_config_t *config);
static int uart_close(uart_num_t uart_num);
static int uart_start(uart_num_t uart_num);
static int uart_stop(uart_num_t uart_num);
static int uart_write_bytes(uart_num_t uart_num, uint8_t *data, uint32_t len);
static int uart_read_bytes(uart_num_t uart_num, uint8_t *data, uint32_t len);

struct uart_driver_api uart_driver = {
    .open = uart_open,
    .close = uart_close,
    .start = uart_start,
    .stop = uart_stop,
    .write_bytes = uart_write_bytes,
    .read_bytes = uart_read_bytes,
};

/**
 * @brief Open the UART port
 * 
 * @param uart_num UART port number
 * @param config Pointer to UART driver configuration structure
 * @return Operation status
 */
static int uart_open(uart_num_t uart_num, uart_driver_config_t *config) {
    int res;
    p_uart_obj[uart_num] = (uart_obj_t *)OMNI_MALLOC(sizeof(uart_obj_t));
    if (p_uart_obj[uart_num] == NULL) {
        return OMNI_FAIL;
    }

    p_uart_obj[uart_num]->hal_context.uart_num = uart_num;
    p_uart_obj[uart_num]->hal_context.mode = config->mode;

    res = uart_hal.init(&p_uart_obj[uart_num]->hal_context);
    if (res != OMNI_OK) {
        OMNI_FREE(p_uart_obj[uart_num]);
        p_uart_obj[uart_num] = NULL;
        return res;
    }

    // Set UART pins
    gpio_driver_config_t gpio_config = {
        .mode = GPIO_MODE_PP_AF,
        .pull = GPIO_PULL_NONE,
        .speed = GPIO_SPEED_LEVEL_HIGH,
    };

    // Set TX pin
    gpio_config.alternate = p_uart_obj[uart_num]->hal_context.dev.tx_pin.alternate;
    res = gpio_driver.open(p_uart_obj[uart_num]->hal_context.dev.tx_pin.index, &gpio_config);
    if (res != OMNI_OK) {
        OMNI_FREE(p_uart_obj[uart_num]);
        p_uart_obj[uart_num] = NULL;
        return res;
    }

    // Set RX pin
    gpio_config.alternate = p_uart_obj[uart_num]->hal_context.dev.rx_pin.alternate;
    res = gpio_driver.open(p_uart_obj[uart_num]->hal_context.dev.rx_pin.index, &gpio_config);
    if (res != OMNI_OK) {
        OMNI_FREE(p_uart_obj[uart_num]);
        p_uart_obj[uart_num] = NULL;
        return res;
    }

    // Set UART parameters
    if ((res = uart_hal.disable(&p_uart_obj[uart_num]->hal_context)) != OMNI_OK ||
        (res = uart_hal.set_stop_bits(&p_uart_obj[uart_num]->hal_context, config->stop_bits)) != OMNI_OK ||
        (res = uart_hal.set_data_bits(&p_uart_obj[uart_num]->hal_context, config->data_bits)) != OMNI_OK ||
        (res = uart_hal.set_parity(&p_uart_obj[uart_num]->hal_context, config->parity)) != OMNI_OK ||
        (res = uart_hal.set_flow_ctrl(&p_uart_obj[uart_num]->hal_context, config->flow_ctrl)) != OMNI_OK ||
        (res = uart_hal.set_baud_rate(&p_uart_obj[uart_num]->hal_context, config->baudrate)) != OMNI_OK ||
        (res = uart_hal.enable(&p_uart_obj[uart_num]->hal_context)) != OMNI_OK) {
        // Close GPIO
        gpio_driver.close(p_uart_obj[uart_num]->hal_context.dev.tx_pin.index);
        gpio_driver.close(p_uart_obj[uart_num]->hal_context.dev.rx_pin.index);
        // Free UART object
        OMNI_FREE(p_uart_obj[uart_num]);
        p_uart_obj[uart_num] = NULL;
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Close the UART port
 * 
 * @param uart_num UART port number
 * @return Operation status
 */
static int uart_close(uart_num_t uart_num) {
    int res;

    res = uart_hal.deinit(&p_uart_obj[uart_num]->hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    if (p_uart_obj[uart_num] != NULL) {
        OMNI_FREE(p_uart_obj[uart_num]);
        p_uart_obj[uart_num] = NULL;
    }

    return OMNI_OK;
}

/**
 * @brief Start UART port
 * 
 * @param uart_num UART port number
 * @return Operation status
 */
static int uart_start(uart_num_t uart_num) {
    int res;

    res = uart_hal.enable(&p_uart_obj[uart_num]->hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Stop UART port
 * 
 * @param uart_num UART port number
 * @return Operation status
 */
static int uart_stop(uart_num_t uart_num) {
    int res;

    res = uart_hal.disable(&p_uart_obj[uart_num]->hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Write bytes to UART port
 * 
 * @param uart_num UART port number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int uart_write_bytes(uart_num_t uart_num, uint8_t *data, uint32_t len) {
    int res;

    res = uart_hal.write(&p_uart_obj[uart_num]->hal_context, data, len);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

/**
 * @brief Read bytes from UART port
 * 
 * @param uart_num UART port number
 * @param data Pointer to data buffer
 * @param len Length of data buffer
 * @return Operation status
 */
static int uart_read_bytes(uart_num_t uart_num, uint8_t *data, uint32_t len) {
    int res;

    res = uart_hal.read(&p_uart_obj[uart_num]->hal_context, data, len);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

#endif /* CONFIG_OMNI_DRIVERS_UART */
