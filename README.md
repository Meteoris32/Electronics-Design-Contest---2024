# 2024大学生电子竞赛H题 - 循迹小车项目

## 项目简介

本项目是为2024年大学生电子竞赛H题设计的循迹小车。该小车使用灰度传感器进行赛道循迹，旨在完成比赛的四个小题。

## 硬件平台

*   **主控芯片:** MSPM0G3507
*   **传感器:** 灰度传感器 (Grayscale Sensor)
*   **电机驱动:** L298N
*   **其他:** OLED 屏幕

## 软件框架

*   **开发环境:** Keil uVision
*   **编程语言:** C
*   **主要模块:**
    *   **`board.c/board.h`**:  板级支持包，提供底层硬件初始化和驱动。
    *   **`BSP/`**:  包含所有板级支持代码
        *   **`as5600.c/as5600.h`**: AS5600 磁编码器驱动 (如果使用)。
        *   **`bsp_mpu6050.c/bsp_mpu6050.h`**: MPU6050 IMU 驱动 (如果使用)。
        *   **`control.c/control.h`**:  控制算法实现，例如PID控制。
        *   **`Delay.c/Delay.h`**:  延时函数。
        *   **`grayscale.c/gw_grayscale_sensor.h`**: 灰度传感器驱动。
        *   **`motor.c/motor.h`**:  电机驱动。
        *   **`pid.c/pid.h`**:  PID 控制器实现。
        *   **`soft_timer.c/soft_timer.h`**: 软件定时器。
        *   **`struct_typedef.h`**:  结构体定义。
        *   **`eMPL/`**:  InvenSense eMPL 库 (如果使用MPU6050)。
        *   **`IMU/`**:  IMU 相关代码。
    *   **`ndrivers/`**:  外设驱动
        *   **`drv_i2c.c/drv_i2c.h`**: I2C 驱动。
        *   **`drv_oled.c/drv_oled.h`**: OLED 屏幕驱动。
        *   **`drv_spi.c/drv_spi.h`**: SPI 驱动。
        *   **`ssd1306.c/ssd1306.h`**: SSD1306 OLED 屏幕驱动。
    *   **`ti/`**:  TI 提供的 DriverLib 库。
        *   **`ti_msp_dl_config.c/ti_msp_dl_config.h`**: TI DriverLib 配置。
    *   **`empty.c`**: 主函数入口。

## 比赛模式

代码中包含四个模式，分别对应比赛内容的四个小题：

1.  **模式一:**  小车放在 A 点，自动行驶到 B 点停车，有声光提示，用时不大于 15 秒。(20 分)
2.  **模式二:**  小车放在 A 点，自动行驶到 B 点后，沿半弧线行驶到 C 点，再由 C 点自动行驶到 D 点，最后沿半弧线行驶到 A 点停车,每经过一个点声光提示一次。完成一圈用时不大于 30 秒。(20 分)
3.  **模式三:**  小车放在 A 点，自动行驶到 C 点后，沿半弧线行驶到 B 点，再由 B 点自动行驶到 D 点，最后沿半弧线行驶到 A 点停车。每经过一个点声光提示一次。完成一圈用时不大于 40 秒。(30 分)
4.  **模式四:**  按要求3的路径自动行驶4圈停车，用时越少越好 (30分)

## 使用说明

1.  使用 Keil uVision 打开 `keil/empty_LP_MSPM0G3507_nortos_keil.uvprojx` 工程。
2.  配置硬件连接，确保灰度传感器、电机、OLED屏幕等硬件连接正确。
3.  选择对应的比赛模式，修改 `empty.c` 中的代码。
4.  编译并下载程序到 MSPM0G3507 开发板。
5.  将小车放置在赛道上，观察循迹效果。

## 注意事项

*   请根据实际硬件连接修改代码中的引脚配置。
*   PID 参数需要根据实际情况进行调整，以达到最佳循迹效果。
*   比赛时请注意赛道规则，避免违规行为。
*   小车尺寸不大于 25cm (长) X15cm (宽)  15cm(高)。
*   小车行驶时只能前进，不得后退。
*   小车上不得安装摄像头。
*   测试时，应允许相关人员在场地外围走动。
*   启动、停车及行驶经过 A、B、C、D 点时，小车的地面投影必须覆盖圆弧顶点;小车所有在圆弧上的行驶过程，其投影必须在弧线上，投影脱离圆弧即认为此次测试失败，此项目不得分。
*   所有测试项目如果完成时间超过规定时间一倍以上时，此项目不得分。
*   小车采用车载电池供电。进入测试环节，中途不得更换电池。

