/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM_Motor */
#define PWM_Motor_INST                                                     TIMA0
#define PWM_Motor_INST_IRQHandler                               TIMA0_IRQHandler
#define PWM_Motor_INST_INT_IRQN                                 (TIMA0_INT_IRQn)
#define PWM_Motor_INST_CLK_FREQ                                         32000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_Motor_C0_PORT                                             GPIOB
#define GPIO_PWM_Motor_C0_PIN                                     DL_GPIO_PIN_14
#define GPIO_PWM_Motor_C0_IOMUX                                  (IOMUX_PINCM31)
#define GPIO_PWM_Motor_C0_IOMUX_FUNC                 IOMUX_PINCM31_PF_TIMA0_CCP0
#define GPIO_PWM_Motor_C0_IDX                                DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_Motor_C1_PORT                                             GPIOA
#define GPIO_PWM_Motor_C1_PIN                                      DL_GPIO_PIN_3
#define GPIO_PWM_Motor_C1_IOMUX                                   (IOMUX_PINCM8)
#define GPIO_PWM_Motor_C1_IOMUX_FUNC                  IOMUX_PINCM8_PF_TIMA0_CCP1
#define GPIO_PWM_Motor_C1_IDX                                DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 2 */
#define GPIO_PWM_Motor_C2_PORT                                             GPIOA
#define GPIO_PWM_Motor_C2_PIN                                      DL_GPIO_PIN_7
#define GPIO_PWM_Motor_C2_IOMUX                                  (IOMUX_PINCM14)
#define GPIO_PWM_Motor_C2_IOMUX_FUNC                 IOMUX_PINCM14_PF_TIMA0_CCP2
#define GPIO_PWM_Motor_C2_IDX                                DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_PWM_Motor_C3_PORT                                             GPIOA
#define GPIO_PWM_Motor_C3_PIN                                      DL_GPIO_PIN_4
#define GPIO_PWM_Motor_C3_IOMUX                                   (IOMUX_PINCM9)
#define GPIO_PWM_Motor_C3_IOMUX_FUNC                  IOMUX_PINCM9_PF_TIMA0_CCP3
#define GPIO_PWM_Motor_C3_IDX                                DL_TIMER_CC_3_INDEX

