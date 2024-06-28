/**
  * @file    cli.h
  * @author  MorroMaker
  * @brief   Command Line Interface (CLI) class for Omni
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
#ifndef OMNI_CLI_H
#define OMNI_CLI_H

/* Includes ------------------------------------------------------------------*/
#include "cli_hal.h"

namespace omni {
    template<typename T, size_t SIZE>
    class CLI {

    public:
        /**
         * @brief Construct a new CLI object
         *
         * @param cli
         */
        CLI(cli_t obj) : _cli(obj) {
            _cli = obj;
            //The initialization of CLI should be completed after driver initialization
        }

        /**
         * @brief Destroy the CLI object
         */
        virtual ~CLI()
        {
        }

        bool init()
        {
            shellInit(&_cli.cli, _data, SIZE);
            _is_initialized = true;

            return true;
        }

        bool run()
        {
            if (_is_initialized) {
                shellTask(&_cli.cli);
            }

            return true;
        }

    private:
        cli_t _cli;
        T _data[SIZE];
        bool _is_initialized = false;
    }; // class CLI
} // namespace omni

#endif /* OMNI_CLI_H */
