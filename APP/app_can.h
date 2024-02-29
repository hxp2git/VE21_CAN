#ifndef __APP_CAN_H_
#define __APP_CAN_H_

#include "OsekNm.h"
#include "Com.h"
#include "can.h"
#include "CanIf.h"
#include "CanTp.h"
#include "CanTrcv.h"
#include "demm.h"
#include "Ccp.h"
#include "Dcm.h"
#include "app_demm.h"

void AppCanInit(void);
void AppCanTask5ms(void);
void AppCanTask10ms(void);

typedef struct
{
    uint8_t pms_drive_mode_ind;             ///< ECO信号 指示灯信号
    uint8_t pms_sliding_momentr_set_req;    ///< 能量回收 指示灯信号
    uint8_t pms_epedal_active;              ///< 单踏板指示灯信号
    uint8_t ehb_pata_response;              ///< ECO OFF指示灯信号
    uint8_t bcm_front_fog_light_sts;        ///< 前雾灯指示灯信号
    uint8_t pms_v2x_dcha_swt_fb1;           ///< V2L 指示灯信号

}AppCanReceiveDataStruct;
extern AppCanReceiveDataStruct g_app_can_receive_data;
#endif

