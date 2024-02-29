/* 
 * File:   app_crc8.h
 * Author: Administrator
 *
 * Created on September 8, 2023, 2:21 PM
 */

#ifndef APP_CRC8_H
#define	APP_CRC8_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>

uint8_t AppCrc8Calc(uint8_t *dat, uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_CRC8_H */

