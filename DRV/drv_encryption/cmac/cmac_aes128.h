//
// Created by iwall on 11/14/19.
//
// Version: 1.0
// Author: Liu

#ifndef CRYPTO_TINY_CMAC_AES128_H
#define CRYPTO_TINY_CMAC_AES128_H

#include "./../DRV/drv_encryption/aes/aes.h"

typedef struct _cmac_ctx {
    unsigned char K1[AES_BLOCK_SIZE];
    unsigned char K2[AES_BLOCK_SIZE];
    unsigned char T[AES_BLOCK_SIZE];
    aes_context cmac_key;//AES_KEY
} cmac_ctx;

#define CMAC_MSB(x) (((x)[0] & 0x80)?1:0)

#ifdef  __cplusplus
extern "C" {
#endif

int cmac_init(cmac_ctx *ctx, const unsigned char *key, int key_len);

void cmac_encrypt(cmac_ctx *ctx, const unsigned char *msg, int msg_len, unsigned char *ct);

#ifdef  __cplusplus
};
#endif

#endif //CRYPTO_TINY_CMAC_AES128_H
