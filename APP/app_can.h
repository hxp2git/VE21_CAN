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
    uint8_t pms_drive_mode_ind;             ///< ECO�ź� ָʾ���ź�
    uint8_t pms_sliding_momentr_set_req;    ///< �������� ָʾ���ź�
    uint8_t pms_epedal_active;              ///< ��̤��ָʾ���ź�
    uint8_t ehb_pata_response;              ///< ECO OFFָʾ���ź�
    uint8_t bcm_front_fog_light_sts;        ///< ǰ���ָʾ���ź�
    uint8_t pms_v2x_dcha_swt_fb1;           ///< V2L ָʾ���ź�

}AppCanReceiveDataStruct;
extern AppCanReceiveDataStruct g_app_can_receive_data;
#endif

