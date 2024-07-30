/**
  * @file    cli_hal.c
  * @author  MorroMaker
  * @brief   CLI HAL for STM32
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
#include "hal/cli_hal.h"

static int cli_hal_shell_init(cli_hal_context_t *context);
static int cli_hal_shell_deinit(cli_hal_context_t *context);
static int cli_hal_shell_enable(cli_hal_context_t *context);
static int cli_hal_log_init(cli_hal_context_t *context);
static int cli_hal_log_deinit(cli_hal_context_t *context);

const struct cli_hal_api cli_hal = {
    .shell_init = cli_hal_shell_init,
    .shell_deinit = cli_hal_shell_deinit,
    .shell_enable = cli_hal_shell_enable,
    .log_init = cli_hal_log_init,
    .log_deinit = cli_hal_log_deinit,
};

/**
 * @brief Initialize shell
 * 
 * @param context Pointer to CLI HAL context
 * @return Operation status
 */
static int cli_hal_shell_init(cli_hal_context_t *context) {
    // Initialize shell
    shellInit(context->dev.shell, context->buffer, context->buffer_size);

    context->is_initiated = true;

    return OMNI_OK;
}

static int cli_hal_shell_deinit(cli_hal_context_t *context) {
    // Deinitialize shell
    shellDeInit(context->dev.shell);

    context->is_initiated = false;

    return OMNI_OK;
}

/**
 * @brief Enable shell
 * 
 * @param context Pointer to CLI HAL context
 * @return Operation status
 */
static int cli_hal_shell_enable(cli_hal_context_t *context) {
    // Run shell
    shellTask(context->dev.shell);

    return OMNI_OK;
}

/**
 * @brief Initialize log
 * 
 * @param context Pointer to CLI HAL context
 * @return Operation status
 */
static int cli_hal_log_init(cli_hal_context_t *context) {
    // Register log function
#if defined(CONFIG_SHELL_SUPPORT_END_LINE)
    logRegister(context->dev.log, context->dev.shell);
#else
    logRegister(context->dev.log, NULL);
#endif /* CONFIG_SHELL_SUPPORT_END_LINE */

    return OMNI_OK;
}

/**
 * @brief Deinitialize log
 * 
 * @param context Pointer to CLI HAL context
 * @return Operation status
 */
static int cli_hal_log_deinit(cli_hal_context_t *context) {
    // Unregister log function
    logUnRegister(context->dev.log);

    return OMNI_OK;
}
