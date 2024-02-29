//
// Created by iwall on 2019-11-18.
//
// Version: 1.1
// Author: Kong

#include "aes_crypto.h"
#include "ext/modes.h"
#include <string.h>
#include <stdio.h>

int aes_encrypt_init(AES_CTX *c, const unsigned char *key, int keylen, const unsigned char *ivec, const int mode) {
    int rv = -1;
    if (c == NULL || key == NULL)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    memset(c->ctx, 0x00, sizeof(aes_context));
    c->encrypt = CRYPTO_AES_ENCRYPT;
    c->key = (unsigned char *) key;
    c->num = 0;
    c->buf_len = 0;
    memset(c->buf, 0x00, AES_MAX_BLOCK_LENGTH);
    c->mode = mode;
    if (ivec) {
        memcpy(c->oiv, ivec, AES_MAX_IV_LENGTH);
        memcpy(c->iv, ivec, AES_MAX_IV_LENGTH);
    }
    switch (mode) {
        case AES_ECB:
        case AES_CBC:
        case AES_CFB:
        case AES_OFB:
            rv = aes_setkey_enc(c->ctx, key, keylen * 8);
            break;
        case AES_CTR:
            if (ivec) {
                memcpy(c->ecount, ivec, AES_MAX_COUNT_LENGTH);
            }
            rv = aes_setkey_enc(c->ctx, key, keylen * 8);
            break;
        default:
            rv = CRYPTO_ERR_AES_INVALID_INPUT;
            break;
    }
    return rv;
}

int aes_encrypt_update(AES_CTX *c, const unsigned char *in, int inl, unsigned char *out, int *outl) {
    int rv = -1;
    unsigned int b = 0;
    int l = 0;
    if (c == NULL || in == NULL || out == NULL)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (inl < 1 || *outl < 0)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (*outl < inl)
        return CRYPTO_ERR_AES_BUFFER_TOO_SMALL;

    if (c->encrypt != CRYPTO_AES_ENCRYPT)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    b = inl % AES_BLOCK_SIZE;
    l = inl - b;
    if (l >= AES_BLOCK_SIZE) {
        switch (c->mode) {
            case AES_ECB :
                rv = aes_crypt_ecb(c->ctx, c->encrypt, l, in, out);
                break;
            case AES_CBC:
                rv = aes_crypt_cbc(c->ctx, c->encrypt, l, c->iv, in, out);
                break;
            case AES_CFB:
                rv = aes_crypt_cfb(c->ctx, c->encrypt, l, c->iv, &c->num, in, out);
                break;
            case AES_OFB:
                rv = aes_crypt_ofb(c->ctx, c->encrypt, l, c->iv, &c->num, in, out);
                break;
            case AES_CTR:
                rv = aes_crypt_ctr128(c->ctx, c->encrypt, l, c->iv, c->ecount, &c->num, in, out);
                break;
            default:
                rv = CRYPTO_ERR_AES_INVALID_INPUT;
                break;
        }
    } else {
        rv = 0;
    }
    if (b) {
        memcpy(c->buf, in + l, b);
        c->buf_len = b;
    }
    *outl = l;
    return rv;
}

int aes_encrypt_final(AES_CTX *c, unsigned char *out, int *outl) {
    int rv = 0;
    int n, i, b, bl;
    if (c == NULL || out == NULL)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (*outl < 0)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (c->encrypt != CRYPTO_AES_ENCRYPT)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    b = AES_BLOCK_SIZE;
    bl = c->buf_len;

    n = b - bl;
    for (i = bl; i < b; ++i)
        c->buf[i] = n;

    switch (c->mode) {
        case AES_ECB:
            rv = aes_crypt_ecb(c->ctx, c->encrypt, b, (unsigned char *) c->buf, out + *outl);
            *outl += b;
            break;
        case AES_CBC:
            rv = aes_crypt_cbc(c->ctx, c->encrypt, b, c->iv, c->buf, out + *outl);
            *outl += b;
            break;
        case AES_CFB:
            rv = aes_crypt_cfb(c->ctx, c->encrypt, bl, c->iv, &c->num, c->buf, out + *outl);
            *outl += bl;
            break;
        case AES_OFB:
            rv = aes_crypt_ofb(c->ctx, c->encrypt, bl, c->iv, &c->num, c->buf, out + *outl);
            *outl += bl;
            break;
        case AES_CTR:
            rv = aes_crypt_ctr128(c->ctx, c->encrypt, bl, c->iv, c->ecount, &c->num, c->buf, out + *outl);
            *outl += bl;
            break;
        default:
            rv = CRYPTO_ERR_AES_INVALID_INPUT;
            break;
    }
    return rv;
}


