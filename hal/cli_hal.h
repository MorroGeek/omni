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
#ifndef OMNI_CLI_HAL_H
#define OMNI_CLI_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "targets/device.h"
#include "hal/common.h"

#include "libraries/letter_shell/include/shell.h"
#include "libraries/letter_shell/extensions/log/log.h"

struct cli_s {
    Shell *shell;
    Log *log;
};

// Alias for log functions
#define log_error       logError
#define log_warning     logWarning
#define log_info        logInfo
#define log_debug       logDebug

/**
 * @brief CLI handle structure
 */
typedef struct {
    struct cli_s cli;
    void (*init_callback)();
} cli_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_CLI_HAL_H */
