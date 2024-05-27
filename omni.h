/**
  * @file    omni.h
  * @author  MorroMaker
  * @brief   OmniOS header file
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
#ifndef OMNI_H
#define OMNI_H

/* Includes ------------------------------------------------------------------*/
/* OmniOS drivers */
#include "drivers/include/omni_digital.h"
#include "drivers/include/omni_serial.h"
#include "drivers/include/omni_i2c.h"
#include "drivers/include/omni_spi.h"

/* OmniOS utilities */
#include "utilities/command/omni_command.h"
#include "utilities/ring_buffer/omni_ring_buffer.h"

/* Exported defines ----------------------------------------------------------*/
using namespace omni;

#endif /* OMNI_H */
