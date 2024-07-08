/**
  * @file    command.cpp
  * @author  MorroMaker
  * @brief   Command class
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
#include "utilities/command/command.h"

/* Private includes ----------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/

namespace omni {

    /**
     * @brief  Set command
     * @param  type: type
     * @param  command: command
     * @param  length: length of data
     * @param  data: data
     * @retval true: success
     *         false: fail
     */
    bool Command::set(uint8_t type, uint8_t command, uint16_t length, uint8_t *data) {
        _type = type;
        _command = command;
        _length = length;
        _data = data;
        _checksum = calculate_checksum();

        return true;
    }

    /**
     * @brief  Parse command
     * @param  data: buffer to parse
     * @param  size: size of buffer
     * @retval true: success
     *         false: fail
     */
    bool Command::parse(uint8_t *data, size_t size) {
        if (size < 4) {
            return false;
        }

        if (data[0] != CMD_STX) {
            return false;
        }

        _command = data[1];
        _length = data[2] << 8 | data[3];

        if (_length == 0) {
            _data = nullptr;
        } else {
            _data = &data[4];
        }
        _checksum = data[4 + _length];

        if (_checksum != calculate_checksum()) {
            return false;
        }

        return true;
    }

    /**
     * @brief  Calculate check sum
     * @retval check sum
     */
    uint8_t Command::calculate_checksum() {
        uint8_t check_sum = 0;
        check_sum ^= CMD_STX;
        check_sum ^= _command;
        check_sum ^= _length >> 8;
        check_sum ^= _length & 0xFF;
        if (_data != nullptr) {
            for (uint32_t i = 0; i < _length; i++) {
                check_sum ^= _data[i];
            }
        }

        return check_sum;
    }

}  // namespace omni

/* Private functions ---------------------------------------------------------*/
