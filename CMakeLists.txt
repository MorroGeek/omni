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

include(tools/cmake/omni_get_arm_gcc_version.cmake)

project(omni)

if(NOT DEFINED OMNI_PLATFORM)
    set(OMNI_PLATFORM "stm" CACHE STRING "Omni platform")
endif()

if(NOT DEFINED OMNI_CPU)
    set(OMNI_CPU "stm32f405xg" CACHE STRING "Omni CPU")
endif()

if(NOT DEFINED OMNI_BOARD)
    set(OMNI_BOARD "" CACHE STRING "Omni board")
endif()

if(NOT DEFINED OMNI_RTOS)
    set(OMNI_RTOS "freertos" CACHE STRING "Omni RTOS")
endif()

if(NOT DEFINED OMNI_USB)
    set(OMNI_USB "cherryusb" CACHE STRING "Omni USB")
endif()

if(NOT DEFINED OMNI_SHELL)
    set(OMNI_SHELL "letter" CACHE STRING "Omni shell")
endif()

if(NOT DEFINED OMNI_LINKER_SCRIPT)
    set(OMNI_LINKER_SCRIPT "default" CACHE STRING "Omni linker script")
endif()

if(NOT DEFINED ARM_GCC_VERSION)
    set(ARM_GCC_VERSION "10.3.1" CACHE STRING "ARM GCC version")
endif()

message(STATUS "Platform: ${OMNI_PLATFORM}")
message(STATUS "CPU: ${OMNI_CPU}")
message(STATUS "Board: ${OMNI_BOARD}")
message(STATUS "RTOS: ${OMNI_RTOS}")
message(STATUS "USB: ${OMNI_USB}")
message(STATUS "Shell: ${OMNI_SHELL}")
message(STATUS "ARM GCC version: ${ARM_GCC_VERSION}")

# Check ARM GCC version
check_arm_gcc_version(${ARM_GCC_VERSION})

add_library(omni INTERFACE)

add_library(omni-core INTERFACE)
add_library(omni-rtos INTERFACE)

target_link_libraries(omni INTERFACE
        omni-rtos
        omni-core
)

target_include_directories(omni INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(cmsis)
add_subdirectory(drivers)
add_subdirectory(hal)
add_subdirectory(targets)
add_subdirectory(utilities)
add_subdirectory(libraries)

if(OMNI_TEST STREQUAL ON)
    add_subdirectory(test)
endif()

target_link_libraries(omni-core INTERFACE
        omni-cmsis
        omni-drivers
        omni-hal
        omni-targets
        omni-utilities
)

if(OMNI_RTOS STREQUAL "freertos")
    target_link_libraries(omni-rtos INTERFACE
            omni-cmsis-freertos
    )
endif()

if(OMNI_USB STREQUAL "cherryusb")
    target_link_libraries(omni-core INTERFACE
            omni-cherryusb
    )
endif()

if(OMNI_SHELL STREQUAL "letter")
    target_link_libraries(omni-core INTERFACE
        omni-letter-shell
    )
endif()
