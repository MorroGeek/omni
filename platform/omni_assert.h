/**
  * @file    omni_assert.h
  * @author  MorroMaker
  * @brief   Assert functions for OmniOS
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
#ifndef OMNI_ASSERT_H
#define OMNI_ASSERT_H

/* Includes ------------------------------------------------------------------*/
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

#define USE_OMNI_ASSERT

/**
 * @brief Assert function for OmniOS
 * @param expr: The expression to be evaluated
 * @param file: The file name where the assert function is called
 * @param line: The line number where the assert function is called
 */
void omni_assert(const char *expr, const char *file, int line);

#ifdef USE_OMNI_ASSERT
#define OMNI_ASSERT(expr) ((expr) ? (void)0 : omni_assert(#expr, __FILE__, __LINE__))
#else
#define OMNI_ASSERT(expr) ((void)0)
#endif /* USE_OMNI_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* OMNI_ASSERT_H */
