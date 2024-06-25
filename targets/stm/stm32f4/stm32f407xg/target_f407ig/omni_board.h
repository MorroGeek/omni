/**
  * @file    omni_board.h
  * @author  MorroMaker
  * @brief   Header for omni_board.c file
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
#include "targets.h"
/* Exported defines ----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/

/**
 * @brief  Pin name type definition
 */
typedef enum {
    PA0 = 0x00,
    PA1 = 0x01,
    PA2 = 0x02,
    PA3 = 0x03,
    PA4 = 0x04,
    PA5 = 0x05,
    PA6 = 0x06,
    PA7 = 0x07,
    PA8 = 0x08,
    PA9 = 0x09,
    PA10 = 0x0A,
    PA11 = 0x0B,
    PA12 = 0x0C,
    PA13 = 0x0D,
    PA14 = 0x0E,
    PA15 = 0x0F,

    PB0 = 0x10,
    PB1 = 0x11,
    PB2 = 0x12,
    PB3 = 0x13,
    PB4 = 0x14,
    PB5 = 0x15,
    PB6 = 0x16,
    PB7 = 0x17,
    PB8 = 0x18,
    PB9 = 0x19,
    PB10 = 0x1A,
    PB11 = 0x1B,
    PB12 = 0x1C,
    PB13 = 0x1D,
    PB14 = 0x1E,
    PB15 = 0x1F,

    PC0 = 0x20,
    PC1 = 0x21,
    PC2 = 0x22,
    PC3 = 0x23,
    PC4 = 0x24,
    PC5 = 0x25,
    PC6 = 0x26,
    PC7 = 0x27,
    PC8 = 0x28,
    PC9 = 0x29,
    PC10 = 0x2A,
    PC11 = 0x2B,
    PC12 = 0x2C,
    PC13 = 0x2D,
    PC14 = 0x2E,
    PC15 = 0x2F,

    PD0 = 0x30,
    PD1 = 0x31,
    PD2 = 0x32,
    PD3 = 0x33,
    PD4 = 0x34,
    PD5 = 0x35,
    PD6 = 0x36,
    PD7 = 0x37,
    PD8 = 0x38,
    PD9 = 0x39,
    PD10 = 0x3A,
    PD11 = 0x3B,
    PD12 = 0x3C,
    PD13 = 0x3D,
    PD14 = 0x3E,
    PD15 = 0x3F,

    PE0 = 0x40,
    PE1 = 0x41,
    PE2 = 0x42,
    PE3 = 0x43,
    PE4 = 0x44,
    PE5 = 0x45,
    PE6 = 0x46,
    PE7 = 0x47,
    PE8 = 0x48,
    PE9 = 0x49,
    PE10 = 0x4A,
    PE11 = 0x4B,
    PE12 = 0x4C,
    PE13 = 0x4D,
    PE14 = 0x4E,
    PE15 = 0x4F,

    PF0 = 0x50,
    PF1 = 0x51,
    PF2 = 0x52,
    PF3 = 0x53,
    PF4 = 0x54,
    PF5 = 0x55,
    PF6 = 0x56,
    PF7 = 0x57,
    PF8 = 0x58,
    PF9 = 0x59,
    PF10 = 0x5A,
    PF11 = 0x5B,
    PF12 = 0x5C,
    PF13 = 0x5D,
    PF14 = 0x5E,
    PF15 = 0x5F,

    PG0 = 0x60,
    PG1 = 0x61,
    PG2 = 0x62,
    PG3 = 0x63,
    PG4 = 0x64,
    PG5 = 0x65,
    PG6 = 0x66,
    PG7 = 0x67,
    PG8 = 0x68,
    PG9 = 0x69,
    PG10 = 0x6A,
    PG11 = 0x6B,
    PG12 = 0x6C,
    PG13 = 0x6D,
    PG14 = 0x6E,
    PG15 = 0x6F,

    PH0 = 0x70,
    PH1 = 0x71,
    PH2 = 0x72,
    PH3 = 0x73,
    PH4 = 0x74,
    PH5 = 0x75,
    PH6 = 0x76,
    PH7 = 0x77,
    PH8 = 0x78,
    PH9 = 0x79,
    PH10 = 0x7A,
    PH11 = 0x7B,
    PH12 = 0x7C,
    PH13 = 0x7D,
    PH14 = 0x7E,
    PH15 = 0x7F,

    PI0 = 0x80,
    PI1 = 0x81,
    PI2 = 0x82,
    PI3 = 0x83,
    PI4 = 0x84,
    PI5 = 0x85,
    PI6 = 0x86,
    PI7 = 0x87,
    PI8 = 0x88,
    PI9 = 0x89,
    PI10 = 0x8A,
    PI11 = 0x8B,

    /* Debug pins */
    SYS_JTCK_SWCLK = PA14,
    SYS_JTDI = PA15,
    SYS_JTDO_SWO = PB3,
    SYS_JTMS_SWDIO = PA13,
    SYS_JTRST = PB4,
    SYS_WKUP1 = PA0,

    /* OSC clock */
    RCC_OSC_IN = PH0,
    RCC_OSC_OUT = PH1,
    RCC_OSC32_IN = PC14,
    RCC_OSC32_OUT = PC15,

    /* ADC internal channels */
    ADC_TEMP = 0xF0,
    ADC_VREF = 0xF1,
    ADC_VBAT = 0xF2,

    /* USB FS */
    USB_OTG_FS_DP = PA12,
    USB_OTG_FS_DM = PA11,
    USB_OTG_FS_ID = PA10,
    USB_OTG_FS_VBUS = PA9,
    USB_OTG_FS_SOF = PA8,

    /* USB HS */
    USB_OTG_HS_DP = PB15,
    USB_OTG_HS_DM = PB14,
    USB_OTG_HS_ID = PB12,
    USB_OTG_HS_VBUS = PB13,
    USB_OTG_HS_SOF = PB11,

    NC = (int)0xFFFFFFFF
} pin_name_t;

