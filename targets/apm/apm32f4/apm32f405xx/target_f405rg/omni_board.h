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

    PD2 = 0x32,
    PH0 = 0x70,
    PH1 = 0x71,

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
    OMNI_PWM1 = TMR1_BASE,
    OMNI_PWM2 = TMR2_BASE,
    OMNI_PWM3 = TMR3_BASE,
    OMNI_PWM4 = TMR4_BASE,
    OMNI_PWM5 = TMR5_BASE,
    OMNI_PWM6 = TMR6_BASE,
    OMNI_PWM7 = TMR7_BASE,
    OMNI_PWM8 = TMR8_BASE,
    OMNI_PWM9 = TMR9_BASE,
    OMNI_PWM10 = TMR10_BASE,
    OMNI_PWM11 = TMR11_BASE,
    OMNI_PWM12 = TMR12_BASE,
    OMNI_PWM13 = TMR13_BASE,
    OMNI_PWM14 = TMR14_BASE,
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
    OMNI_USB_HS2 = USB_OTG_HS2_PERIPH_BASE,
} usb_name_t;

/**
 * @brief GPIO handle structure
 */
typedef struct {
    GPIO_TypeDef *ins;
    uint32_t pin;
} gpio_t;

#endif /* OMNI_BOARD_H */
