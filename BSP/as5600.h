#ifndef __as5600_H
#define __as5600_H 

#include "ti_msp_dl_config.h"
//AS5600�ĸߵ͵�ַ
#define	_raw_ang_hi 0x0c
#define	_raw_ang_lo 0x0d
//����SDA���ģʽ
#define SDA_OUT()   {                                                  \
                        DL_GPIO_initDigitalOutput(AS5600_sda_5600_IOMUX);     \
                        DL_GPIO_setPins(AS5600_PORT, AS5600_sda_5600_PIN);      \
                        DL_GPIO_enableOutput(AS5600_PORT, AS5600_sda_5600_PIN); \
                    }
//����SDA����ģʽ
#define SDA_IN()    { DL_GPIO_initDigitalInput(AS5600_sda_5600_IOMUX); }

//��ȡSDA���ŵĵ�ƽ�仯
#define SDA_GET()   ( ( ( DL_GPIO_readPins(AS5600_PORT,AS5600_sda_5600_PIN) & AS5600_sda_5600_PIN ) > 0 ) ? 1 : 0 )
//SDA��SCL���
#define SDA(x)      ( (x) ? (DL_GPIO_setPins(AS5600_PORT,AS5600_sda_5600_PIN)) : (DL_GPIO_clearPins(AS5600_PORT,AS5600_sda_5600_PIN)) )
#define SCL(x)      ( (x) ? (DL_GPIO_setPins(AS5600_PORT,AS5600_scl_5600_PIN)) : (DL_GPIO_clearPins(AS5600_PORT,AS5600_scl_5600_PIN)) )
 uint16_t AS5600_ReadTwoByte();
#endif