## 目录结构

```
├── board.c
├── board.h
├── empty.c
├── empty.syscfg
├── Event.dot
├── README.md
├── ti_msp_dl_config.c
├── ti_msp_dl_config.h
├── BSP/
│   ├── as5600.c
│   ├── as5600.h
│   ├── bsp_mpu6050.c
│   ├── bsp_mpu6050.h
│   ├── control.c
│   ├── control.h
│   ├── Delay.c
│   ├── Delay.h
│   ├── grayscale.c
│   ├── gw_grayscale_sensor.h
│   ├── motor.c
│   ├── motor.h
│   ├── pid.c
│   ├── pid.h
│   ├── soft_timer.c
│   ├── soft_timer.h
│   ├── struct_typedef.h
│   ├── eMPL/
│   │   ├── dmpKey.h
│   │   ├── dmpmap.h
│   │   ├── inv_mpu_dmp_motion_driver.c
│   │   ├── inv_mpu_dmp_motion_driver.h
│   │   ├── inv_mpu.c
│   │   └── inv_mpu.h
│   └── IMU/
│       ├── IMU.c
│       ├── IMU.h
│       ├── MPU6050_Reg.h
│       ├── mpu6050.c
│       ├── mpu6050.h
│       ├── MyI2C.c
│       └── MyI2C.h
├── keil/
│   ├── empty_LP_MSPM0G3507_nortos_keil.uvguix.w'p'j
│   ├── empty_LP_MSPM0G3507_nortos_keil.uvoptx
│   ├── empty_LP_MSPM0G3507_nortos_keil.uvprojx
│   ├── EventRecorderStub.scvd
│   ├── mspm0g3507.sct
│   └── startup_mspm0g350x_uvision.s
├── ndrivers/
│   ├── binary.h
│   ├── drv_i2c.c
│   ├── drv_i2c.h
│   ├── drv_oled.c
│   ├── drv_oled.h
│   ├── drv_spi.c
│   ├── drv_spi.h
│   ├── glcdfont.c
│   ├── ssd1306.c
│   └── ssd1306.h
└── ti/
    ├── dl_adc12.c
    ├── dl_adc12.h
    ├── dl_aes.c
    ├── dl_aes.h
    ├── dl_aesadv.c
    ├── dl_aesadv.h
    ├── dl_common.c
    ├── dl_common.h
    ├── dl_comp.h
    ├── dl_crc.c
    ├── dl_crc.h
    ├── dl_crcp.c
    ├── dl_crcp.h
    ├── dl_dac12.c
    ├── dl_dac12.h
    ├── dl_dma.c
    ├── dl_dma.h
    ├── dl_flashctl.c
    ├── dl_flashctl.h
    ├── dl_gpamp.h
    ├── dl_gpio.h
    ├── dl_i2c.c
    ├── dl_i2c.h
    ├── dl_iwdt.h
    ├── dl_keystorectl.c
    ├── dl_keystorectl.h
    ├── dl_lcd.c
    ├── dl_lcd.h
    ├── dl_lfss.c
    ├── dl_lfss.h
    ├── dl_mathacl.c
    ├── dl_mathacl.h
    ├── dl_mcan.c
    ├── dl_mcan.h
    ├── dl_opa.c
    ├── dl_opa.h
    ├── dl_rtc_a.h
    ├── dl_rtc_common.c
    ├── dl_rtc_common.h
    ├── dl_rtc.h
    ├── dl_scratchpad.h
    ├── dl_spi.c
    ├── dl_spi.h
    ├── dl_tamperio.h
    ├── dl_timer.c
    ├── dl_timer.h
    ├── dl_timera.h
    ├── dl_timerg.h
    ├── dl_trng.c
    ├── dl_trng.h
    ├── dl_uart_extend.h
    ├── dl_uart_main.h
    ├── dl_uart.c
    └── dl_uart.h
