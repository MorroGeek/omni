/**
  * @file    serial_hal.c
  * @author  MorroMaker
  * @brief   Serial HAL for STM32F4
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
#include "serial_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define GET_OBJ_HANDLE(obj) ((UART_HandleTypeDef *)obj->serial.handle)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
 * @brief Initialize the serial port
 * @param obj: Serial handle structure
 * @retval true: success
 *         false: fail
 */
bool serial_init(serial_t *obj)
{
    UART_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return false;
    }

    switch (obj->mode) {
        case OMNI_SERIAL_MODE_BASE:
            handle->Init.Mode = UART_MODE_TX_RX;
            break;

        default:
            return false;
    }

    handle->Init.BaudRate = obj->baud_rate;

    switch (obj->data_bits) {
        case OMNI_SERIAL_WORDLENGTH_8B:
            handle->Init.WordLength = UART_WORDLENGTH_8B;
            break;

        case OMNI_SERIAL_WORDLENGTH_9B:
            handle->Init.WordLength = UART_WORDLENGTH_9B;
            break;

        default:
            return false;
    }

    switch (obj->stop_bits) {
        case OMNI_SERIAL_STOPBITS_1:
            handle->Init.StopBits = UART_STOPBITS_1;
            break;

        case OMNI_SERIAL_STOPBITS_2:
            handle->Init.StopBits = UART_STOPBITS_2;
            break;

        default:
            return false;
    }

    switch (obj->parity) {
        case OMNI_SERIAL_PARITY_NONE:
            handle->Init.Parity = UART_PARITY_NONE;
            break;

        case OMNI_SERIAL_PARITY_EVEN:
            handle->Init.Parity = UART_PARITY_EVEN;
            break;

        case OMNI_SERIAL_PARITY_ODD:
            handle->Init.Parity = UART_PARITY_ODD;
            break;

        default:
            return false;
    }

    handle->Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(handle) != HAL_OK) {
        return false;
    }

    return true;
}

/**
 * @brief Deinitialize the serial port
 * @param obj: Serial handle structure
 * @retval true: success
 *         false: fail
 */
bool serial_deinit(serial_t *obj)
{
    UART_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return false;
    }

    if (HAL_UART_DeInit(handle) != HAL_OK) {
        return false;
    }

    return true;
}

/**
 * @brief Write data to the serial port
 * @param obj: Serial handle structure
 * @param data: Data buffer
 * @param size: Data size
 * @param timeout: Timeout
 * @retval true: success
 *         false: fail
 */
bool serial_write(serial_t *obj, uint8_t *data, uint32_t size, uint32_t timeout)
{
    UART_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return false;
    }

    if (HAL_UART_Transmit(handle, data, size, timeout) != HAL_OK) {
        return false;
    }

    return true;
}

/**
 * @brief Read data from the serial port
 * @param obj: Serial handle structure
 * @param data: Data buffer
 * @param size: Data size
 * @param timeout: Timeout
 * @retval true: success
 *         false: fail
 */
bool serial_read(serial_t *obj, uint8_t *data, uint32_t size, uint32_t timeout)
{
    UART_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return false;
    }

    if (HAL_UART_Receive(handle, data, size, timeout) != HAL_OK) {
        return false;
    }

    return true;
}


/* Private functions ---------------------------------------------------------*/