/**
  * @file    uart_hal.c
  * @author  MorroMaker
  * @brief   UART HAL for STM32
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
#include "hal/uart_hal.h"

static void enable_uart_clock(uart_num_t uart_num);
static void reset_uart_clock(uart_num_t uart_num);
static uart_dev_t get_uart_dev_info(uart_num_t uart_num);

static int uart_hal_init(uart_hal_context_t *context);
static int uart_hal_deinit(uart_hal_context_t *context);
static int uart_set_baud_rate(uart_hal_context_t *context, uint32_t baudrate);
static int uart_set_data_bits(uart_hal_context_t *context, uart_data_bits_t data_bits);
static int uart_set_stop_bits(uart_hal_context_t *context, uart_stop_bits_t stop_bits);
static int uart_set_parity(uart_hal_context_t *context, uart_parity_t parity);
static int uart_set_flow_ctrl(uart_hal_context_t *context, uart_flow_ctrl_t flow_ctrl);
static int uart_hal_start(uart_hal_context_t *context);
static int uart_hal_stop(uart_hal_context_t *context);
static int uart_hal_write(uart_hal_context_t *context, uint8_t *data, uint32_t len);
static int uart_hal_read(uart_hal_context_t *context, uint8_t *data, uint32_t len);

const struct uart_hal_api uart_hal = {
    .init = uart_hal_init,
    .deinit = uart_hal_deinit,
    .set_baud_rate = uart_set_baud_rate,
    .set_data_bits = uart_set_data_bits,
    .set_stop_bits = uart_set_stop_bits,
    .set_parity = uart_set_parity,
    .set_flow_ctrl = uart_set_flow_ctrl,
    .start = uart_hal_start,
    .stop = uart_hal_stop,
    .write = uart_hal_write,
    .read = uart_hal_read,
};

/**
 * @brief Initialize the UART port
 * 
 * @param context Pointer to UART HAL context structure
 * @return Operation status
 */
static int uart_hal_init(uart_hal_context_t *context) {
    int res;

    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    // Get UART dev information
    context->dev = get_uart_dev_info(context->uart_num);

    // Enable UART clock
    enable_uart_clock(context->uart_num);

    if (context->mode == UART_MODE_UART) {
        LL_USART_SetTransferDirection(context->dev.ins, LL_USART_DIRECTION_TX_RX);
    }

    context->is_initiated = true;

    return OMNI_OK;
}

/**
 * @brief Deinitialize the UART port
 * 
 * @param context Pointer to UART HAL context structure
 * @return Operation status
 */
static int uart_hal_deinit(uart_hal_context_t *context) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    // Get UART dev information
    context->dev = get_uart_dev_info(context->uart_num);

    // Reset UART clock
    reset_uart_clock(context->uart_num);

    context->is_initiated = false;

    return OMNI_OK;
}

/**
 * @brief Set UART baud rate
 * 
 * @param context Pointer to UART HAL context structure
 * @param baudrate Baud rate
 * @return Operation status
 */
static int uart_set_baud_rate(uart_hal_context_t *context, uint32_t baudrate) {
    uint32_t pclk;

    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

#if defined(USART6)
#if defined(CONFIG_UART_NUM_1) && defined(CONFIG_UART_NUM_6)
    if (context->uart_num == UART_NUM_1 || context->uart_num == UART_NUM_6) {
        pclk = HAL_RCC_GetPCLK2Freq();
    }
#elif defined(CONFIG_UART_NUM_1)
    if (context->uart_num == UART_NUM_1) {
        pclk = HAL_RCC_GetPCLK2Freq();
    }
#endif /* CONFIG_UART_NUM_1 || CONFIG_UART_NUM_6 */
#else
    if (context->uart_num == UART_NUM_1) {
        pclk = HAL_RCC_GetPCLK2Freq();
    }
#endif /* USART6 */
    else {
        pclk = HAL_RCC_GetPCLK1Freq();
    }

    LL_USART_SetOverSampling(context->dev.ins, LL_USART_OVERSAMPLING_16);

    LL_USART_SetBaudRate(context->dev.ins, pclk, LL_USART_OVERSAMPLING_16, baudrate);

    return OMNI_OK;
}

/**
 * @brief Set UART baud rate
 * 
 * @param context Pointer to UART HAL context structure
 * @param baudrate Baud rate
 * @return Operation status
 */
static int uart_set_data_bits(uart_hal_context_t *context, uart_data_bits_t data_bits) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    if (data_bits == UART_DATA_BITS_8) {
        LL_USART_SetDataWidth(context->dev.ins, LL_USART_DATAWIDTH_8B);
    } else if (data_bits == UART_DATA_BITS_9) {
        LL_USART_SetDataWidth(context->dev.ins, LL_USART_DATAWIDTH_9B);
    }

    return OMNI_OK;
}

