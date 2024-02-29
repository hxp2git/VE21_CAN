/* 
 * File:   drv_flash.h
 * Author: Administrator
 *
 * Created on December 8, 2023, 9:52 AM
 */

#ifndef DRV_FLASH_H
#define	DRV_FLASH_H
#include <stdint.h>
typedef flash_type uint32_t        ///<以32位的数据存储
#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct{
        flash_type (*read_addr_data)(uint32_t addr);
        uint8_t (*erase_one_page)(uint32_t addr);
        void (*write_addr_data)(uint32_t addr, flash_type *pBuffer, uint32_t NumToWrite);
        void (*un_lock)(void);
        void (*lock)(void);
        uint32_t flash_start_save_addr;     ///< 起始地址
        uint32_t flash_end_save_addr;       ///< 结束地址
        uint16_t sectors_size;              ///< 扇区大小
        flash_type *buf;
        uint32_t buf_size;
    }DrvFlashDefStruct;
    typedef struct{
        DrvFlashDefStruct user;
    
    }DrvFlashDataStruct;
    typedef struct{
        void (*read_data)(DrvFlashDataStruct *self, uint32_t addr, flash_type *rx_buf, uint32_t size);
        void (*write_data)(DrvFlashDataStruct *self, uint32_t addr, flash_type *buf, uint32_t size);
        void (*run)(DrvFlashDataStruct *self);
    }DrvFlashInterfaceStruct;

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_FLASH_H */

