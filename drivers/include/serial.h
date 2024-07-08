/**
  * @file    serial.h
  * @author  MorroMaker
  * @brief   Serial class for Omni
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
#ifndef OMNI_handle_H
#define OMNI_handle_H

/* Includes ------------------------------------------------------------------*/
#include "hal/serial_hal.h"

namespace omni {
class Serial {
 public:
    Serial(pin_name_t tx,
            pin_name_t rx,
            int baud_rate = 115200);

    explicit Serial(serial_t obj) : _handle(obj) {}

    virtual ~Serial() {}

    // Get the serial driver APIs
    struct serial_driver_api *serial = serial_driver();

    void *get_handle() { return _handle.serial.handle; }

    bool init(serial_t obj);
    bool free();
    bool write(uint8_t *data, uint16_t size, uint32_t timeout);
    bool read(uint8_t *data, uint16_t size, uint32_t timeout);
    void attach(void (*func)(void), uint32_t id);

 private:
    serial_t _handle;  // Serial handle structure
    bool _is_initialized = false;
};  // class Serial
}  // namespace omni

#endif /* OMNI_handle_H */
