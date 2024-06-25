/**
  * @file    omni_serial.cpp
  * @author  MorroMaker
  * @brief   Serial driver for OmniOS
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
#include "drivers/include/serial.h"
#include "platform.h"
#include "assert.h"

namespace omni {

    /**
     * @brief Initialize the serial port
     * @param obj: Serial handle structure
     * @retval true: success
     *         false: fail
     */
    bool Serial::init(serial_t obj) {
        if(serial->init(&obj)) {
            _serial = obj;
            return true;
        }

        return false;
    }

    /**
     * @brief Deinitialize the serial port
     * @param obj: Serial handle structure
     * @retval true: success
     *         false: fail
     */
    bool Serial::free() {
        if(serial->deinit(&_serial)) {
            _is_initialized = false;
            return true;
        }

        return false;
    }

    /**
     * @brief Write data to the serial port
     * @param data: Data to write
     * @param size: Size of data
     * @param timeout: Timeout in ms
     * @retval true: success
     *         false: fail
     */
    bool Serial::write(uint8_t *data, uint16_t size, uint32_t timeout) {
        if(serial->write(&_serial, data, size, timeout)) {
            return true;
        }

        return false;
    }

    /**
     * @brief Read data from the serial port
     * @param data: Data buffer
     * @param size: Size of data
     * @param timeout: Timeout in ms
     * @retval true: success
     *         false: fail
     */
    bool Serial::read(uint8_t *data, uint16_t size, uint32_t timeout) {
        if(serial->read(&_serial, data, size, timeout)) {
            return true;
        }

        return false;
    }

} // namespace omni
