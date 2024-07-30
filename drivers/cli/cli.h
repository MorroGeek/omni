/**
  * @file    cli.h
  * @author  MorroMaker
  * @brief   CLI driver for omni
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
#ifndef OMNI_DRIVERS_CLI_H
#define OMNI_DRIVERS_CLI_H

/* Includes ------------------------------------------------------------------*/
#include "hal/cli_hal.h"

#if defined(CONFIG_OMNI_DRIVERS_CLI)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CLI driver configuration
 */
typedef struct cli_driver_config {
    cli_shell_t *shell;
    cli_log_t *log;
    uint32_t buffer_size;
} cli_driver_config_t;

/**
 * @brief Open CLI driver
 */
typedef int (*cli_open_t)(cli_num_t cli_num, cli_driver_config_t *config);

/**
 * @brief Close CLI driver
 */
typedef int (*cli_close_t)(cli_num_t cli_num);

/**
 * @brief Start CLI driver
 */
typedef int (*cli_start_t)(cli_num_t cli_num);

/**
 * @brief Stop CLI driver
 */
typedef int (*cli_stop_t)(cli_num_t cli_num);

/**
 * @brief CLI driver API
 */
struct cli_driver_api {
    cli_open_t open;
    cli_close_t close;
    cli_start_t start;
};

extern struct cli_driver_api cli_driver;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CONFIG_OMNI_DRIVERS_CLI */

#endif /* OMNI_DRIVERS_CLI_H */
