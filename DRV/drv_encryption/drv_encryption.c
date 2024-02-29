#include "./drv_encryption.h"

void SetDef(DrvEncryptionDataStruct *self, DrvEncryptionDefStruct *def_buf)
{
    self->init_data = def_buf->init_data;
    self->init_data_len = def_buf->init_data_len;
    self->key = def_buf->key;
    self->key_len = def_buf->key_len;
}
void GetCmac(DrvEncryptionDataStruct *self, uint8_t *cmac)
{
    uint8_t ires = 0;
    cmac_ctx ctx;
    if (self->init_data == NULL || self->key == NULL)
    {
        return;
    }
    if (self->key_len != 16)
    {
        return;
    }
    ires = cmac_init(&ctx, self->key, self->key_len);
    if (ires != 1)
    {
        return;
    }
    cmac_encrypt(&ctx, self->init_data, self->init_data_len, cmac);
}

const DrvEncryptionInterfaceStruct g_drv_encryption_interface =
{
    .set_def = SetDef,
    .get_cmac = GetCmac,
};
