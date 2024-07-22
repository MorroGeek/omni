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
#include "omni_target.h"
/* Exported defines ----------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/

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

    GPIO_NUM_PD0 = 0x30,
    GPIO_NUM_PD1 = 0x31,
    GPIO_NUM_PD2 = 0x32,
    GPIO_NUM_PD3 = 0x33,
    GPIO_NUM_PD4 = 0x34,
    GPIO_NUM_PD5 = 0x35,
    GPIO_NUM_PD6 = 0x36,
    GPIO_NUM_PD7 = 0x37,
    GPIO_NUM_PD8 = 0x38,
    GPIO_NUM_PD9 = 0x39,
    GPIO_NUM_PD10 = 0x3A,
    GPIO_NUM_PD11 = 0x3B,
    GPIO_NUM_PD12 = 0x3C,
    GPIO_NUM_PD13 = 0x3D,
    GPIO_NUM_PD14 = 0x3E,
    GPIO_NUM_PD15 = 0x3F,

    GPIO_NUM_PE0 = 0x40,
    GPIO_NUM_PE1 = 0x41,
    GPIO_NUM_PE2 = 0x42,
    GPIO_NUM_PE3 = 0x43,
    GPIO_NUM_PE4 = 0x44,
    GPIO_NUM_PE5 = 0x45,
    GPIO_NUM_PE6 = 0x46,
    GPIO_NUM_PE7 = 0x47,
    GPIO_NUM_PE8 = 0x48,
    GPIO_NUM_PE9 = 0x49,
    GPIO_NUM_PE10 = 0x4A,
    GPIO_NUM_PE11 = 0x4B,
    GPIO_NUM_PE12 = 0x4C,
    GPIO_NUM_PE13 = 0x4D,
    GPIO_NUM_PE14 = 0x4E,
    GPIO_NUM_PE15 = 0x4F,

    GPIO_NUM_PF0 = 0x50,
    GPIO_NUM_PF1 = 0x51,
    GPIO_NUM_PF2 = 0x52,
    GPIO_NUM_PF3 = 0x53,
    GPIO_NUM_PF4 = 0x54,
    GPIO_NUM_PF5 = 0x55,
    GPIO_NUM_PF6 = 0x56,
    GPIO_NUM_PF7 = 0x57,
    GPIO_NUM_PF8 = 0x58,
    GPIO_NUM_PF9 = 0x59,
    GPIO_NUM_PF10 = 0x5A,
    GPIO_NUM_PF11 = 0x5B,
    GPIO_NUM_PF12 = 0x5C,
    GPIO_NUM_PF13 = 0x5D,
    GPIO_NUM_PF14 = 0x5E,
    GPIO_NUM_PF15 = 0x5F,

    GPIO_NUM_PG0 = 0x60,
    GPIO_NUM_PG1 = 0x61,
    GPIO_NUM_PG2 = 0x62,
    GPIO_NUM_PG3 = 0x63,
    GPIO_NUM_PG4 = 0x64,
    GPIO_NUM_PG5 = 0x65,
    GPIO_NUM_PG6 = 0x66,
    GPIO_NUM_PG7 = 0x67,
    GPIO_NUM_PG8 = 0x68,
    GPIO_NUM_PG9 = 0x69,
    GPIO_NUM_PG10 = 0x6A,
    GPIO_NUM_PG11 = 0x6B,
    GPIO_NUM_PG12 = 0x6C,
    GPIO_NUM_PG13 = 0x6D,
    GPIO_NUM_PG14 = 0x6E,
    GPIO_NUM_PG15 = 0x6F,

    GPIO_NUM_PH0 = 0x70,
    GPIO_NUM_PH1 = 0x71,
    GPIO_NUM_PH2 = 0x72,
    GPIO_NUM_PH3 = 0x73,
    GPIO_NUM_PH4 = 0x74,
    GPIO_NUM_PH5 = 0x75,
    GPIO_NUM_PH6 = 0x76,
    GPIO_NUM_PH7 = 0x77,
    GPIO_NUM_PH8 = 0x78,
    GPIO_NUM_PH9 = 0x79,
    GPIO_NUM_PH10 = 0x7A,
    GPIO_NUM_PH11 = 0x7B,
    GPIO_NUM_PH12 = 0x7C,
    GPIO_NUM_PH13 = 0x7D,
    GPIO_NUM_PH14 = 0x7E,
    GPIO_NUM_PH15 = 0x7F,

    GPIO_NUM_PI0 = 0x80,
    GPIO_NUM_PI1 = 0x81,
    GPIO_NUM_PI2 = 0x82,
    GPIO_NUM_PI3 = 0x83,
    GPIO_NUM_PI4 = 0x84,
    GPIO_NUM_PI5 = 0x85,
    GPIO_NUM_PI6 = 0x86,
    GPIO_NUM_PI7 = 0x87,
    GPIO_NUM_PI8 = 0x88,
    GPIO_NUM_PI9 = 0x89,
    GPIO_NUM_PI10 = 0x8A,
    GPIO_NUM_PI11 = 0x8B,
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