int aes_decrypt_init(AES_CTX *c, const unsigned char *key, int keylen, const unsigned char *ivec, const int mode) {
    int rv = -1;
    if (c == NULL || key == NULL)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    memset(c->ctx, 0x00, sizeof(aes_context));
    c->encrypt = CRYPTO_AES_DECRYPT;
    c->key = (unsigned char *) key;
    c->num = 0;
    c->buf_len = 0;
    memset(c->buf, 0x00, AES_MAX_BLOCK_LENGTH);
    c->mode = mode;

    if (ivec) {
        memcpy(c->oiv, ivec, AES_MAX_IV_LENGTH);
        memcpy(c->iv, ivec, AES_MAX_IV_LENGTH);
    }
    switch (mode) {
        case AES_ECB:
        case AES_CBC:
            rv = aes_setkey_dec(c->ctx, key, keylen * 8);
            break;
        case AES_CFB:
        case AES_OFB:
            rv = aes_setkey_enc(c->ctx, key, keylen * 8);
            break;
        case AES_CTR:
            if (ivec) {
                memcpy(c->ecount, ivec, AES_MAX_COUNT_LENGTH);
            }
            rv = aes_setkey_enc(c->ctx, key, keylen * 8);
            break;
        default:
            rv = CRYPTO_ERR_AES_INVALID_INPUT;
            break;
    }
    return rv;
}

int aes_decrypt_update(AES_CTX *c, const unsigned char *in, int inl, unsigned char *out, int *outl) {
    int rv = -1;
    unsigned int b = 0;
    if (c == NULL || in == NULL || out == NULL)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (inl < 1 || *outl < 0)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (*outl < inl)
        return CRYPTO_ERR_AES_BUFFER_TOO_SMALL;

    if (c->encrypt != CRYPTO_AES_DECRYPT)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    b = inl % AES_BLOCK_SIZE;
    switch (c->mode) {
        case AES_ECB :
            if (b != 0) return CRYPTO_ERR_AES_INVALID_INPUT;
            rv = aes_crypt_ecb(c->ctx, c->encrypt, inl, (unsigned char *) in, out);
            break;
        case AES_CBC:
            if (b != 0) return CRYPTO_ERR_AES_INVALID_INPUT;
            rv = aes_crypt_cbc(c->ctx, c->encrypt, inl, c->iv, in, out);
            break;
        case AES_CFB:
            rv = aes_crypt_cfb(c->ctx, c->encrypt, inl, c->iv, &c->num, in, out);
            break;
        case AES_OFB:
            rv = aes_crypt_ofb(c->ctx, c->encrypt, inl, c->iv, &c->num, in, out);
            break;
        case AES_CTR:
            rv = aes_crypt_ctr128(c->ctx, c->encrypt, inl, c->iv, c->ecount, &c->num, in, out);
            break;
        default:
            rv = CRYPTO_ERR_AES_INVALID_INPUT;
            break;
    }
    *outl = inl;
    return rv;
}

int aes_decrypt_final(AES_CTX *c, unsigned char *out, int *outl) {
    int rv = -1;
    int n, i, b;
    if (c == NULL || out == NULL)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (*outl < 0)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    if (c->encrypt != CRYPTO_AES_DECRYPT)
        return CRYPTO_ERR_AES_INVALID_INPUT;

    b = AES_BLOCK_SIZE;
    switch (c->mode) {
        case AES_ECB:
        case AES_CBC:
            n = out[*outl - 1];
            if (n < 0 || n > b)
                return CRYPTO_ERR_AES_INVALID_INPUT;
            for (i = 1; i <= n; i++)
                out[*outl - i] = 0;
            *outl -= n;
            rv = 0;
            break;
        case AES_CFB:
        case AES_OFB:
        case AES_CTR:
            rv = 0;
            break;
        default:
            rv = CRYPTO_ERR_AES_INVALID_INPUT;
            break;
    }
    return rv;
}

