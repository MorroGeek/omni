/**
  * @file    omni_i2c.cpp
  * @author  MorroMaker
  * @brief   I2C driver for OmniOS
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
#include "drivers/include/i2c.h"
#include "platform.h"
#include "assert.h"

namespace omni {

    /**
     * @brief Initialize the I2C bus
     * @param obj: I2C handle structure
     * @retval true: success
     *         false: fail
     */
    bool I2C::init(i2c_t obj) {
        if(i2c->init(&obj)) {
            _is_initialized = true;
            return true;
        }

        return false;
    }

    /**
     * @brief Deinitialize the I2C bus
     * @param obj: I2C handle structure
     * @retval true: success
     *         false: fail
     */
    bool I2C::free() {
        if(i2c->deinit(&_i2c)) {
            _is_initialized = false;
            return true;
        }

        return false;
    }

    // TODO: Add recovery functions

    /**
     * @brief Write data to the I2C bus
     * @param address: I2C device address
     * @param data: Data buffer
     * @param size: Data size
     * @param timeout: Timeout
     * @retval true: success
     *         false: fail
     */
    bool I2C::write(uint16_t address, uint8_t *data, uint16_t size, uint32_t timeout) {
        if (!_is_initialized) {
            return false;
        }

        return i2c->write(&_i2c, address, data, size, timeout);
    }

    /**
     * @brief Read data from the I2C bus
     * @param address: I2C device address
     * @param data: Data buffer
     * @param size: Data size
     * @param timeout: Timeout
     * @retval true: success
     *         false: fail
     */
    bool I2C::read(uint16_t address, uint8_t *data, uint16_t size, uint32_t timeout) {
        if (!_is_initialized) {
            return false;
        }

        return i2c->read(&_i2c, address, data, size, timeout);
    }

    /*
     * @brief  Listen I2C
     * @param  size: size of data
     * @retval true: success
     *         false: fail
     * @note   This function is used for I2C slave
     */
    bool I2C::listen(uint16_t size) {
        eeprom_info.size = size;
        // Allocate memory
        eeprom_info.data = new uint8_t[size];
        eeprom_info.cache = new uint8_t[size];

        return i2c->listen(&_i2c);
    }

    /**
     * @brief Stop listening on the I2C bus
     * @retval true: success
     *         false: fail
     */
    bool I2C::listen_stop() {
        memset(&eeprom_info, 0, sizeof(eeprom_info));

        if (eeprom_info.data != nullptr) {
            delete[] eeprom_info.data;
        }

        if (eeprom_info.cache != nullptr) {
            delete[] eeprom_info.cache;
        }

        return (i2c->listen_stop(&_i2c));
    }

} // namespace omni
