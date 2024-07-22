/**
  * @file    cli_types.h
  * @author  MorroMaker
  * @brief   CLI HAL types
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
#ifndef OMNI_HAL_CLI_TYPES_H
#define OMNI_HAL_CLI_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hal/device.h"

#include "libraries/letter_shell/include/shell.h"
#include "libraries/letter_shell/extensions/log/log.h"

typedef Shell cli_shell_t;
typedef Log cli_log_t;
typedef LogLevel cli_log_level_t;

// Alias for log functions
#define log_error       logError
#define log_warning     logWarning
#define log_info        logInfo
#define log_debug       logDebug

/**
 * @brief CLI number
 */
typedef enum {
#ifdef CONFIG_CLI_NUM_1
    CLI_NUM_1 = 0x01,
#endif /* CONFIG_CLI_NUM_1 */
#ifdef CONFIG_CLI_NUM_2
    CLI_NUM_2 = 0x02,
#endif /* CONFIG_CLI_NUM_2 */
    CLI_NUM_MAX,
} cli_num_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* OMNI_HAL_CLI_TYPES_H */