int aes_encrypt_ecb(const unsigned char *key, int keylen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_encrypt_init(&ctx, key, keylen, NULL, AES_ECB);
    if (rv)
        return rv;
    rv = aes_encrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_encrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_decrypt_ecb(const unsigned char *key, int keylen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_decrypt_init(&ctx, key, keylen, NULL, AES_ECB);
    if (rv)
        return rv;
    rv = aes_decrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_decrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_encrypt_cbc(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_encrypt_init(&ctx, key, keylen, iv, AES_CBC);
    if (rv)
        return rv;
    rv = aes_encrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_encrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_decrypt_cbc(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_decrypt_init(&ctx, key, keylen, iv, AES_CBC);
    if (rv)
        return rv;
    rv = aes_decrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_decrypt_final(&ctx, out, outlen);
    return rv;
}


int aes_encrypt_cfb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_encrypt_init(&ctx, key, keylen, iv, AES_CFB);
    if (rv)
        return rv;
    rv = aes_encrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_encrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_decrypt_cfb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_decrypt_init(&ctx, key, keylen, iv, AES_CFB);
    if (rv)
        return rv;
    rv = aes_decrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_decrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_encrypt_ofb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_encrypt_init(&ctx, key, keylen, iv, AES_OFB);
    if (rv)
        return rv;
    rv = aes_encrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_encrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_decrypt_ofb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_decrypt_init(&ctx, key, keylen, iv, AES_OFB);
    if (rv)
        return rv;
    rv = aes_decrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_decrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_encrypt_ctr(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_encrypt_init(&ctx, key, keylen, iv, AES_CTR);
    if (rv)
        return rv;
    rv = aes_encrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_encrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_decrypt_ctr(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen) {
    int rv = 0;
    AES_CTX ctx = {0};
    rv = aes_decrypt_init(&ctx, key, keylen, iv, AES_CTR);
    if (rv)
        return rv;
    rv = aes_decrypt_update(&ctx, in, inlen, out, outlen);
    if (rv)
        return rv;
    rv = aes_decrypt_final(&ctx, out, outlen);
    return rv;
}

int aes_encrypt_ccm(const unsigned char *key, int keylen,
                    const unsigned char *nonce, int nlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen) {
    int rv = 0;

    int M = 12;//default
    int L = 8;//default

    AES_CTX aesCtx;
    CCM128_CONTEXT ccm128Ctx;
    // Setup AES round_key
    aes_setkey_enc(aesCtx.ctx, key, keylen * 8);
    // init ccm -> L
    L = 15 - nlen;
    if (L < 2 || L > 8)
        return -1;
    // set tag to 16 bytes
    M = taglen;
    // init ccm
    CRYPTO_ccm128_init(&ccm128Ctx, M, L,
                       aesCtx.ctx, (block128_f) aes_encrypt);
    // set nonce
    rv = CRYPTO_ccm128_setiv(&ccm128Ctx, nonce, 15 - L, inlen);
    if (rv) { goto END; }
    // encrypt add
    CRYPTO_ccm128_aad(&ccm128Ctx, add, alen);
    rv = CRYPTO_ccm128_encrypt(&ccm128Ctx, in, out, inlen);
    if (rv) { goto END; }
    if (tag) {// independent tag
        if (!CRYPTO_ccm128_tag(&ccm128Ctx, tag, M))
            return -1;
        *outlen = inlen;
    } else {// cipher with tag
        if (!CRYPTO_ccm128_tag(&ccm128Ctx, out + inlen, M))
            return -1;
        *outlen = inlen + taglen;
    }

    END:
    return rv;
}

int aes_decrypt_ccm(const unsigned char *key, int keylen,
                    const unsigned char *nonce, int nlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen) {
    int rv = 0;

    int M = 12;//default
    int L = 8;//default
    int mlen;// message length
    unsigned char auth[16];

    AES_CTX aesCtx;
    CCM128_CONTEXT ccm128Ctx;
    // Setup AES round_key
    aes_setkey_enc(aesCtx.ctx, key, keylen * 8);
    // init ccm -> L
    L = 15 - nlen;
    if (L < 2 || L > 8)
        return -1;
    // set tag to 16 bytes
    M = taglen;

    if (tag) {
        mlen = inlen;
    } else {
        mlen = inlen - taglen;
    }

    CRYPTO_ccm128_init(&ccm128Ctx, M, L,
                       aesCtx.ctx, (block128_f) aes_encrypt);
    // set nonce
    rv = CRYPTO_ccm128_setiv(&ccm128Ctx, nonce, 15 - L, mlen);
    if (rv) { goto END; }
    // decrypt add
    CRYPTO_ccm128_aad(&ccm128Ctx, add, alen);
    rv = CRYPTO_ccm128_decrypt(&ccm128Ctx, in, out, mlen);
    if (rv) { goto END; }
    // check tag
    if (CRYPTO_ccm128_tag(&ccm128Ctx, auth, M)) {
        if (tag) {// independent tag
            if (!memcmp(auth, tag, M)) {
                *outlen = inlen;
                return 0;
            } else {
                return -1;
            }
        } else {// cipher with tag
            if (!memcmp(auth, in + mlen, M)) {
                *outlen = inlen - taglen;
                return 0;
            } else {
                return -1;
            }
        }
    } else {
        return -1;
    }

    END:
    return rv;
}

int aes_encrypt_gcm(const unsigned char *key, int keylen,
                    const unsigned char *iv, int ivlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen) {
    int rv = 0;

    AES_CTX aesCtx;
    GCM128_CONTEXT gcm128Ctx;
    // Setup AES round_key
    aes_setkey_enc(aesCtx.ctx, key, keylen * 8);
    // init ccm
    CRYPTO_gcm128_init(&gcm128Ctx, aesCtx.ctx, (block128_f) aes_encrypt);
    // set nonce
    CRYPTO_gcm128_setiv(&gcm128Ctx, iv, ivlen);
    // encrypt add
    rv = CRYPTO_gcm128_aad(&gcm128Ctx, add, alen);
    if (rv) { goto END; }
    rv = CRYPTO_gcm128_encrypt(&gcm128Ctx, in, out, inlen);
    if (rv) { goto END; }
    if (tag) {// independent tag
        CRYPTO_gcm128_tag(&gcm128Ctx, tag, taglen);
        *outlen = inlen;
    } else {// cipher with tag
        CRYPTO_gcm128_tag(&gcm128Ctx, out + inlen, taglen);
        *outlen = inlen + taglen;
    }

    END:
    return rv;
}

int aes_decrypt_gcm(const unsigned char *key, int keylen,
                    const unsigned char *iv, int ivlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen) {
    int rv = 0;

    int mlen;// message length
    unsigned char auth[16];

    AES_CTX aesCtx;
    GCM128_CONTEXT gcm128Ctx;
    // Setup AES round_key
    aes_setkey_enc(aesCtx.ctx, key, keylen * 8);

    if (tag) {
        mlen = inlen;
    } else {
        mlen = inlen - taglen;
    }

    CRYPTO_gcm128_init(&gcm128Ctx, aesCtx.ctx, (block128_f) aes_encrypt);
    // set nonce
    CRYPTO_gcm128_setiv(&gcm128Ctx, iv, ivlen);
    // decrypt add
    rv = CRYPTO_gcm128_aad(&gcm128Ctx, add, alen);
    if (rv) { goto END; }
    rv = CRYPTO_gcm128_decrypt(&gcm128Ctx, in, out, mlen);
    if (rv) { goto END; }
    // check tag
    CRYPTO_gcm128_tag(&gcm128Ctx, auth, sizeof(auth));
    if (tag) {// independent tag
        if (!memcmp(auth, tag, taglen)) {
            *outlen = inlen;
            return 0;
        } else {
            return -1;
        }
    } else {// cipher with tag
        if (!memcmp(auth, in + mlen, taglen)) {
            *outlen = inlen - taglen;
            return 0;
        } else {
            return -1;
        }
    }

    END:
    return rv;
}