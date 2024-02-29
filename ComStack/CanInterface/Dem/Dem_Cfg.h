#ifndef _DEM_CFG_H_
#define _DEM_CFG_H_

#include "Dcm_Cfg.h"
#include "Dem_types.h"
#include "PduR_Dcm.h"
#include <stdint.h>



#define TOTAL_DTC_NUM  (NUM_OF_DTC)    /*配置 NUM_OF_DTC */
#define DTC_STATUS_USED_MASK  (0x7FU)  /*配置 DTC MASK */
#define DTC_SNAP_SHOT_DATA_ENABLE (STD_ON) /*配置是否支持快照 0: 不使用snap shot data  */
#define DTC_EXTENDED_DATA_ENABLE (0U)  /*配置是否支持擴展數據:0: 不使用EXTENDEDt data  */

#define DEM_DTC_STORAGE_TO_EEPROM_EN  (1)
#define TOTAL_MAX_STORED_DTC_NUM (TOTAL_DTC_NUM)  
#define DTC_TASK_TICK_PER_SEC  (TASK_TICKS_PER_SEC*0.5)  /*配置 CAN TASK PERIOD:100/s   CAN 任務 每秒100次  */
#define DTC_TIME_s(x) ((uint16_t)((x)*DTC_TASK_TICK_PER_SEC))

#define EEPROM_INTIED_FLAG_ADDR             (0x0000)
#define DEM_DTC_STORAGE_EEPROM_START_ADDR   (DTC_EE_FLASH_RAM_START_ADDRESS)

#if (TOTAL_DTC_NUM <253)
typedef uint8_t dtc_handle_t;
#else
typedef uint16_t dtc_handle_t;  
#endif

#define DTC_NO_EXIST     ((dtc_handle_t)(-1))
#define DTC_IS_IN_GROUP  ((dtc_handle_t)(-2))

#define DTC_INIT_FLAG_STORY_TO_EXT_EEPROM
#define DTC_RECORD_STORY_TO_EXT_EEPROM

#define DTC_ALL_GROUPS 			0xFFFFFFu
#define DTC_NETWORK_COMM_GROUPS	0xC00000u
#define DTC_BODY_GROUPS 		0x800000u
#define DTC_CHASSIS_GROUPS 		0x400000u
#define DTC_POWERTRAIN_GROUPS 	0X100000u
#define DTC_EMISSION_GROUPS 	0x000000u


typedef uint16 IntEEPROM1_TAddress; /* Type of address to the EEPROM */


#define EEPROM_UNINITED		     0u
#define EEPROM_INITED	         1u
#define EEPROM_DTC_CLEAR         2u

#define DTC_SET_TIME_FOR_OUTPUT      (80u)   /* 80*10MS = 800mS */
#define DTC_TEST_FAILED              (0u)
#define DTC_TEST_PASSED              (1u)

#define TEST_RESULT_STATE_BIT_LENGTH  (2U)
#define TOTAL_TEST_RESULT_NUM        ((TOTAL_DTC_NUM)/(8/(TEST_RESULT_STATE_BIT_LENGTH)) + 1)

#define TOTAL_DTC_FLAG_NUM                (TOTAL_DTC_NUM / 8 + 1)
//#define DTC_MONITORING_CYCLE_NUM          (TOTAL_STORED_DTC_NUM / 8 + 1)
#define LAST_DTC_INDEX					  (TOTAL_DTC_NUM-1)
#define NO_DTC_STORED_INDEX               (0xffu)



#define TOTAL_DTC_MONITORING_CYCLE        2u
#define DTC_MONITORING_CYCLE2             0u
#define DTC_MONITORING_CYCLE4             1u


#define TOTAL_DTC_SNAP_SHOT_ID_NUM        2u  /* FE-5 4 did */
#define TOTAL_DTC_SNAP_SHOT_STORED_NUM    1u
#define TOTAL_DTC_EXTENDED_DATA_NUM       5u
#define MAX_DTC_AGING_COUNTER_VALUE       40u

#define MIN_DTC_FAULT_DT_CNT_VALUE        16u		/* -128 + 16 */
#define MAX_DTC_FAULT_DT_CNT_VALUE        223u		/* 127 - 32 */
#define DTC_FAULT_DT_CNT_UP_STEP          32u
#define DTC_FAULT_DT_CNT_DOWN_STEP        16u

