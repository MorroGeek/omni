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
#include <stdarg.h>
#include "hal/cli_hal.h"

namespace omni {
template<typename T, size_t SIZE>
class CLI {
 public:
    /**
     * @brief Construct a new CLI object
     *
     * @param shell: shell object
     */

    explicit CLI(Shell *shell) {
        _handle.cli.shell = shell;
        _handle.cli.log = nullptr;

        // The initialization of CLI should be completed after driver initialization
    }

    CLI(Shell *shell, Log *log) {
        _handle.cli.shell = shell;
        _handle.cli.log = log;

        // The initialization of CLI should be completed after driver initialization
    }

    /**
     * @brief Destroy the CLI object
     */
    virtual ~CLI() {
    }

    bool get_initialized() {
        return _is_initialized;
    }

    bool init() {
        // Initialize the shell
        shellInit(_handle.cli.shell, _data, SIZE);

        // Register the log
        if (_handle.cli.log != nullptr) {
#if SHELL_SUPPORT_END_LINE == 1
            logRegister(_handle.cli.log, _handle.cli.shell);
    #else
            logRegister(_handle.cli.log, nullptr);
#endif
        }

        _is_initialized = true;

        return true;
    }

    bool deinit() {
        if (!_is_initialized) {
            return false;
        }

        shellRemove(_handle.cli.shell);

        if (_handle.cli.log != nullptr) {
            logUnRegister(_handle.cli.log);
        }

        _is_initialized = false;

        return true;
    }

    bool run() {
        if (_is_initialized) {
            shellTask(_handle.cli.shell);
        }

        return true;
    }

    bool set_log_level(LogLevel level) {
        if (!_is_initialized) {
            return false;
        }

        _handle.cli.log->level = level;

        return true;
    }

 private:
    cli_t _handle{};
    T _data[SIZE];
    bool _is_initialized = false;
};  // class CLI
}  // namespace omni

#endif /* OMNI_CLI_H */
