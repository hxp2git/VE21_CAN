//
// Created by iwall on 11/20/19.
//
// Version: 1.1
// Author: Liu

#include <string.h>
#include "./../DRV/drv_encryption/aes/aes.h"
#include "cmac_aes128.h"

static unsigned char zero_block[AES_BLOCK_SIZE] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void cmacgo(const unsigned char *key, const unsigned char *ptr, int size, unsigned char *mac) {
    cmac_ctx ctx;
    cmac_init(&ctx, key, AES_BLOCK_SIZE);
    cmac_encrypt(&ctx, ptr, size, mac);
}

static void cmac_xor(unsigned char *out, const unsigned char *in) {
    int i;
    for (i = 0; i < AES_BLOCK_SIZE; i++) {
        out[i] ^= in[i];
    }
}

static void cmac_pad(unsigned char *buf, int len) {
    int i;
    for (i = len; i < AES_BLOCK_SIZE; i++) {
        buf[i] = (i == len) ? 0x80 : 0x00;
    }
}

static void cmac_left_shift(unsigned char *out, unsigned char *in, unsigned char *overflow) {
    int i;
    for (i = AES_BLOCK_SIZE - 1; i >= 0; i--) {
        out[i] = (in[i] << 1) | (*overflow);
        (*overflow) = CMAC_MSB(&in[i]);
    }
}

static void cmac_generate_sub_key(unsigned char *out, unsigned char *in) {
    unsigned char overflow = 0;

    cmac_left_shift(out, in, &overflow);

    if (overflow) {
        out[AES_BLOCK_SIZE - 1] ^= 0x87;
    }
}

void cmac_encrypt(cmac_ctx *ctx, const unsigned char *msg, int msg_len, unsigned char *ct) {
    int i, j, k, n;
    unsigned char buf[AES_BLOCK_SIZE] = {0};
    unsigned char iv[AES_BLOCK_SIZE] = {0};

    k = msg_len % AES_BLOCK_SIZE;
    n = (msg_len - k) / AES_BLOCK_SIZE;

    for (i = 0; i < (k == 0 ? n - 1 : n); ++i) {
        aes_crypt_cbc(&ctx->cmac_key, CRYPTO_AES_ENCRYPT, AES_BLOCK_SIZE, iv, msg + i * AES_BLOCK_SIZE, buf);
    }

    memset(buf, 0, AES_BLOCK_SIZE);
    if (k == 0) {
        if (n == 0) {
            buf[k] = 0x80;
            for (j = 0; j < AES_BLOCK_SIZE; j++) {
                buf[j] ^= ctx->K2[j];
            }
        } else {
            memcpy(buf, msg + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
            for (j = 0; j < AES_BLOCK_SIZE; ++j) {
                buf[j] ^= ctx->K1[j];
            }
        }
    } else {
        memcpy(buf, msg + i * AES_BLOCK_SIZE, k);
        buf[k] = 0x80;
        for (j = 0; j < AES_BLOCK_SIZE; j++) {
            buf[j] ^= ctx->K2[j];
        }
    }
    aes_crypt_cbc(&ctx->cmac_key, CRYPTO_AES_ENCRYPT, AES_BLOCK_SIZE, iv, buf, buf);
    memcpy(ct, iv, AES_BLOCK_SIZE);
}

int cmac_init(cmac_ctx *ctx, const unsigned char *key, int key_len) {
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    unsigned char L[AES_BLOCK_SIZE];

    memset((char *) ctx, 0, sizeof(cmac_ctx));

    aes_setkey_enc(&ctx->cmac_key, key, 128);

    aes_crypt_cbc(&ctx->cmac_key, CRYPTO_AES_ENCRYPT, AES_BLOCK_SIZE, iv, zero_block, L);

    cmac_generate_sub_key(ctx->K1, L);
    cmac_generate_sub_key(ctx->K2, ctx->K1);

    return 1;
}