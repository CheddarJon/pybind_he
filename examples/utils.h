#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define PARAMS "params.data"
#define SECRETKEY "secret.key"
#define CLOUDKEY "cloud.key"
#define WRITEMODE "wb"
#define APPENDMODE "ab"
#define READMODE "rb"
#define CIPHER_FILE "ciphertext.data"
#define DATA_FILE "output.data"

#define DATABASE "database.data"
#define SEARCH "searchterm.data"

#define DATABASE_SIZE 20

#define PORT 6667
#define NUM_CLIENTS 1

int die(const char* msg)
{
	fprintf(stderr, msg);
	exit(-1);
}

