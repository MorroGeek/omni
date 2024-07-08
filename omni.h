/**
  * @file    omni.h
  * @author  MorroMaker
  * @brief   Omni header file
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
/* Omni drivers */
#include "drivers/include/cli.h"
#include "drivers/include/digital.h"
#include "drivers/include/serial.h"
#include "drivers/include/i2c.h"
#include "drivers/include/spi.h"

/* Omni utilities */
#include "utilities/command/command.h"
#include "utilities/ring_buffer/ring_buffer.h"

/* Exported defines ----------------------------------------------------------*/
using namespace omni;

#ifndef UNUSED
#define UNUSED(X) (void)X
#endif /* UNUSED */

#endif /* OMNI_H */