/* Defines for Servo */
#define Servo_INST                                                         TIMA1
#define Servo_INST_IRQHandler                                   TIMA1_IRQHandler
#define Servo_INST_INT_IRQN                                     (TIMA1_INT_IRQn)
#define Servo_INST_CLK_FREQ                                              1000000
/* GPIO defines for channel 0 */
#define GPIO_Servo_C0_PORT                                                 GPIOA
#define GPIO_Servo_C0_PIN                                         DL_GPIO_PIN_15
#define GPIO_Servo_C0_IOMUX                                      (IOMUX_PINCM37)
#define GPIO_Servo_C0_IOMUX_FUNC                     IOMUX_PINCM37_PF_TIMA1_CCP0
#define GPIO_Servo_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_Servo_C1_PORT                                                 GPIOB
#define GPIO_Servo_C1_PIN                                          DL_GPIO_PIN_1
#define GPIO_Servo_C1_IOMUX                                      (IOMUX_PINCM13)
#define GPIO_Servo_C1_IOMUX_FUNC                     IOMUX_PINCM13_PF_TIMA1_CCP1
#define GPIO_Servo_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                            (39U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_0_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_9
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_8
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM20)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM19)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM19_PF_UART1_TX
#define UART_1_BAUD_RATE                                                (115200)
#define UART_1_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_1_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_3 */
#define UART_3_INST                                                        UART3
#define UART_3_INST_IRQHandler                                  UART3_IRQHandler
#define UART_3_INST_INT_IRQN                                      UART3_INT_IRQn
#define GPIO_UART_3_RX_PORT                                                GPIOB
#define GPIO_UART_3_TX_PORT                                                GPIOB
#define GPIO_UART_3_RX_PIN                                         DL_GPIO_PIN_3
#define GPIO_UART_3_TX_PIN                                         DL_GPIO_PIN_2
#define GPIO_UART_3_IOMUX_RX                                     (IOMUX_PINCM16)
#define GPIO_UART_3_IOMUX_TX                                     (IOMUX_PINCM15)
#define GPIO_UART_3_IOMUX_RX_FUNC                      IOMUX_PINCM16_PF_UART3_RX
#define GPIO_UART_3_IOMUX_TX_FUNC                      IOMUX_PINCM15_PF_UART3_TX
#define UART_3_BAUD_RATE                                                (115200)
#define UART_3_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_3_FBRD_4_MHZ_115200_BAUD                                       (11)
/* Defines for UART_2 */
#define UART_2_INST                                                        UART2
#define UART_2_INST_IRQHandler                                  UART2_IRQHandler
#define UART_2_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_2_RX_PORT                                                GPIOA
#define GPIO_UART_2_TX_PORT                                                GPIOA
#define GPIO_UART_2_RX_PIN                                        DL_GPIO_PIN_22
#define GPIO_UART_2_TX_PIN                                        DL_GPIO_PIN_21
#define GPIO_UART_2_IOMUX_RX                                     (IOMUX_PINCM47)
#define GPIO_UART_2_IOMUX_TX                                     (IOMUX_PINCM46)
#define GPIO_UART_2_IOMUX_RX_FUNC                      IOMUX_PINCM47_PF_UART2_RX
#define GPIO_UART_2_IOMUX_TX_FUNC                      IOMUX_PINCM46_PF_UART2_TX
#define UART_2_BAUD_RATE                                                (115200)
#define UART_2_IBRD_4_MHZ_115200_BAUD                                        (2)
#define UART_2_FBRD_4_MHZ_115200_BAUD                                       (11)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI1
#define SPI_0_INST_IRQHandler                                   SPI1_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI1_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOB
#define GPIO_SPI_0_PICO_PIN                                      DL_GPIO_PIN_15
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM32)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM32_PF_SPI1_PICO
#define GPIO_SPI_0_POCI_PORT                                              GPIOA
#define GPIO_SPI_0_POCI_PIN                                      DL_GPIO_PIN_16
#define GPIO_SPI_0_IOMUX_POCI                                   (IOMUX_PINCM38)
#define GPIO_SPI_0_IOMUX_POCI_FUNC                   IOMUX_PINCM38_PF_SPI1_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOA
#define GPIO_SPI_0_SCLK_PIN                                      DL_GPIO_PIN_17
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM39)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM39_PF_SPI1_SCLK



/* Port definition for Pin Group BEEP */
#define BEEP_PORT                                                        (GPIOA)

/* Defines for beep: GPIOA.27 with pinCMx 60 on package pin 31 */
#define BEEP_beep_PIN                                           (DL_GPIO_PIN_27)
#define BEEP_beep_IOMUX                                          (IOMUX_PINCM60)
/* Port definition for Pin Group Encoder */
#define Encoder_PORT                                                     (GPIOB)

/* Defines for PIN_0: GPIOB.4 with pinCMx 17 on package pin 52 */
// pins affected by this interrupt request:["PIN_0","PIN_1","PIN_2","PIN_3"]
#define Encoder_INT_IRQN                                        (GPIOB_INT_IRQn)
#define Encoder_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define Encoder_PIN_0_IIDX                                   (DL_GPIO_IIDX_DIO4)
#define Encoder_PIN_0_PIN                                        (DL_GPIO_PIN_4)
#define Encoder_PIN_0_IOMUX                                      (IOMUX_PINCM17)
/* Defines for PIN_1: GPIOB.5 with pinCMx 18 on package pin 53 */
#define Encoder_PIN_1_IIDX                                   (DL_GPIO_IIDX_DIO5)
#define Encoder_PIN_1_PIN                                        (DL_GPIO_PIN_5)
#define Encoder_PIN_1_IOMUX                                      (IOMUX_PINCM18)
/* Defines for PIN_2: GPIOB.6 with pinCMx 23 on package pin 58 */
#define Encoder_PIN_2_IIDX                                   (DL_GPIO_IIDX_DIO6)
#define Encoder_PIN_2_PIN                                        (DL_GPIO_PIN_6)
#define Encoder_PIN_2_IOMUX                                      (IOMUX_PINCM23)
/* Defines for PIN_3: GPIOB.7 with pinCMx 24 on package pin 59 */
#define Encoder_PIN_3_IIDX                                   (DL_GPIO_IIDX_DIO7)
#define Encoder_PIN_3_PIN                                        (DL_GPIO_PIN_7)
#define Encoder_PIN_3_IOMUX                                      (IOMUX_PINCM24)
/* Port definition for Pin Group key */
#define key_PORT                                                         (GPIOB)