/**
 * @brief  ADC name type definition
 */
typedef enum
{
    OMNI_ADC1 = ADC1_BASE,
    OMNI_ADC2 = ADC2_BASE,
    OMNI_ADC3 = ADC3_BASE,
} adc_name_t;

/**
 * @brief  CAN name type definition
 */
typedef enum
{
    OMNI_CAN1 = CAN1_BASE,
    OMNI_CAN2 = CAN2_BASE,
} can_name_t;

/**
 * @brief  DAC name type definition
 */
typedef enum
{
    OMNI_DAC1 = DAC_BASE,
} dac_name_t;

/**
 * @brief  I2C name type definition
 */
typedef enum
{
    OMNI_I2C1 = I2C1_BASE,
    OMNI_I2C2 = I2C2_BASE,
    OMNI_I2C3 = I2C3_BASE,
} i2c_name_t;

/**
 * @brief  I2S name type definition
 */
typedef enum
{
    OMNI_I2S2 = I2S2ext_BASE,
    OMNI_I2S3 = I2S3ext_BASE,
} i2s_name_t;

/**
 * @brief  SDIO name type definition
 */
typedef enum
{
    OMNI_SDIO1 = SDIO_BASE,
} sdio_name_t;

/**
 * @brief  SPI name type definition
 */
typedef enum
{
    OMNI_SPI1 = SPI1_BASE,
    OMNI_SPI2 = SPI2_BASE,
    OMNI_SPI3 = SPI3_BASE,
} spi_name_t;

/**
 * @brief  PWM name type definition
 */
typedef enum
{
    OMNI_PWM1 = TIM1_BASE,
    OMNI_PWM2 = TIM2_BASE,
    OMNI_PWM3 = TIM3_BASE,
    OMNI_PWM4 = TIM4_BASE,
    OMNI_PWM5 = TIM5_BASE,
    OMNI_PWM6 = TIM6_BASE,
    OMNI_PWM7 = TIM7_BASE,
    OMNI_PWM8 = TIM8_BASE,
    OMNI_PWM9 = TIM9_BASE,
    OMNI_PWM10 = TIM10_BASE,
    OMNI_PWM11 = TIM11_BASE,
    OMNI_PWM12 = TIM12_BASE,
    OMNI_PWM13 = TIM13_BASE,
    OMNI_PWM14 = TIM14_BASE,
} pwm_name_t;

/**
 * @brief  UART name type definition
 */
typedef enum
{
    OMNI_UART1 = USART1_BASE,
    OMNI_UART2 = USART2_BASE,
    OMNI_UART3 = USART3_BASE,
    OMNI_UART4 = UART4_BASE,
    OMNI_UART5 = UART5_BASE,
    OMNI_UART6 = USART6_BASE,
} uart_name_t;

/**
 * @brief  USB name type definition
 */
typedef enum
{
    OMNI_USB_FS = USB_OTG_FS_PERIPH_BASE,
    OMNI_USB_HS = USB_OTG_HS_PERIPH_BASE,
} usb_name_t;

/**
 * @brief GPIO handle structure
 */
typedef struct {
    GPIO_TypeDef *ins;
    uint32_t pin;
} gpio_t;

#endif /* OMNI_BOARD_H */
