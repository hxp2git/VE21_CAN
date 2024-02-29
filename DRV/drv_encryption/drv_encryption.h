
#ifndef __DRV_ENCRYPTION_H
#define __DRV_ENCRYPTION_H

#include "./cmac/cmac_aes128.h"

typedef struct
{  
    uint8_t *init_data;
    uint16_t init_data_len;
    uint8_t *key;
    uint16_t key_len;
} DrvEncryptionDataStruct;
typedef struct
{
    uint8_t *init_data;
    uint16_t init_data_len;
    uint8_t *key;
    uint16_t key_len;
} DrvEncryptionDefStruct;

typedef struct
{
    /**
     * @brief 设置该对象的参数
     * @param[in] void
     * @return None
     * @par self:  对象实体地址
     * @par def_dat:  设置的数据地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_def)(DrvEncryptionDataStruct *self, DrvEncryptionDefStruct *def_buf);
    /**
     * @brief 获取CMAC加密数据
     * @param[in] void
     * @return None
     * @par self:  对象实体地址
     * @par cmac：加密后的数据存储区域
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*get_cmac)(DrvEncryptionDataStruct *self, uint8_t *cmac);
} DrvEncryptionInterfaceStruct;

extern const DrvEncryptionInterfaceStruct g_drv_encryption_interface;
#ifdef __cplusplus
}
;
#endif

#endif // CRYPTO_TINY_CMAC_AES128_H
