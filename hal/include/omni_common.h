/**
  * @file    omni_common.h
  * @author  MorroMaker
  * @brief   Header for omni_common.c file
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
#ifndef OMNI_COMMON_H
#define OMNI_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include "omni_board.h"

/* Exported defines ----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/**
 * @brief Pin map structure
 */
typedef struct {
    pin_name_t pin;
    uint32_t peripheral;
    union {

        struct {
            uint32_t mode       : 4;
            uint32_t dir        : 2;
            uint32_t speed      : 2;
            uint32_t alternate  : 4;
            uint32_t channel    : 5;
            uint32_t inverted   : 1;
            uint32_t status     : 1;
            uint32_t reserved   : 13;
        } feature;

        uint32_t _feature;
    };
} pin_map_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* OMNI_COMMON_H */
