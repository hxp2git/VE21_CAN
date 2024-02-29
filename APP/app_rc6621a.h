/* 
 * File:   app_bluetooth.h
 * Author: Administrator
 *
 * Created on September 2, 2023, 9:06 AM
 */

#ifndef APP_BLUETOOTH_H
#define	APP_BLUETOOTH_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif


typedef struct
{
    
}AppBluetoothStruct;

void AppRc6621aInit(void);
void AppRc6621aTask(void);
void Rc6621aSignalTxProcess(void);
void Rc6621aSignalRxProcess(void);
#ifdef	__cplusplus
}
#endif

#endif	/* APP_BLUETOOTH_H */

