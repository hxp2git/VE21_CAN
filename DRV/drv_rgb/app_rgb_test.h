/* 
 * File:   app_rgb.h
 * Author: Administrator
 *
 * Created on 2023年8月11日, 下午4:32
 */

#ifndef APP_RGB_H
#define	APP_RGB_H

#ifdef	__cplusplus
extern "C" {
#endif

#define RGB_NUM_MAX     18
//void AppRgbSetData(TRgbDataBufUnion dat, uint8_t num);
void AppRgbInit(void);
void AppRgbTask(void);
enum TRgbStateTag{
    kSetRgbDataInit = 0,
    kSetRgbDataInit1,
    kSetRgbDataInit2,
    kSetRgbDataInit3,
    kRunRgb,
};
typedef enum TRgbStateTag TRgbStateEnum;


#ifdef	__cplusplus
}
#endif
void AppRgbSetMode(uint8_t mode);
void AppRgbSetBreathingState(uint8_t state);
void AppRgbSetBreathingSwitch(uint8_t mode);
void AppRgbSetModeSwitch(uint8_t sw);
void AppRgbSetLightStripSwitch(uint8_t sw);
void AppRgbSetLightStripMode(uint8_t mode);
void AppRgbSetLightStripEffect(uint8_t effect);
void AppRgbSetLightStripRhythm(uint8_t rhythm);
void AppRgbSetStripData(uint8_t *buf, uint8_t len);
void AppRgbSetRightData(uint8_t *buf, uint8_t len);
void AppRgbSetLeftData(uint8_t *buf, uint8_t len);
extern uint8_t g_srtip_receive_buf[];
extern uint8_t g_left_receive_buf[];
extern uint8_t g_right_receive_buf[];
#endif	/* APP_RGB_H */

