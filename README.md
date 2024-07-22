# Omni

[![Version](https://img.shields.io/github/v/release/MorroGeek/omni)](https://github.com/MorroGeek/omni/releases/latest)
[![License](https://img.shields.io/github/license/MorroGeek/omni)](https://github.com/MorroGeek/omni/blob/main/LICENSE)

The Omni Project stands as a robust framework, adeptly utilizing CMake to orchestrate a diverse suite of middleware and libraries. It seamlessly integrates HAL and driver layer functionalities, bolstered by comprehensive frameworks for unit testing and sophisticated Kconfig configuration management. It includes:

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