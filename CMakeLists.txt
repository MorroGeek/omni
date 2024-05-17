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

project(OmniOS)

message(STATUS "Platform: ${OMNI_PLATFORM}")
message(STATUS "CPU: ${OMNI_CPU}")
message(STATUS "Board: ${OMNI_BOARD}")

add_library(omni-os INTERFACE)

add_library(omni-core INTERFACE)

target_link_libraries(omni-os INTERFACE
        #        omni-rtos
        omni-core
)

target_include_directories(omni-os INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(cmsis)
add_subdirectory(drivers)
add_subdirectory(hal)
add_subdirectory(targets)
add_subdirectory(utilities)

target_link_libraries(omni-core INTERFACE
        omni-cmsis
        omni-drivers
        omni-hal
        omni-targets
        omni-utilities
)

#add_subdirectory(tools)
#add_subdirectory(utils)
