/**
  * @file    i2c.h
  * @author  MorroMaker
  * @brief   I2C class for Omni
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
#ifndef OMNI_I2C_H
#define OMNI_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "hal/i2c_hal.h"

namespace omni {
class I2C {
 public:
    /**
     * @brief Construct a new I2C object
     *
     * @param i2c
     */
    I2C(pin_name_t sda,
        pin_name_t scl,
        int frequency = 100000);

    explicit I2C(i2c_t obj) : _handle(obj) {}

    /**
     * @brief Destroy the I2C object
     */
    virtual ~I2C() {}

    // Get the I2C driver APIs
    struct i2c_driver_api *i2c = i2c_driver();

    /*
    * @brief  I2C EEPROM structure
    */
    typedef struct {
        uint8_t *data;      // Data buffer
        uint8_t *cache;     // Cache buffer
        uint16_t address;
        uint16_t size;
        __IO uint8_t listen;
        __IO uint8_t tx_complete;
        __IO uint8_t rx_complete;
        __IO uint32_t dir;
        uint32_t error;
        uint32_t rx_index;
    } EEPROM_INFO_T;

    EEPROM_INFO_T eeprom_info{};

    uint32_t get_mode() { return _handle.mode; }
    uint32_t get_address1() { return _handle.address1; }
    uint32_t get_address2() { return _handle.address2; }
    uint32_t get_frequency() { return _handle.frequency; }
    void *get_handle() { return _handle.i2c.handle; }

    bool init(i2c_t obj);
    bool free();
    bool recovery();
    bool write(uint16_t address, uint8_t *data, uint16_t size, uint32_t timeout);
    bool read(uint16_t address, uint8_t *data, uint16_t size, uint32_t timeout);
    bool enable_listen(uint16_t size);
    bool disable_listen();
    void attach(void (*func)(void), uint32_t id);

 private:
    i2c_t _handle{};
    bool _is_initialized = false;
};  // class I2C
}  // namespace omni

#endif /* OMNI_I2C_H */
