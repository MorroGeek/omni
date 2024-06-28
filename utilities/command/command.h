/**
  * @file    command.h
  * @author  MorroMaker
  * @brief   Provide a class to implement command
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
#ifndef OMNI_COMMAND_H
#define OMNI_COMMAND_H

/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#include <cstddef>
/* Exported defines ----------------------------------------------------------*/
#define CMD_STX         0xA0
#define CMD_TYPE_REQ    0x00
#define CMD_TYPE_ACK    0x01
/* Command Format ------------------------------------------------------------
 *  | 0x00 | 0x01 | 0x02 | 0x03 | 0x04 | ... | 0xNN | 0x00 |
 *  |------|------|------|------|------|-----|------|------|
 *  | STX  | CMD  | LEN_H | LEN_L | DAT  | ... | DAT  | CheckSum |
 *  e.g.
 *  Host  => STX: A0, CMD: 01, LEN: 03, DAT: 01 02 03, CheckSum
 *  Slave <= STX: A1, CMD: 01, LEN: 03, DAT: 01 02 03, CheckSum
 *  --------------------------------------------------------------------------*/
/*
 * @brief  Command class
 */
namespace omni {
    class Command {

    public:
        /**
         * @brief  Constructor
         */
        Command() : _command(0), _length(0), _data(nullptr), _checksum(0), _type(CMD_TYPE_REQ)
        {
        }

        uint8_t rev_complete = 0;

        uint8_t get_type() { return _type; }
        uint8_t get_command() { return _command; }
        uint8_t get_length() { return _length; }
        uint8_t *get_data() { return _data; }
        uint8_t get_checksum() { return _checksum; }

        bool set(uint8_t type, uint8_t command, uint16_t length, uint8_t *data);
        bool parse(uint8_t *data, size_t size);
        uint8_t calculate_checksum();

    private:

        uint8_t _type;
        uint8_t _command;
        uint16_t _length;
        uint8_t *_data;
        uint8_t _checksum;
    };
} // namespace omni

#endif /* OMNI_COMMAND_H */