/**
 * @brief Set UART stop bits
 * 
 * @param context Pointer to UART HAL context structure
 * @param stop_bits Stop bits
 * @return Operation status
 */
static int uart_set_stop_bits(uart_hal_context_t *context, uart_stop_bits_t stop_bits) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    if (stop_bits == UART_STOP_BITS_0_5) {
        LL_USART_SetStopBitsLength(context->dev.ins, LL_USART_STOPBITS_0_5);
    } else if (stop_bits == UART_STOP_BITS_1) {
        LL_USART_SetStopBitsLength(context->dev.ins, LL_USART_STOPBITS_1);
    } else if (stop_bits == UART_STOP_BITS_1_5) {
        LL_USART_SetStopBitsLength(context->dev.ins, LL_USART_STOPBITS_1_5);
    } else if (stop_bits == UART_STOP_BITS_2) {
        LL_USART_SetStopBitsLength(context->dev.ins, LL_USART_STOPBITS_2);
    }

    return OMNI_OK;
}

/**
 * @brief Set UART parity
 * 
 * @param context Pointer to UART HAL context structure
 * @param parity Parity
 * @return Operation status
 */
static int uart_set_parity(uart_hal_context_t *context, uart_parity_t parity) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    if (parity == UART_PARITY_DISABLE) {
        LL_USART_SetParity(context->dev.ins, LL_USART_PARITY_NONE);
    } else if (parity == UART_PARITY_TYPE_EVEN) {
        LL_USART_SetParity(context->dev.ins, LL_USART_PARITY_EVEN);
    } else if (parity == UART_PARITY_TYPE_ODD) {
        LL_USART_SetParity(context->dev.ins, LL_USART_PARITY_ODD);
    }

    return OMNI_OK;
}

/**
 * @brief Set UART flow control
 * 
 * @param context Pointer to UART HAL context structure
 * @param flow_ctrl Flow control
 * @return Operation status
 */
static int uart_set_flow_ctrl(uart_hal_context_t *context, uart_flow_ctrl_t flow_ctrl) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    if (flow_ctrl == UART_FLOW_CTRL_DISABLE) {
        LL_USART_SetHWFlowCtrl(context->dev.ins, LL_USART_HWCONTROL_NONE);
    } else if (flow_ctrl == UART_FLOW_CTRL_RTS) {
        LL_USART_SetHWFlowCtrl(context->dev.ins, LL_USART_HWCONTROL_RTS);
    } else if (flow_ctrl == UART_FLOW_CTRL_CTS) {
        LL_USART_SetHWFlowCtrl(context->dev.ins, LL_USART_HWCONTROL_CTS);
    } else if (flow_ctrl == UART_FLOW_CTRL_RTS_CTS) {
        LL_USART_SetHWFlowCtrl(context->dev.ins, LL_USART_HWCONTROL_RTS_CTS);
    }

    return OMNI_OK;
}

/**
 * @brief Start UART
 * 
 * @param context Pointer to UART HAL context structure
 * @return Operation status
 */
static int uart_hal_start(uart_hal_context_t *context) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    LL_USART_Enable(context->dev.ins);

    return OMNI_OK;
}

/**
 * @brief Stop UART
 * 
 * @param context Pointer to UART HAL context structure
 * @return Operation status
 */
static int uart_hal_stop(uart_hal_context_t *context) {
    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    LL_USART_Disable(context->dev.ins);

    return OMNI_OK;
}

/**
 * @brief Write data to UART
 * 
 * @param context Pointer to UART HAL context structure
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int uart_hal_write(uart_hal_context_t *context, uint8_t *data, uint32_t len) {
    uint32_t timeout = 0;

    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    context->tx_count = len;

    while (context->tx_count > 0) {
        while (!LL_USART_IsActiveFlag_TXE(context->dev.ins)) {
            if (LL_SYSTICK_IsActiveCounterFlag()) {
                timeout++;
                if (timeout > UART_TX_TIMEOUT_MS) {
                    return OMNI_FAIL;
                }
            }
        }

        LL_USART_TransmitData8(context->dev.ins, *data);
        data++;
        context->tx_count--;
    }

    while (!LL_USART_IsActiveFlag_TC(context->dev.ins)) {
        if (LL_SYSTICK_IsActiveCounterFlag()) {
            timeout++;
            if (timeout > UART_TX_TIMEOUT_MS) {
                return OMNI_FAIL;
            }
        }
    }

    return OMNI_OK;
}

/**
 * @brief Read data from UART
 * 
 * @param context Pointer to UART HAL context structure
 * @param data Pointer to data buffer
 * @param len Data length
 * @return Operation status
 */
