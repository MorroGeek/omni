# Omni

[![Version](https://img.shields.io/github/v/release/MorroGeek/omni)](https://github.com/MorroGeek/omni/releases/latest)
[![License](https://img.shields.io/github/license/MorroGeek/omni)](https://github.com/MorroGeek/omni/blob/main/LICENSE)

Omni is the "Swiss Army Knife" for embedded systems, including a variety of popular libraries and C++-based HAL drivers, all designed for plug-and-play.

## Directory Structure

| Directory                          | Content                                                      |
| :--------------------------------- | :-----------------------------------------------             |
| [omni/cmsis](./cmsis)              | CMSIS headers and startup files                              |
| [omni/docs](./docs)                | User guide                                                   |
| [omni/drivers](./drivers)          | Peripheral drivers                                           |
| [omni/hal](./hal)                  | Hardware abstraction layer                                   |
| [omni/libraries](./libraries)      | Third-party libraries                                        |
| [omni/platform](./platform)        | Platform common files                                        |
| [omni/targets](./targets)          | Target device HAL drivers, startup files, and linker scripts |
| [omni/tools](./tools)              | Tools for building and flashing                              |
| [omni/utilities](./utilities)      | Utility functions                                            |

## Supported Platforms
| Platform      | Device                                                |
| :------------ | :---------------------------------------------------- |
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

## License

Omni is provided under the [![License](https://img.shields.io/github/license/MorroGeek/omni?label)](https://github.com/MorroGeek/omni/blob/main/LICENSE) Contributions to this project are accepted under the same license. 

This project contains code from other projects. The original license text is included in those source files. 