#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>

#define PARAMS "params.data"
#define SECRETKEY "secret.key"
#define CLOUDKEY "cloud.key"
#define WRITEMODE "wb"
#define READMODE "rb"
#define CIPHER_FILE "ciphertext.data"
#define DATA_FILE "message.data"

int die(const char* msg)
{
	fprintf(stderr, msg);
	return -1;
}
