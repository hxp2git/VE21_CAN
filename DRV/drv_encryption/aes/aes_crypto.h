//
// Created by iwall on 2019-11-18.
//
// Version: 1.1
// Author: Kong

#ifndef CRYPTO_SIMPLE_AES_CRYPTO_H
#define CRYPTO_SIMPLE_AES_CRYPTO_H

#define AES_MAX_BLOCK_LENGTH    16
#define AES_MAX_IV_LENGTH       16
#define AES_MAX_COUNT_LENGTH    16

#define AES_ECB                 1000
#define AES_CBC                 1001
#define AES_CFB                 1002
#define AES_OFB                 1003
#define AES_CTR                 1004

#include "aes.h"

#ifdef __cplusplus
extern "C" {
#endif

struct aes_ctx_st {
    aes_context    ctx[1];                             /* crypto context */
    int            encrypt;                            /* encrypt or decrypt */
    void           *key;                               /* key struct */
    int            num;                                /* working num */
    int            buf_len;                            /* number how many left */
    unsigned char  buf[AES_MAX_BLOCK_LENGTH];          /* partial block */
    int            mode;                               /* Encrypt Mode */
    unsigned char  oiv[AES_MAX_IV_LENGTH];             /* original iv */
    unsigned char  iv[AES_MAX_IV_LENGTH];              /* working iv */
    unsigned char  ecount[AES_MAX_COUNT_LENGTH];       /* used by ctr ecount_buf */
}; /* AES_CTX */

typedef struct aes_ctx_st AES_CTX;

/*
* @abstract This function init for encryption
*
* @param c       [IN]  context
* @param key     [IN]  the AES key.
* @param ivec    [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param mode    [IN] the encryption mode.
*
* @return 0 on success
*/
int aes_encrypt_init(AES_CTX *c, const unsigned char *key, int keylen, const unsigned char *ivec, const int mode);

/*
* @abstract This function process encryption data
*
* @param c       [IN]  context
* @param in      [IN]  the plain text.
* @param inl     [IN]  the plain text length.
* @param out     [OUT]  the last block data for encrypt_update
* @param outl    [OUT]  the encryption length
*
* @return 0 on success
*/
int aes_encrypt_update(AES_CTX *c, const unsigned char *in, int inl, unsigned char *out, int *outl);

/*
* @abstract This function finish encrypt with padding
*
* @param c       [IN]  context
* @param out     [OUT]  the last block data for encrypt_update
* @param outl    [OUT]  the encryption data with padding
*
* @return 0 on success
*/
int aes_encrypt_final(AES_CTX *c, unsigned char *out, int *outl);

/*
* @abstract This function init for decryption
*
* @param c       [IN]  context
* @param key     [IN]  the AES key.
* @param ivec    [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param mode    [IN] the decryption mode.
*
* @return 0 on success
*/
int aes_decrypt_init(AES_CTX *c, const unsigned char *key, int keylen, const unsigned char *ivec, const int mode);

/*
* @abstract This function process decryption data
*
* @param c       [IN]  context
* @param in      [IN]  the cipher text.
* @param inl     [IN]  the cipher text length.
* @param out     [OUT]  the last block data for decrypt_update
* @param outl    [OUT]  the decryption length
*
* @return 0 on success
*/
int aes_decrypt_update(AES_CTX *c, const unsigned char *in, int inl, unsigned char *out, int *outl);

/*
* @abstract This function finish decrypt without padding
*
* @param c       [IN]  context
* @param out     [OUT]  the last block data for decrypt_update
* @param outl    [OUT]  the decryption data without padding
*
* @return 0 on success
*/
int aes_decrypt_final(AES_CTX *c, unsigned char *out, int *outl);

/*
* @abstract This function encrypt data with ecb mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_encrypt_ecb(const unsigned char *key, int keylen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

/*
* @abstract This function decrypt data with ecb mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the out data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_decrypt_ecb(const unsigned char *key, int keylen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);


/*
* @abstract This function encrypt data with cbc mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_encrypt_cbc(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

/*
* @abstract This function decrypt data with cbc mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out

*
* @return 0 on success
*/
int aes_decrypt_cbc(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);


/*
* @abstract This function encrypt data with ofb mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_encrypt_ofb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

/*
* @abstract This function decrypt data with ofb mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_decrypt_ofb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

/*
* @abstract This function encrypt data with cfb mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_encrypt_cfb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

/*
* @abstract This function decrypt data with cfb mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_decrypt_cfb(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

/*
* @abstract This function encrypt data with ctr mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_encrypt_ctr(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);


/*
* @abstract This function decrypt data with ctr mode
*
* @param key     [IN]  the AES key
* @param keylen  [IN]  the AES key length
* @param iv      [IN]  the Vector (update after use)
*                      it must be a readable and writeable buffer of 16 Bytes.
* @param in      [IN]  the buffer holding the input data.
* @param inlen   [IN]  the input data len
* @param out     [OUT] the buffer holding the output data.
* @param outlen  [OUT] the output data len
*                      it must be the buffer length of the out
*
* @return 0 on success
*/
int aes_decrypt_ctr(const unsigned char *key, int keylen,
                    const unsigned char *iv,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen);

int aes_encrypt_ccm(const unsigned char *key, int keylen,
                    const unsigned char *nonce, int nlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen);

int aes_decrypt_ccm(const unsigned char *key, int keylen,
                    const unsigned char *nonce, int nlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen);

int aes_encrypt_gcm(const unsigned char *key, int keylen,
                    const unsigned char *iv, int ivlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen);

int aes_decrypt_gcm(const unsigned char *key, int keylen,
                    const unsigned char *iv, int ivlen,
                    const unsigned char *add, int alen,
                    const unsigned char *in, int inlen,
                    unsigned char *out, int *outlen,
                    unsigned char *tag, int taglen);

#ifdef __cplusplus
}
#endif
#endif //CRYPTO_SIMPLE_AES_CRYPTO_H
