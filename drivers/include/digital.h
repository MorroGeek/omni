/**
  * @file    digital.h
  * @author  MorroMaker
  * @brief   Digital class for Omni
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
#ifndef OMNI_DIGITAL_H
#define OMNI_DIGITAL_H

/* Includes ------------------------------------------------------------------*/
#include "hal/gpio_hal.h"

namespace omni {
class Digital {
 public:
    /**
     * @brief Construct a new Digital object
     * @param pin: pin name
     * @param dir: direction
     * @param pull: pull
     * @param speed: speed
     * @param inverted: inverted
     * @param value: value
     */
    Digital(pin_name_t pin,
            gpio_dir_t dir,
            gpio_pull_t pull = OMNI_GPIO_PULL_NONE,
            gpio_speed_t speed = OMNI_GPIO_SPEED_LOW,
            gpio_inverted_t inverted = OMNI_GPIO_NONINVERTED,
            gpio_status_t value = OMNI_GPIO_LOW): _handle() {
        uint32_t mode;

        if (pull == OMNI_GPIO_PULL_NONE) {
            mode = OMNI_GPIO_PP_PULLNONE;
        } else if (pull == OMNI_GPIO_PULL_UP) {
            mode = OMNI_GPIO_PP_PULLUP;
        } else {
            mode = OMNI_GPIO_PP_PULLDOWN;
        }

        _pin_map = {
                pin,
                0,
                mode,
                dir,
                speed,
                0,
                0,
                inverted,
                value,
        };

        gpio->init(&_handle, _pin_map);
    }

    /**
     * @brief Destroy the Digital object
     */
    virtual ~Digital() {}

    // Get the GPIO driver APIs
    struct gpio_driver_api *gpio = gpio_driver();

    /**
     * @brief Write a value to the digital pin
     * @param value: value to write
     */
    void write(int value) {
        gpio->write(&_handle, value);
    }

    /**
     * @brief Toggle the digital pin
     */
    void toggle() {
        gpio->toggle(&_handle);
    }

    /**
     * @brief Read the digital pin
     */
    void read(uint32_t *value) {
        gpio->read(&_handle, value);
    }

 private:
    gpio_t _handle{};
    pin_map_t _pin_map{};
};  // class Digital
}  // namespace omni

#endif /* OMNI_DIGITAL_H */
