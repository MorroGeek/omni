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

add_subdirectory(stm)
add_subdirectory(apm)

add_library(omni-targets INTERFACE)

if(${OMNI_PLATFORM} STREQUAL "stm")
    target_link_libraries(omni-targets INTERFACE
        omni-stm
    )
endif()

file(GLOB OMNI_TARGET_SOURCES "*.c")

target_sources(omni-targets INTERFACE
    ${OMNI_TARGET_SOURCES}
)

target_include_directories(omni-targets INTERFACE
    .
)