# Copyright (c) 2024 MorroMaker
# All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_library(omni-stm32f4cube-fw INTERFACE)

file(GLOB SOURCES
    "STM32F4xx_HAL_Driver/Src/*.c"
)

target_sources(omni-stm32f4cube-fw INTERFACE
        ${SOURCES}
)

target_include_directories(omni-stm32f4cube-fw INTERFACE
        STM32F4xx_HAL_Driver/Inc
        STM32F4xx_HAL_Driver/Inc/Legacy
        CMSIS/Device/ST/STM32F4xx/Include
        CMSIS/Include
)
