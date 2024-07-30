# Omni

[![Version](https://img.shields.io/github/v/release/MorroGeek/omni)](https://github.com/MorroGeek/omni/releases/latest)
[![License](https://img.shields.io/github/license/MorroGeek/omni)](https://github.com/MorroGeek/omni/blob/main/LICENSE)

The Omni Project is a framework that uses CMake and Kconfig to manage a variety of middleware and libraries. It includes the Hardware Abstraction Layer (HAL) and driver layer interfaces, as well as tools for unit testing. It includes:

- CMake Management: Utilizes CMake for project dependency management and build system.
- HAL and Driver Layers: Provides support for hardware abstraction layer and driver layer.
- Unit Testing: Integrates a unit testing framework to ensure code reliability.
- Kconfig Configuration: Uses Kconfig for project configuration management.


## Directory Structure

| Directory                          | Content                                                      |
| :--------------------------------- | :----------------------------------------------------------- |
| [omni/boards](./boards)            | Board definitions and configurations                         |
| [omni/cmsis](./cmsis)              | CMSIS headers                                                |
| [omni/components](./components)    | Components                                                   |
| [omni/docs](./docs)                | User guide                                                   |
| [omni/drivers](./drivers)          | Drivers                                                      |
| [omni/hal](./hal)                  | Hardware abstraction layer                                   |
| [omni/libraries](./libraries)      | Third-party libraries                                        |
| [omni/targets](./targets)          | Target device HAL drivers, startup files, and linker scripts |
| [omni/tests](./tests)              | Test programs                                                |
| [omni/tools](./tools)              | Tools for building and flashing                              |

## Supported Platforms

| Platform      | Device                                                |
| :------------ | :---------------------------------------------------- |
| APM32F4       | APM32F405RG, APM32F407RG                              |
| STM32F4       | STM32F405xG, STM32F407xG                              |

## Dependencies

- [CMake](https://cmake.org/)
- [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm)
- [Ruby](https://www.ruby-lang.org/en/)
- [Ceedling](https://github.com/ThrowTheSwitch/Ceedling)
- [Python](https://www.python.org/)

## Getting Started

Clone the repository and initialize the submodules. Then build the project using the make command.

```bash
git clone

cd omni

git submodule update --init --recursive

make
```

## Other rlated Github repositories

- [Omni-FreeRTOS](https://github.com/MorroGeek/freertos) - FreeRTOS library for Omni
- [Omni-CherryUSB](https://github.com/MorroGeek/cherryusb) - CherryUSB library for Omni
- [Omni-LetterShell](https://github.com/MorroGeek/letter_shell) - LetterShell library for Omni

## License

Omni is provided under the [![License](https://img.shields.io/github/license/MorroGeek/omni?label)](https://github.com/MorroGeek/omni/blob/main/LICENSE) Contributions to this project are accepted under the same license. 

This project contains code from other projects. The original license text is included in those source files. 