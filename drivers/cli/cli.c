/**
  * @file    cli.c
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

/* Includes ------------------------------------------------------------------*/
#include "drivers/cli/cli.h"
#include "drivers/assert.h"

#if defined(CONFIG_OMNI_DRIVERS_CLI)

/**
 * @brief CLI driver data
 */
typedef struct cli_driver_data {
    void *buffer;                       /**< CLI buffer */
    bool is_initiated;
} cli_driver_data_t;

typedef struct {
    cli_hal_context_t hal_context;      /**< CLI HAL context */
    cli_driver_data_t driver_data;     /**< CLI driver data */
} cli_obj_t;

static cli_obj_t *p_cli_obj[CLI_NUM_MAX];

static int cli_open(cli_num_t cli_num, cli_driver_config_t *config);
static int cli_close(cli_num_t cli_num);
static int cli_start(cli_num_t cli_num);

struct cli_driver_api cli_driver = {
    .open = cli_open,
    .close = cli_close,
    .start = cli_start,
};

/**
 * @brief Open CLI
 * 
 * @param cli_num CLI number
 * @param config Pointer to CLI driver configuration structure
 * @return Operation status
 */
static int cli_open(cli_num_t cli_num, cli_driver_config_t *config) {
    int res;

    p_cli_obj[cli_num] = (cli_obj_t *)malloc(sizeof(cli_obj_t));
    if (p_cli_obj[cli_num] == NULL) {
        return OMNI_FAIL;
    }

    p_cli_obj[cli_num]->driver_data.buffer = malloc(config->buffer_size);
    if (p_cli_obj[cli_num]->driver_data.buffer == NULL) {
        return OMNI_FAIL;
    }

    p_cli_obj[cli_num]->hal_context.dev.shell = config->shell;
    p_cli_obj[cli_num]->hal_context.dev.log = config->log;

    p_cli_obj[cli_num]->hal_context.cli_num = cli_num;
    p_cli_obj[cli_num]->hal_context.buffer = p_cli_obj[cli_num]->driver_data.buffer;

    p_cli_obj[cli_num]->hal_context.buffer_size = config->buffer_size;

    res = cli_hal.shell_init(&p_cli_obj[cli_num]->hal_context);
    if (res != OMNI_OK) {
        OMNI_FREE(p_cli_obj[cli_num]->driver_data.buffer);
        OMNI_FREE(p_cli_obj[cli_num]);
        p_cli_obj[cli_num] = NULL;
        return res;
    }

    if (config->log->active) {
        res = cli_hal.log_init(&p_cli_obj[cli_num]->hal_context);
        if (res != OMNI_OK) {
            OMNI_FREE(p_cli_obj[cli_num]->driver_data.buffer);
            OMNI_FREE(p_cli_obj[cli_num]);
            p_cli_obj[cli_num] = NULL;
            return res;
        }
    }

    return OMNI_OK;
}

/**
 * @brief Close CLI
 * 
 * @param cli_num CLI number
 * @return Operation status
 */
static int cli_close(cli_num_t cli_num) {
    int res;

    res = cli_hal.shell_deinit(&p_cli_obj[cli_num]->hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    if (p_cli_obj[cli_num]->hal_context.dev.log->active) {
        res = cli_hal.log_deinit(&p_cli_obj[cli_num]->hal_context);
        if (res != OMNI_OK) {
            return res;
        }
    }

    if (p_cli_obj[cli_num]->driver_data.buffer != NULL) {
        OMNI_FREE(p_cli_obj[cli_num]->driver_data.buffer);
        p_cli_obj[cli_num]->driver_data.buffer = NULL;
    }

    if (p_cli_obj[cli_num] != NULL) {
        OMNI_FREE(p_cli_obj[cli_num]);
        p_cli_obj[cli_num] = NULL;
    }

    return OMNI_OK;
}

/**
 * @brief Start CLI driver
 * 
 * @param cli_num CLI port number
 * @return Operation status
 */
static int cli_start(cli_num_t cli_num) {
    int res;

    res = cli_hal.shell_enable(&p_cli_obj[cli_num]->hal_context);
    if (res != OMNI_OK) {
        return res;
    }

    return OMNI_OK;
}

#endif /* CONFIG_OMNI_DRIVERS_CLI */
