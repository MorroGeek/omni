/**
  * @file    omni_spi.cpp
  * @author  MorroMaker
  * @brief   SPI driver for OmniOS
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
#include "omni_spi.h"

namespace omni {

    /**
     * @brief Initialize the SPI bus
     * @param obj: SPI handle structure
     * @retval true: success
     *         false: fail
     */
    bool SPI::init(spi_t obj) {
        if (spi_init(&obj)) {
            _is_initialized = true;
            return true;
        }

        return false;
    }

    /**
     * @brief Deinitialize the SPI bus
     * @param obj: SPI handle structure
     * @retval true: success
     *         false: fail
     */
    bool SPI::free() {
        if (spi_deinit(&_spi)) {
            _is_initialized = false;
            return true;
        }

        return false;
    }

    /**
     * @brief Write data to the SPI bus
     * @param data: data to write
     * @param size: size of data
     * @param timeout: timeout in ms
     * @retval true: success
     *         false: fail
     */
    bool SPI::write(uint8_t *data, uint16_t size, uint32_t timeout) {
        if (spi_write(&_spi, data, size, timeout)) {
            return true;
        }

        return false;
    }

    /**
     * @brief Read data from the SPI bus
     * @param data: data to read
     * @param size: size of data
     * @param timeout: timeout in ms
     * @retval true: success
     *         false: fail
     */
    bool SPI::read(uint8_t *data, uint16_t size, uint32_t timeout) {
        if (spi_read(&_spi, data, size, timeout)) {
            return true;
        }

        return false;
    }

    /**
     * @brief Transfer data to and from the SPI bus
     * @param txData: data to write
     * @param rxData: data to read
     * @param size: size of data
     * @param timeout: timeout in ms
     * @retval true: success
     *         false: fail
     */
    bool SPI::transfer(uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout) {
        if (spi_transfer(&_spi, txData, rxData, size, timeout)) {
            return true;
        }

        return false;
    }

} // namespace omni
