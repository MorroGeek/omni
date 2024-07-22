/**
  * @file    command.c
  * @author  MorroMaker
  * @brief   Command component for omni
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
#include "components/command/command.h"

#if defined(CONFIG_OMNI_COMPONENTS_COMMAND)

static uint8_t calculate_checksum(command_t *cmd);

static int cmd_init(command_t *cmd, uint8_t stx, uint16_t size);
static int cmd_deinit(command_t *cmd);
static int cmd_set_packet(command_t *cmd, command_type_t cmd_type, uint8_t cmd_index, uint8_t *packet_data, uint16_t data_size);
static int cmd_parse_packet(command_t *cmd, uint8_t *data, uint16_t length);

struct command_api command = {
    .init = cmd_init,
    .deinit = cmd_deinit,
    .set_packet = cmd_set_packet,
    .parse_packet = cmd_parse_packet,
};

/**
 * @brief Initialize the command
 * 
 * @param cmd Pointer to the command
 * @param stx Start index of the command
 * @param size Size of the buffer
 * @return Operation status
 */
static int cmd_init(command_t *cmd, uint8_t stx, uint16_t size) {
    cmd->packet.data = (uint8_t *)OMNI_MALLOC(size * sizeof(uint8_t));
    if (cmd->packet.data == NULL) {
        return OMNI_FAIL;
    }

    cmd->packet.stx = stx;
    cmd->packet.data_size = 0;

    return OMNI_OK;
}

/**
 * @brief Deinitialize the command
 * 
 * @param cmd Pointer to the command
 * @return Operation status
 */
static int cmd_deinit(command_t *cmd) {
    if (cmd->packet.data != NULL) {
        OMNI_FREE(cmd->packet.data);
        cmd->packet.data = NULL;
    }

    cmd->packet.stx = 0;
    cmd->packet.cmd_type = 0;
    cmd->packet.cmd_index = 0;
    cmd->packet.data_size = 0;
    cmd->packet.checksum = 0;

    return OMNI_OK;
}

/**
 * @brief Set command packet
 * 
 * @param cmd Pointer to the command
 * @param cmd_type Command type
 * @param cmd_index Command index
 * @param packet_data Pointer to the packet data
 * @param data_size Size of data
 * @return Operation status
 */
static int cmd_set_packet(command_t *cmd, command_type_t cmd_type, \
                          uint8_t cmd_index, uint8_t *packet_data, uint16_t data_size) {
    cmd->packet.cmd_type = cmd_type;
    cmd->packet.cmd_index = cmd_index;
    cmd->packet.data_size = data_size;
    if (packet_data != NULL) {
        for (uint16_t i = 0; i < data_size; i++) {
            cmd->packet.data[i] = packet_data[i];
        }
    }
    cmd->packet.checksum = calculate_checksum(cmd);

    return OMNI_OK;
}

/**
 * @brief Parse command packet
 * 
 * @param cmd Pointer to the command
 * @param data Pointer to the packet data
 * @param length Length of data
 * @return Operation status
 */
static int cmd_parse_packet(command_t *cmd, uint8_t *data, uint16_t length) {
    if (length < CMD_MIN_LENGTH) {
        return OMNI_FAIL;
    }

    if (data[0] != cmd->packet.stx) {
        return OMNI_FAIL;
    }

    cmd->packet.cmd_index = data[1];
    cmd->packet.data_size = data[2] << 8 | data[3];

    if (cmd->packet.data_size != 0) {
        for (uint16_t i = 0; i < cmd->packet.data_size; i++) {
            cmd->packet.data[i] = data[CMD_MIN_LENGTH + i];
        }
    }
    cmd->packet.checksum = data[CMD_MIN_LENGTH + cmd->packet.data_size];

    if (cmd->packet.checksum != calculate_checksum(cmd)) {
        return OMNI_FAIL;
    }

    return OMNI_OK;
}

/**
 * @brief Calculate command packet checksum
 * 
 * @param cmd Pointer to the command
 * @return Checksum
 */
static uint8_t calculate_checksum(command_t *cmd) {
    uint8_t checksum = 0;

    checksum ^= cmd->packet.stx;
    checksum ^= cmd->packet.cmd_index;
    checksum ^= cmd->packet.data_size >> 8;
    checksum ^= cmd->packet.data_size & 0xFF;

    if (cmd->packet.data != NULL) {
        for (uint16_t i = 0; i < cmd->packet.data_size; i++) {
            checksum ^= cmd->packet.data[i];
        }
    }

    return checksum;
}

#endif /* CONFIG_OMNI_COMPONENTS_COMMAND */
