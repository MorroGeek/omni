/**
  * @file    omni_config.h
  * @author  MorroMaker
  * @brief   Omni configuration file
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
#ifndef OMNI_CONFIG_H
#define OMNI_CONFIG_H

#include <stdlib.h>

#include "omni/omni_kconfig.h"

#ifndef OMNI_MALLOC
#define OMNI_MALLOC malloc
#endif /* OMNI_MALLOC */

#ifndef OMNI_FREE
#define OMNI_FREE free
#endif /* OMNI_FREE */

#ifndef UNUSED
#define UNUSED(X) (void)X
#endif /* UNUSED */

#endif /* OMNI_CONFIG_H */