#define DTC_MONITORING_CYCLE0_MASK        0x01u
#define DTC_MONITORING_CYCLE1_MASK        0x02u
#define DTC_MONITORING_CYCLE2_MASK        0x04u
#define DTC_MONITORING_CYCLE3_MASK        0x08u
#define DTC_MONITORING_CYCLE4_MASK        0x10u

/* Define DTC index  */


#define DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_BCM_ID 		0u /* Loss of communication between MFS and BCM */
#define DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_ICC_ID 		1u /* Loss of communication between MFS and ICC */
#define DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_PEPS_ID 		2u /* Loss of communication between MFS and PEPS */
#define DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_CIM_ID 		3u /* Loss of communication between MFS and CIM */
#define DTC_MFS_NM_LIMPHOME_FAULT_ID 		                    4u /* MFS NM Limphome Fault */
#define DTC_CAN_BUS_COMMUNICATION_FAULT_ID 		                5u /* CAN Bus Communication Fault */
#define DTC_CUSTOM_SWITCH_STUCK_FAILURE_ID                      6u
#define DTC_RETURN_SWITCH_STUCK_FAILURE_ID                      7u
#define DTC_LEFT_SWITCH_STUCK_FAILURE_ID                        8u
#define DTC_RIGHT_SWITCH_STUCK_FAILURE_ID                       9u
#define DTC_LE_ROLL_PRESS_STUCK_FAILURE_ID                      10u
#define DTC_SRC_SWITCH_STUCK_FAILURE_ID                         11u
#define DTC_VOICE_SWITCH_STUCK_FAILURE_ID                       12u
#define DTC_PREV_SONG_SWITCH_STUCK_FAILURE_ID                   13u
#define DTC_NEXT_SONG_SWITCH_STUCK_FAILURE_ID                   14u
#define DTC_RI_ROLL_PRESS_STUCK_FAILURE_ID                      15u
#define DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_ESP_ID        16u



#define  DTC_GROUP_BODY_INDEX_MIN (0U)
#define  DTC_GROUP_BODY_INDEX_MAX (DTC_TAILGATE_PE_SW_STUCK_ID)

#define  DTC_GROUP_NETWORK_INDEX_MIN (DTC_GROUP_BODY_INDEX_MAX+1)
#define  DTC_GROUP_NETWORK_INDEX_MAX (DTC_LOST_COMMUNICATION_IMMO_ID)



#define _SnapShort_size_0     (fld_sizeof(dtc_snap_shot_data_t, c_main_ecu_supply_voltage))
#define _SnapShort_size_1     (fld_sizeof(dtc_snap_shot_data_t, c_main_ecu_power_mode))



typedef struct{
	dtc_status_t dtc_status;  
#if (DTC_EXTENDED_DATA_ENABLE)	
	dtc_extended_data_t dtc_extended_data;
#endif
#if (DTC_SNAP_SHOT_DATA_ENABLE) /* not used for brilliance-auto */
	dtc_snap_shot_data_t  DTCSnapShotData[TOTAL_DTC_SNAP_SHOT_STORED_NUM];
	uint8_t SnapShotWritePonit;
	uint8_t NumOfSnapShot;
#endif
} dtc_stored_data_t;

typedef struct{
	uint8_t write_pointer;   /* DTC_INDEX Stored to RAM */
	uint8_t stored_dtc_index[TOTAL_MAX_STORED_DTC_NUM];  /* DTC_INDEX Stored to RAM */
	/* Don't save cMonitoringCycle in EEPROM, it just used for  the increasing of monitory cycle counter . */
	dtc_stored_data_t dtc_stored_dt[TOTAL_MAX_STORED_DTC_NUM];
#if 0
	#if (DTC_SNAP_SHOT_DATA_ENABLE) /* not used for brilliance-auto */
	dtc_snap_shot_data_t DTCSnapShotData;
	#endif
#endif
} dtc_info_struct_t;


#if (DTC_SNAP_SHOT_DATA_ENABLE)
extern const uint8_t c_dtc_snap_shot_data_id[TOTAL_DTC_SNAP_SHOT_ID_NUM][2];
extern const uint8_t c_dtc_snap_shot_data_size[TOTAL_DTC_SNAP_SHOT_ID_NUM];
#endif

#if (DTC_EXTENDED_DATA_ENABLE)
extern const uint8_t c_dtc_extended_data_id[TOTAL_DTC_EXTENDED_DATA_NUM];
#endif

extern const uint32_t SupportedDTC[TOTAL_DTC_NUM];

#endif