static int uart_hal_read(uart_hal_context_t *context, uint8_t *data, uint32_t len) {
    uint32_t timeout = 0;

    if (context == NULL) {
        return OMNI_FAIL;
    }

    if (context->uart_num >= UART_NUM_MAX) {
        return OMNI_FAIL;
    }

    context->rx_count = len;

    while (context->rx_count > 0) {
        while (!LL_USART_IsActiveFlag_RXNE(context->dev.ins)) {
            if (LL_SYSTICK_IsActiveCounterFlag()) {
                timeout++;
                if (timeout > UART_RX_TIMEOUT_MS) {
                    return OMNI_FAIL;
                }
            }
        }

        *data = LL_USART_ReceiveData8(context->dev.ins);

        data++;
        context->rx_count--;
    }

    return OMNI_OK;
}

/**
 * @brief Get UART device information
 * 
 * @param uart_num UART port number
 * @return UART device information
 */
static uart_dev_t get_uart_dev_info(uart_num_t uart_num) {
    uart_dev_t dev;

    switch (uart_num) {
        case UART_NUM_1:
            dev.ins = USART1;
            dev.tx_pin.index = CONFIG_UART1_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART1_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART1_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART1_RX_PIN_AF;
            break;

#if defined(CONFIG_UART_NUM_2)
        case UART_NUM_2:
            dev.ins = USART2;
            dev.tx_pin.index = CONFIG_UART2_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART2_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART2_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART2_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_2 */

#if defined(CONFIG_UART_NUM_3)
        case UART_NUM_3:
            dev.ins = USART3;
            dev.tx_pin.index = CONFIG_UART3_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART3_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART3_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART3_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_3 */

#if defined(CONFIG_UART_NUM_4)
        case UART_NUM_4:
            dev.ins = UART4;
            dev.tx_pin.index = CONFIG_UART4_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART4_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART4_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART4_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_4 */

#if defined(CONFIG_UART_NUM_5)
        case UART_NUM_5:
            dev.ins = UART5;
            dev.tx_pin.index = CONFIG_UART5_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART5_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART5_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART5_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_5 */

#if defined(CONFIG_UART_NUM_6)
        case UART_NUM_6:
            dev.ins = USART6;
            dev.tx_pin.index = CONFIG_UART6_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART6_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART6_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART6_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_6 */

#if defined(CONFIG_UART_NUM_7)
        case UART_NUM_7:
            dev.ins = UART7;
            dev.tx_pin.index = CONFIG_UART7_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART7_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART7_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART7_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_7 */

#if defined(CONFIG_UART_NUM_8)
        case UART_NUM_8:
            dev.ins = UART8;
            dev.tx_pin.index = CONFIG_UART8_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART8_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART8_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART8_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_8 */

#if defined(CONFIG_UART_NUM_9)
        case UART_NUM_9:
            dev.ins = UART9;
            dev.tx_pin.index = CONFIG_UART9_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART9_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART9_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART9_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_9 */

#if defined(CONFIG_UART_NUM_10)
        case UART_NUM_10:
            dev.ins = UART10;
            dev.tx_pin.index = CONFIG_UART10_TX_PIN;
            dev.tx_pin.alternate = CONFIG_UART10_TX_PIN_AF;

            dev.rx_pin.index = CONFIG_UART10_RX_PIN;
            dev.rx_pin.alternate = CONFIG_UART10_RX_PIN_AF;
            break;
#endif /* CONFIG_UART_NUM_10 */

        default:
            dev.ins = NULL;
            break;
    }

    return dev;
}

/**
 * @brief Enable UART clock
 * 
 * @param uart_num UART port number
 */
