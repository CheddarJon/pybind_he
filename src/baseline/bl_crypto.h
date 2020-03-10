#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>
#include <openssl/pem.h>

#define RSA_KEYLEN 2048
#define AES_ROUNDS 6
#define AES_KEYLEN 256
#define AES_IVLEN 256

void
die(char *msg)
{
	perror(msg);
	exit(-1);
}

int
envelope_seal(EVP_PKEY **pk, unsigned char *plaintext, int plaintext_len,
		unsigned char **ek, int *ekl, unsigned char *iv,
		unsigned char *ciphertext)
{
	EVP_CIPHER_CTX *ctx;

	int ciphertext_len;

	int len;

	if (!(ctx = EVP_CIPHER_CTX_new()))
		die("Generating new context in evelope_seal...\n");

	if( 1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), ek, ekl, iv, pk, 1))
		die("SealInit...\n");

	if (1 != EVP_SealUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
		die("SealUpdate...\n");
	ciphertext_len = len;

	if (1 != EVP_SealFinal(ctx, ciphertext + len, &len))
		die("SealFinal...\n");
	ciphertext_len += len;

	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}

int
envelope_open(EVP_PKEY *sk, unsigned char *ciphertext, int ciphertext_len,
		unsigned char *ek, int ekl, unsigned char *iv,
		unsigned char *plaintext)
{
	EVP_CIPHER_CTX *ctx;

	int len;

	int plaintext_len;

	if (!(ctx = EVP_CIPHER_CTX_new()))
		die("Generating new context in envelope_open...\n");

	if (1 != EVP_OpenInit(ctx, EVP_aes_256_cbc(), ek, ekl, iv, sk))
		die("OpenInit...\n");

	if (1 != EVP_OpenUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
		die("OpenUpdate...\n");
	plaintext_len = len;

	if (1 != EVP_OpenFinal(ctx, plaintext + len, &len))
		die("OpenFinal...\n");
	plaintext_len += len;

	EVP_CIPHER_CTX_free(ctx);

	return plaintext_len;
}

int
genRSAkeypair(EVP_PKEY **keypair)
{
	EVP_PKEY_CTX *ctx;

	if (!(ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL)))
		die("genRSAkeypair...\n");


	if (EVP_PKEY_keygen_init(ctx) <= 0)
		die("RSA keygen init...\n");

	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, RSA_KEYLEN) <= 0)
		die("RSA keygen bits...\n");

	if (EVP_PKEY_keygen(ctx, keypair) <= 0)
		die("RSA keygen...\n");

	EVP_PKEY_CTX_free(ctx);
	return 0;
}

int
genAESkey(unsigned char **key, unsigned char **iv)
{
	if (RAND_bytes(*key, AES_KEYLEN) == 0)
		die("Failure to fill aes key with random bytes...\n");

	if (RAND_bytes(*iv, AES_IVLEN) == 0)
		die("Failure to fill aes IV with random bytes...\n");
}

int
exportPubKey(EVP_PKEY *pk, unsigned char *f)
{
    if (f == NULL || pk == NULL)
        die("exportPubKey null...\n");
    BIO *bp = BIO_new_file(f, "w+");
    PEM_write_bio_PUBKEY(bp, pk);
}

int
setup(EVP_PKEY **rsaKey, unsigned char **aesKey, unsigned char **aesIV)
{
	*aesKey = (unsigned char *)malloc(AES_KEYLEN);
	*aesIV = (unsigned char *)malloc(AES_IVLEN);

	if (aesKey == NULL || aesIV == NULL)
		die("malloc in setup...\n");

	// OpenSSL init
	ERR_load_crypto_strings();
	OpenSSL_add_all_algorithms();
	OPENSSL_config(NULL);

	// Generate keys
	genRSAkeypair(rsaKey);

	if (rsaKey == NULL)
		die("Failed to set rsa key...\n");

	genAESkey(aesKey, aesIV);

	if (aesKey == NULL || aesIV == NULL)
		die("Failed to set aeskey and IV...\n");

	return 0;
}

int
teardown(unsigned char *aesKey, unsigned char *aesIV)
{
	free(aesKey);
	free(aesIV);
	EVP_cleanup();
	CRYPTO_cleanup_all_ex_data();
	ERR_free_strings();
    return 0;
}
