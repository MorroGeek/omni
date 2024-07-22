/**
  * @file    cli_hal.h
  * @author  MorroMaker
  * @brief   Header for cli_hal.c file
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
#ifndef OMNI_HAL_CLI_H
#define OMNI_HAL_CLI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal/cli_types.h"

typedef struct cli_dev {
    cli_shell_t *shell;
    cli_log_t *log;
} cli_dev_t;

typedef struct cli_hal_context {
    cli_dev_t dev;
    cli_num_t cli_num;
    void *buffer;               /**< Shell buffer */
    uint32_t buffer_size;       /**< Shell buffer size */
    bool is_initiated;
} cli_hal_context_t;

/**
 * @brief CLI controller HAL API structure
 */
struct cli_hal_api {
    int (*shell_init)(cli_hal_context_t *context);
    int (*shell_deinit)(cli_hal_context_t *context);
    // int (*register_command)(cli_hal_context_t *context, const char *command, ShellCommandFunction function, const char *description);
    // int (*unregister_command)(cli_hal_context_t *context, const char *command);
    int (*shell_start)(cli_hal_context_t *context);
    int (*log_init)(cli_hal_context_t *context);
    int (*log_deinit)(cli_hal_context_t *context);
    int (*log_set_level)(cli_hal_context_t *context, cli_log_level_t level);
};

extern const struct cli_hal_api cli_hal;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_CLI_H */
