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

add_subdirectory(target_f405rg)

include(../../../../tools/cmake/omni_set_linker_script.cmake)
include(../../../../tools/cmake/omni_get_subdirectories.cmake)

set(STARTUP_FILE toolchain/gcc/startup_apm32f405xx.s)
set(LINKER_FILE toolchain/gcc/apm32f405xg_flash.ld)

add_library(omni-apm32f405xx INTERFACE)

target_include_directories(omni-apm32f405xx INTERFACE
    .
)

target_sources(omni-apm32f405xx INTERFACE
    ${STARTUP_FILE}
)

if(${OMNI_TARGET} STREQUAL "apm32f405xx")
    if(NOT ${OMNI_LINKER_SCRIPT} STREQUAL "custom")
        omni_set_linker_script(omni-apm32f405xx ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_FILE})
    endif()

    # Get all subdirectories
    omni_get_subdirectories(${CMAKE_CURRENT_SOURCE_DIR} OMNI_BOARDS)

    # Check if the board is supported
    list(FIND OMNI_BOARDS ${OMNI_BOARD} BOARD_INDEX)

    if(${BOARD_INDEX} GREATER -1)
        # message(STATUS "${OMNI_BOARD} is in the list.")
        set(BOARD_TYPE "omni-apm32f405xx-${OMNI_BOARD}")
    else()
        # Output all supported boards
        message("---------- Supported Board ----------")
        foreach(board ${OMNI_BOARDS})
            message(STATUS "${board}")
        endforeach()
        message(FATAL_ERROR "Board ${OMNI_BOARD} is not supported.")
    endif()

    target_link_libraries(omni-apm32f405xx INTERFACE
        ${BOARD_TYPE}
    )
endif()
