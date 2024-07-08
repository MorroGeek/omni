/**
  * @file    i2c_hal.c
  * @author  MorroMaker
  * @brief   I2C HAL for STM32F4
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
#include "hal/i2c_hal.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define GET_OBJ_HANDLE(obj) ((I2C_HandleTypeDef *)obj->i2c.handle)

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static int i2c_hw_reset(i2c_t *obj);
static int i2c_sw_reset(i2c_t *obj);

static int i2c_init(i2c_t *obj);
static int i2c_deinit(i2c_t *obj);
static int i2c_write(i2c_t *obj, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout);
static int i2c_read(i2c_t *obj, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout);
static int i2c_enable_listen(i2c_t *obj);
static int i2c_disable_listen(i2c_t *obj);

/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/

static struct i2c_driver_api i2c_stm32_driver = {
    .init = i2c_init,
    .deinit = i2c_deinit,
    .write = i2c_write,
    .read = i2c_read,
    .enable_listen = i2c_enable_listen,
    .disable_listen = i2c_disable_listen,
};

struct i2c_driver_api *i2c_driver(void) {
    return &i2c_stm32_driver;
}

/**
 * @brief Initialize the I2C bus
 * @param obj: I2C handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_init(i2c_t *obj) {
    int res;

    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    // Limit the frequency
    if (obj->frequency > obj->i2c.max_freq) {
        obj->frequency = obj->i2c.max_freq;
    }

    // Initialize the I2C bus
    if (obj->mode == OMNI_I2C_MODE_MASTER) {
        handle->Init.ClockSpeed = (uint32_t) (obj->frequency) * 1000;  // 1000倍频率，单位为Hz
        handle->Init.DutyCycle = I2C_DUTYCYCLE_2;  // 50%快速模式占空比，即高电平和低电平时间相等，仅在快速模式下有效
    } else if (obj->mode == OMNI_I2C_MODE_SLAVE) {
        handle->Init.ClockSpeed = (uint32_t) (obj->frequency) * 1000;  // 1000倍频率，单位为Hz
        handle->Init.DutyCycle = I2C_DUTYCYCLE_2;  // 50%快速模式占空比，即高电平和低电平时间相等，仅在快速模式下有效
        handle->Init.OwnAddress1 = (uint32_t) (obj->address1);  // 从机地址
        handle->Init.OwnAddress2 = (uint32_t) (obj->address2);  // 第二个地址
        handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;  // 7位地址模式，例如从机地址为10100000b,实际地址为01010000b,最低位为读写位
        handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;  // 双地址模式
        handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;  // 使能广播呼叫，对地址00h应答
        handle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;  // 使能时钟拉伸，从机可以拉伸时钟周期，以便于从机处理数据
    } else {
        return OMNI_FAIL;
    }

    // Reset to clear pending flags if any
    res = i2c_hw_reset(obj);
    if (res != OMNI_OK) {
        return res;
    }

    if (HAL_I2C_Init(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Deinitialize the I2C bus
 * @param obj: I2C handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_deinit(i2c_t *obj) {
    int res;

    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    // Reset to clear pending flags if any
    res = i2c_hw_reset(obj);
    if (res != OMNI_OK) {
        return res;
    }

    // Deinitialize the I2C bus
    if (HAL_I2C_DeInit(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief  Write data to I2C
 * @param  obj: I2C handle structure
 * @param  devAddress: device address
 * @param  pData: data to write
 * @param  size: size of data
 * @param  timeout: timeout
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_write(i2c_t *obj, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout) {
    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    if (HAL_I2C_Master_Transmit(handle, devAddress, pData, size, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief  Read data from I2C
 * @param  obj: I2C handle structure
 * @param  devAddress: device address
 * @param  pData: data to read
 * @param  size: size of data
 * @param  timeout: timeout
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_read(i2c_t *obj, uint16_t devAddress, uint8_t *pData, uint16_t size, uint32_t timeout) {
    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    if (HAL_I2C_Master_Receive(handle, devAddress, pData, size, timeout) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief  I2C enable listen
 * @param  obj: I2C handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_enable_listen(i2c_t *obj) {
    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (HAL_I2C_EnableListen_IT(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief  I2C disable listen
 * @param  obj: I2C handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_disable_listen(i2c_t *obj) {
    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (HAL_I2C_DisableListen_IT(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief Reset the I2C bus
 * @param obj: I2C handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_hw_reset(i2c_t *obj) {
    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    // Reset the I2C bus
    if (HAL_I2C_DeInit(handle) != HAL_OK) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Reset the I2C bus
 * @param obj: I2C handle structure
 * @return Operation status
 *         @arg OMNI_OK: Operation successful
 *         @arg OMNI_FAIL: Operation failed
 */
static int i2c_sw_reset(i2c_t *obj) {
    I2C_HandleTypeDef *handle = GET_OBJ_HANDLE(obj);

    if (handle == NULL) {
        return OMNI_FAIL;
    }

    // Reset the I2C bus
    /*  SW reset procedure:
     *  PE must be kept low during at least 3 APB clock cycles
     *  in order to perform the software reset.
     *  This is ensured by writing the following software sequence:
     *  - Write PE=0
     *  - Check PE=0
     *  - Write PE=1.
     */
    handle->Instance->CR1 &=  ~I2C_CR1_PE;
    while (handle->Instance->CR1 & I2C_CR1_PE) {
    }

    handle->Instance->CR1 |=  I2C_CR1_PE;

    return OMNI_OK;
}
