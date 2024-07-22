/**
  * @file    omni_version.h
  * @author  MorroMaker
  * @brief   Version information for Omni
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
#ifndef OMNI_VERSION_H
#define OMNI_VERSION_H

#define OMNI_VER_MAJOR                               0
#define OMNI_VER_MINOR                               2
#define OMNI_VER_PATCH                               0
#define OMNI_VER                                     (OMNI_VER_MAJOR * 10000 + OMNI_VER_MINOR * 100 + OMNI_VER_PATCH)
#define OMNI_STR(x)                                  #x
#define OMNI_PROJECT_VERSION(major, minor, patch)    "v" APP_STR(major, minor, patch)

#endif /* OMNI_VERSION_H */
