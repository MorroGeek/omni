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

include(../../../../tools/cmake/omni_set_linker_script.cmake)
include(../../../../tools/cmake/omni_get_subdirectories.cmake)

set(STARTUP_FILE toolchain/gcc/startup_stm32f407xx.s)
set(LINKER_FILE toolchain/gcc/stm32f407xg_flash.ld)

add_library(omni-stm32f407xg INTERFACE)

target_include_directories(omni-stm32f407xg INTERFACE
        .
)

target_sources(omni-stm32f407xg INTERFACE
        ${STARTUP_FILE}
)

#set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_FILE} CACHE INTERNAL "Linker script")
#
#message(STATUS "Linker script1: ${LINKER_SCRIPT}")

# target_link_options(omni-stm32f407xg INTERFACE
#     -T${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_FILE}
# )

if(${OMNI_CPU} STREQUAL "stm32f407xg")
    omni_set_linker_script(omni-stm32f407xg ${CMAKE_CURRENT_SOURCE_DIR}/${LINKER_FILE})

    # 获取所有子目录
    omni_get_subdirectories(${CMAKE_CURRENT_SOURCE_DIR} OMNI_BOARDS)

    # 检查OMNI_BOARD是否在数组中
    list(FIND OMNI_BOARDS ${OMNI_BOARD} BOARD_INDEX)

    if(${BOARD_INDEX} GREATER -1)
        #    message(STATUS "${OMNI_BOARD} is in the list.")
        set(BOARD_TYPE "omni-stm32f407xg-${OMNI_BOARD}")
    else()
        # 输出结果
        message("---------- Supported Board ----------")
        foreach(board ${OMNI_BOARDS})
            message(STATUS "${board}")
        endforeach()
        message(FATAL_ERROR "Board ${OMNI_BOARD} is not supported.")
    endif()

    target_link_libraries(omni-stm32f407xg INTERFACE
            ${BOARD_TYPE}
    )
endif()