static void enable_uart_clock(uart_num_t uart_num) {
    switch (uart_num) {
        case UART_NUM_1:
            __HAL_RCC_USART1_CLK_ENABLE();
            break;

#if defined(USART2) && defined(CONFIG_UART_NUM_2)
        case UART_NUM_2:
            __HAL_RCC_USART2_CLK_ENABLE();
            break;
#endif /* USART2 && CONFIG_UART_NUM_2 */

#if defined(USART3) && defined(CONFIG_UART_NUM_3)
        case UART_NUM_3:
            __HAL_RCC_USART3_CLK_ENABLE();
            break;
#endif /* USART3 && CONFIG_UART_NUM_3 */

#if defined(UART4) && defined(CONFIG_UART_NUM_4)
        case UART_NUM_4:
            __HAL_RCC_UART4_CLK_ENABLE();
            break;
#endif /* UART4 && CONFIG_UART_NUM_4 */

#if defined(UART5) && defined(CONFIG_UART_NUM_5)
        case UART_NUM_5:
            __HAL_RCC_UART5_CLK_ENABLE();
            break;
#endif /* UART5 && CONFIG_UART_NUM_5 */

#if defined(USART6) && defined(CONFIG_UART_NUM_6)
        case UART_NUM_6:
            __HAL_RCC_USART6_CLK_ENABLE();
            break;
#endif /* USART6 && CONFIG_UART_NUM_6 */

#if defined(UART7) && defined(CONFIG_UART_NUM_7)
        case UART_NUM_7:
            __HAL_RCC_UART7_CLK_ENABLE();
            break;
#endif /* UART7 && CONFIG_UART_NUM_7 */

#if defined(UART8) && defined(CONFIG_UART_NUM_8)
        case UART_NUM_8:
            __HAL_RCC_UART8_CLK_ENABLE();
            break;
#endif /* UART8 && CONFIG_UART_NUM_8 */

#if defined(UART9) && defined(CONFIG_UART_NUM_9)
        case UART_NUM_9:
            __HAL_RCC_UART9_CLK_ENABLE();
            break;
#endif /* UART9 && CONFIG_UART_NUM_9 */

#if defined(UART10) && defined(CONFIG_UART_NUM_10)
        case UART_NUM_10:
            __HAL_RCC_UART10_CLK_ENABLE();
            break;
#endif /* UART10 && CONFIG_UART_NUM_10 */

        default:
            break;
    }
}

/**
 * @brief Reset UART clock
 * 
 * @param uart_num UART port number
 */
static void reset_uart_clock(uart_num_t uart_num) {
    switch (uart_num) {
        case UART_NUM_1:
            __HAL_RCC_USART1_FORCE_RESET();
            __HAL_RCC_USART1_RELEASE_RESET();
            break;

#if defined(USART2) && defined(CONFIG_UART_NUM_2)
        case UART_NUM_2:
            __HAL_RCC_USART2_FORCE_RESET();
            __HAL_RCC_USART2_RELEASE_RESET();
            break;
#endif /* USART2 && CONFIG_UART_NUM_2 */

#if defined(USART3) && defined(CONFIG_UART_NUM_3)
        case UART_NUM_3:
            __HAL_RCC_USART3_FORCE_RESET();
            __HAL_RCC_USART3_RELEASE_RESET();
            break;

#endif /* USART3 && CONFIG_UART_NUM_3 */

#if defined(UART4) && defined(CONFIG_UART_NUM_4)
        case UART_NUM_4:
            __HAL_RCC_UART4_FORCE_RESET();
            __HAL_RCC_UART4_RELEASE_RESET();
            break;
#endif /* UART4 && CONFIG_UART_NUM_4 */

#if defined(UART5) && defined(CONFIG_UART_NUM_5)
        case UART_NUM_5:
            __HAL_RCC_UART5_FORCE_RESET();
            __HAL_RCC_UART5_RELEASE_RESET();
            break;
#endif /* UART5 && CONFIG_UART_NUM_5 */

#if defined(USART6) && defined(CONFIG_UART_NUM_6)
        case UART_NUM_6:
            __HAL_RCC_USART6_FORCE_RESET();
            __HAL_RCC_USART6_RELEASE_RESET();
            break;
#endif /* USART6 && CONFIG_UART_NUM_6 */

#if defined(UART7) && defined(CONFIG_UART_NUM_7)
        case UART_NUM_7:
            __HAL_RCC_UART7_FORCE_RESET();
            __HAL_RCC_UART7_RELEASE_RESET();
            break;
#endif /* UART7 && CONFIG_UART_NUM_7 */

#if defined(UART8) && defined(CONFIG_UART_NUM_8)
        case UART_NUM_8:
            __HAL_RCC_UART8_FORCE_RESET();
            __HAL_RCC_UART8_RELEASE_RESET();
            break;
#endif /* UART8 && CONFIG_UART_NUM_8 */

#if defined(UART9) && defined(CONFIG_UART_NUM_9)
        case UART_NUM_9:
            __HAL_RCC_UART9_FORCE_RESET();
            __HAL_RCC_UART9_RELEASE_RESET();
            break;
#endif /* UART9 && CONFIG_UART_NUM_9 */

#if defined(UART10) && defined(CONFIG_UART_NUM_10)
        case UART_NUM_10:
            __HAL_RCC_UART10_FORCE_RESET();
            __HAL_RCC_UART10_RELEASE_RESET();
            break;
#endif /* UART10 && CONFIG_UART_NUM_10 */

        default:
            break;
    }
}
