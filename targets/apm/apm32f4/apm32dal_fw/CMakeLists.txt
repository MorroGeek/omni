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

add_library(omni-apm32f4dal-fw INTERFACE)

file(GLOB APM32F4DAL_FW_SOURCES
    "APM32F4xx_DAL_Driver/Source/*.c"
)

target_sources(omni-apm32f4dal-fw INTERFACE
    ${APM32F4DAL_FW_SOURCES}
)

target_include_directories(omni-apm32f4dal-fw INTERFACE
    APM32F4xx_DAL_Driver/Include
    APM32F4xx_DAL_Driver/Include/Legacy
    CMSIS/Device/Geehy/APM32F4xx/Include
)
