#include "DEM_Cfg.h"
#include "DCM_CFG.h"
#include "Dem_Types.h"

const uint32_t SupportedDTC[TOTAL_DTC_NUM] = {

/*0*/   {0xD72287u},/* Loss of communication between MFS and BCM */
/*1*/   {0xD72187u},/* Loss of communication between MFS and ICC */
/*2*/   {0xD72387u},/* Loss of communication between MFS and PEPS */
/*3*/   {0xD72487u},/* Loss of communication between MFS and CIM */
/*4*/   {0xD72586u},/* MFS NM Limphome Fault */
/*5*/   {0xD72688u},/* CAN Bus Communication Fault */
/*6*/   {0x996071u},/* Custom Function Keyboard Long Time (30s) Blocking Failure */
/*7*/   {0x996171u},/* Return function button long time (30s) stuck fault */
/*8*/   {0x996271u},/* Left Switching Instrument Keyboard Long Time (30s) Stagnation Fault */
/*9*/   {0x996371u},/* Fault of long time (30s) jam of switch instrument key to right */
/*10*/   {0x996671u},/* Left Roller (Press) Long Time (30s) Stagnation Fault */
/*11*/   {0x996771u},/* Long time (30s) jamming failure of MODE function keys */
/*12*/   {0x996871u},/* Speech Recognition Keyboard Long Time (30s) Stick Fault */
/*13*/   {0x996971u},/* Long time (30s) jamming failure of the last function key */
/*14*/   {0x996A71u},/* Long time (30s) jamming failure of next function key */
/*15*/   {0x996D71u},/* Right Roller (Press) Long Time (30s) Stagnation Fault */
/*16*/   {0xD72787u},/* Loss of communication between MFS and ESP */

};

const dtc_drv_cfg_t dtc_cfg_tbl[TOTAL_DTC_NUM] = {

/*0*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Loss of communication between MFS and BCM */
/*1*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Loss of communication between MFS and ICC */
/*2*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Loss of communication between MFS and PEPS */
/*3*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Loss of communication between MFS and CIM��Only the flagship edition��*/
/*4*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* MFS NM Limphome Fault */
/*5*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* CAN Bus Communication Fault */
/*6*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Custom Function Keyboard Long Time (30s) Blocking Failure */
/*7*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Return function button long time (30s) stuck fault */
/*8*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Left Switching Instrument Keyboard Long Time (30s) Stagnation Fault */
/*9*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Fault of long time (30s) jam of switch instrument key to right */
/*10*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Left Roller (Press) Long Time (30s) Stagnation Fault */
/*11*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Long time (30s) jamming failure of MODE function keys */
/*12*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Speech Recognition Keyboard Long Time (30s) Stick Fault */
/*13*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Long time (30s) jamming failure of the last function key */
/*14*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Long time (30s) jamming failure of next function key */
/*15*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Right Roller (Press) Long Time (30s) Stagnation Fault */
/*16*/   {1, DEM_DTC_DEBOUNCE_RST, DTC_STORAGE_TO_EE},/* Loss of communication between MFS and ESP */
};

#if (DTC_SNAP_SHOT_DATA_ENABLE)
const uint8_t c_dtc_snap_shot_data_id[TOTAL_DTC_SNAP_SHOT_ID_NUM][2] = { 
  {0x15, 0x40}, {0x15, 0x41}, 
};

//各快照的內容長度
const uint8_t c_dtc_snap_shot_data_size[TOTAL_DTC_SNAP_SHOT_ID_NUM] = {
 _SnapShort_size_0, _SnapShort_size_1,
};

#endif


#if (DTC_EXTENDED_DATA_ENABLE)
const uint8_t c_dtc_extended_data_id[TOTAL_DTC_EXTENDED_DATA_NUM] = {
  0x01, 0x02, 0x03, 0x04, 0x10,
};
#endif
