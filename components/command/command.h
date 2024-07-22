/**
  * @file    command.h
  * @author  MorroMaker
  * @brief   command component for omni
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
#ifndef OMNI_COMPONENTS_COMMAND_H
#define OMNI_COMPONENTS_COMMAND_H

/* Includes ------------------------------------------------------------------*/
#include "hal/device.h"

#if defined(CONFIG_OMNI_COMPONENTS_COMMAND)

#ifdef __cplusplus
extern "C" {
#endif

// STX + CMD_INDEX + LEN_H + LEN_L = 4
#define CMD_MIN_LENGTH  4

/**
 * @brief Command type
 */
typedef enum {
    CMD_TYPE_REQ = 0x00,
    CMD_TYPE_ACK = 0x01,
} command_type_t;

/* Command Format ------------------------------------------------------------
 *  | 0x00 | 0x01 | 0x02 | 0x03 | 0x04 | ... | 0xNN | 0x00 |
 *  |------|------|------|------|------|-----|------|------|
 *  | STX  | CMD  | LEN_H | LEN_L | DAT  | ... | DAT  | CheckSum |
 *  e.g.
 *  Host  => STX: A0, CMD: 01, LEN: 03, DAT: 01 02 03, CheckSum
 *  Slave <= STX: A1, CMD: 01, LEN: 03, DAT: 01 02 03, CheckSum
 *  --------------------------------------------------------------------------*/

/**
 * @brief Command packet
 */
typedef struct cmd_packet {
    uint8_t *data;
    uint8_t stx;
    command_type_t cmd_type;
    uint8_t cmd_index;
    uint16_t data_size;
    uint8_t checksum;
} cmd_packet_t;

/**
 * @brief Command component
 */
typedef struct command {
    cmd_packet_t packet;
    bool is_received;
} command_t;

/**
 * @brief Initialize the command
 */
typedef int (*cmd_init_t)(command_t *cmd, uint8_t stx, uint16_t size);

/**
 * @brief Deinitialize the command
 */
typedef int (*cmd_deinit_t)(command_t *cmd);

/**
 * @brief Set command packet
 */
typedef int (*cmd_set_packet_t)(command_t *cmd, command_type_t cmd_type, \
                                uint8_t cmd_index, uint8_t *packet_data, uint16_t data_size);

/**
 * @brief Parse command packet
 */
typedef int (*cmd_parse_packet_t)(command_t *cmd, uint8_t *data, uint16_t length);

/**
 * @brief Command component API
 */
struct command_api {
    cmd_init_t init;
    cmd_deinit_t deinit;
    cmd_set_packet_t set_packet;
    cmd_parse_packet_t parse_packet;
};

extern struct command_api command;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONFIG_OMNI_COMPONENTS_COMMAND */

#endif /* OMNI_COMPONENTS_COMMAND_H */
