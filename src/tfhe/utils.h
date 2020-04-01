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

#define SECRETKEY "secret.key"
#define CLOUDKEY "cloud.key"
#define WRITEMODE "wb"
#define APPENDMODE "ab"
#define READMODE "rb"
#define ENC_DB "encdb.data"
#define HE_RESULT "result.data"
#define ENC_INPUT "encserverinput.data"

#define LOG_FILE "tfhe.log"

#define DATABASE_SIZE 20

#define PORT 6667
#define NUM_CLIENTS 1

int die(const char* msg)
{
	fprintf(stderr, msg);
	exit(-1);
}

