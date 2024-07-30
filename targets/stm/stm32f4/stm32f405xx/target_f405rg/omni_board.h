/**
  * @file    omni_board.h
  * @author  MorroMaker
  * @brief   Target board definitions for omni
  * @attention
  *
  * Copyright (c) 2024 MorroMaker
  * All rights reserved.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef OMNI_BOARD_H
#define OMNI_BOARD_H

/* Includes ------------------------------------------------------------------*/
#include "omni_target.h"

/**
 * @brief GPIO number
 */
typedef enum {
    GPIO_NUM_PA0 = 0x00,
    GPIO_NUM_PA1 = 0x01,
    GPIO_NUM_PA2 = 0x02,
    GPIO_NUM_PA3 = 0x03,
    GPIO_NUM_PA4 = 0x04,
    GPIO_NUM_PA5 = 0x05,
    GPIO_NUM_PA6 = 0x06,
    GPIO_NUM_PA7 = 0x07,
    GPIO_NUM_PA8 = 0x08,
    GPIO_NUM_PA9 = 0x09,
    GPIO_NUM_PA10 = 0x0A,
    GPIO_NUM_PA11 = 0x0B,
    GPIO_NUM_PA12 = 0x0C,
    GPIO_NUM_PA13 = 0x0D,
    GPIO_NUM_PA14 = 0x0E,
    GPIO_NUM_PA15 = 0x0F,

    GPIO_NUM_PB0 = 0x10,
    GPIO_NUM_PB1 = 0x11,
    GPIO_NUM_PB2 = 0x12,
    GPIO_NUM_PB3 = 0x13,
    GPIO_NUM_PB4 = 0x14,
    GPIO_NUM_PB5 = 0x15,
    GPIO_NUM_PB6 = 0x16,
    GPIO_NUM_PB7 = 0x17,
    GPIO_NUM_PB8 = 0x18,
    GPIO_NUM_PB9 = 0x19,
    GPIO_NUM_PB10 = 0x1A,
    GPIO_NUM_PB11 = 0x1B,
    GPIO_NUM_PB12 = 0x1C,
    GPIO_NUM_PB13 = 0x1D,
    GPIO_NUM_PB14 = 0x1E,
    GPIO_NUM_PB15 = 0x1F,

    GPIO_NUM_PC0 = 0x20,
    GPIO_NUM_PC1 = 0x21,
    GPIO_NUM_PC2 = 0x22,
    GPIO_NUM_PC3 = 0x23,
    GPIO_NUM_PC4 = 0x24,
    GPIO_NUM_PC5 = 0x25,
    GPIO_NUM_PC6 = 0x26,
    GPIO_NUM_PC7 = 0x27,
    GPIO_NUM_PC8 = 0x28,
    GPIO_NUM_PC9 = 0x29,
    GPIO_NUM_PC10 = 0x2A,
    GPIO_NUM_PC11 = 0x2B,
    GPIO_NUM_PC12 = 0x2C,
    GPIO_NUM_PC13 = 0x2D,
    GPIO_NUM_PC14 = 0x2E,
    GPIO_NUM_PC15 = 0x2F,

    GPIO_NUM_PD2 = 0x32,

    GPIO_NUM_PH0 = 0x70,
    GPIO_NUM_PH1 = 0x71,

    GPIO_NUM_MAX,

    /* Debug pins */
    SYS_JTCK_SWCLK = GPIO_NUM_PA14,
    SYS_JTDI = GPIO_NUM_PA15,
    SYS_JTDO_SWO = GPIO_NUM_PB3,
    SYS_JTMS_SWDIO = GPIO_NUM_PA13,
    SYS_JTRST = GPIO_NUM_PB4,
    SYS_WKUP1 = GPIO_NUM_PA0,

    /* OSC clock */
    RCC_OSC_IN = GPIO_NUM_PH0,
    RCC_OSC_OUT = GPIO_NUM_PH1,
    RCC_OSC32_IN = GPIO_NUM_PC14,
    RCC_OSC32_OUT = GPIO_NUM_PC15,

    /* ADC internal channels */
    ADC_TEMP = 0xF0,
    ADC_VREF = 0xF1,
    ADC_VBAT = 0xF2,

    /* USB FS */
    USB_OTG_FS_DP = GPIO_NUM_PA12,
    USB_OTG_FS_DM = GPIO_NUM_PA11,
    USB_OTG_FS_ID = GPIO_NUM_PA10,
    USB_OTG_FS_VBUS = GPIO_NUM_PA9,
    USB_OTG_FS_SOF = GPIO_NUM_PA8,

    /* USB HS */
    USB_OTG_HS_DP = GPIO_NUM_PB15,
    USB_OTG_HS_DM = GPIO_NUM_PB14,
    USB_OTG_HS_ID = GPIO_NUM_PB12,
    USB_OTG_HS_VBUS = GPIO_NUM_PB13,
    USB_OTG_HS_SOF = GPIO_NUM_PB11,

    GPIO_NUM_NC = 0xFFFFFFFF
} gpio_num_t;

#endif /* OMNI_BOARD_H */