/* Defines for PIN_4: GPIOB.21 with pinCMx 49 on package pin 20 */
#define key_PIN_4_PIN                                           (DL_GPIO_PIN_21)
#define key_PIN_4_IOMUX                                          (IOMUX_PINCM49)
/* Defines for PIN_5: GPIOB.23 with pinCMx 51 on package pin 22 */
#define key_PIN_5_PIN                                           (DL_GPIO_PIN_23)
#define key_PIN_5_IOMUX                                          (IOMUX_PINCM51)
/* Port definition for Pin Group GPIO */
#define GPIO_PORT                                                        (GPIOA)

/* Defines for SCL: GPIOA.0 with pinCMx 1 on package pin 33 */
#define GPIO_SCL_PIN                                             (DL_GPIO_PIN_0)
#define GPIO_SCL_IOMUX                                            (IOMUX_PINCM1)
/* Defines for SDA: GPIOA.1 with pinCMx 2 on package pin 34 */
#define GPIO_SDA_PIN                                             (DL_GPIO_PIN_1)
#define GPIO_SDA_IOMUX                                            (IOMUX_PINCM2)
/* Port definition for Pin Group GrayScale */
#define GrayScale_PORT                                                   (GPIOA)

/* Defines for CLK: GPIOA.28 with pinCMx 3 on package pin 35 */
#define GrayScale_CLK_PIN                                       (DL_GPIO_PIN_28)
#define GrayScale_CLK_IOMUX                                       (IOMUX_PINCM3)
/* Defines for DAT: GPIOA.31 with pinCMx 6 on package pin 39 */
#define GrayScale_DAT_PIN                                       (DL_GPIO_PIN_31)
#define GrayScale_DAT_IOMUX                                       (IOMUX_PINCM6)
/* Port definition for Pin Group RGB */
#define RGB_PORT                                                         (GPIOB)

/* Defines for R: GPIOB.26 with pinCMx 57 on package pin 28 */
#define RGB_R_PIN                                               (DL_GPIO_PIN_26)
#define RGB_R_IOMUX                                              (IOMUX_PINCM57)
/* Defines for G: GPIOB.27 with pinCMx 58 on package pin 29 */
#define RGB_G_PIN                                               (DL_GPIO_PIN_27)
#define RGB_G_IOMUX                                              (IOMUX_PINCM58)
/* Defines for B: GPIOB.22 with pinCMx 50 on package pin 21 */
#define RGB_B_PIN                                               (DL_GPIO_PIN_22)
#define RGB_B_IOMUX                                              (IOMUX_PINCM50)
/* Port definition for Pin Group AS5600 */
#define AS5600_PORT                                                      (GPIOA)

/* Defines for scl_5600: GPIOA.29 with pinCMx 4 on package pin 36 */
#define AS5600_scl_5600_PIN                                     (DL_GPIO_PIN_29)
#define AS5600_scl_5600_IOMUX                                     (IOMUX_PINCM4)
/* Defines for sda_5600: GPIOA.30 with pinCMx 5 on package pin 37 */
#define AS5600_sda_5600_PIN                                     (DL_GPIO_PIN_30)
#define AS5600_sda_5600_IOMUX                                     (IOMUX_PINCM5)
/* Port definition for Pin Group PORTB */
#define PORTB_PORT                                                       (GPIOB)

/* Defines for RST: GPIOB.16 with pinCMx 33 on package pin 4 */
#define PORTB_RST_PIN                                           (DL_GPIO_PIN_16)
#define PORTB_RST_IOMUX                                          (IOMUX_PINCM33)
/* Defines for DC: GPIOB.17 with pinCMx 43 on package pin 14 */
#define PORTB_DC_PIN                                            (DL_GPIO_PIN_17)
#define PORTB_DC_IOMUX                                           (IOMUX_PINCM43)
/* Defines for CS: GPIOB.20 with pinCMx 48 on package pin 19 */
#define PORTB_CS_PIN                                            (DL_GPIO_PIN_20)
#define PORTB_CS_IOMUX                                           (IOMUX_PINCM48)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_Motor_init(void);
void SYSCFG_DL_Servo_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_UART_3_init(void);
void SYSCFG_DL_UART_2_init(void);
void SYSCFG_DL_SPI_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
