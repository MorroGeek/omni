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

add_library(omni-apm32f4 INTERFACE)

# add_subdirectory(stm32cube_fw)

# add_subdirectory(stm32f405xg EXCLUDE_FROM_ALL)
# add_subdirectory(stm32f407xg EXCLUDE_FROM_ALL)

target_include_directories(omni-apm32f4 INTERFACE
        .
)

if(NOT ${OMNI_CPU} STREQUAL "")
    set(CPU_TYPE "omni-${OMNI_CPU}")
else()
    message(FATAL_ERROR "OMNI_CPU is not set")
endif()

target_link_libraries(omni-apm32f4 INTERFACE
    ${CPU_TYPE}
    # omni-stm32f4cube-fw
)
