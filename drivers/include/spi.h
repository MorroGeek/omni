/**
  * @file    spi.h
  * @author  MorroMaker
  * @brief   SPI class for Omni
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
#ifndef OMNI_SPI_H
#define OMNI_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "hal/spi_hal.h"

namespace omni {
class SPI {
 public:
    /**
     * @brief Construct a new SPI object
     *
     * @param spi
     */
    SPI(pin_name_t mosi,
        pin_name_t miso,
        pin_name_t sclk,
        pin_name_t cs,
        int frequency);

    explicit SPI(spi_t obj) : _handle(obj) {}

    /**
     * @brief Destroy the SPI object
     */
    virtual ~SPI() {}

    // Get the SPI driver APIs
    struct spi_driver_api *spi = spi_driver();

    void *get_handle() { return _handle.spi.handle; }

    bool init(spi_t obj);
    bool free();
    bool write(uint8_t *data, uint16_t size, uint32_t timeout);
    bool read(uint8_t *data, uint16_t size, uint32_t timeout);
    bool transfer(uint8_t *txData, uint8_t *rxData, uint16_t size, uint32_t timeout);
    void attach(void (*func)(void), uint32_t id);

 private:
    spi_t _handle{};
    bool _is_initialized = false;
};  // class SPI
}  // namespace omni

#endif /* OMNI_SPI_H */
