#include "utils.h"
#include <string.h>

int
generate(const int security_bits, uint8_t export)
{
	/* Sets parameters according to security specs, exports the keys if export_keys is set.
	 * Returns pointer to the secret key set and sets params.
	 */
	TFheGateBootstrappingParameterSet* params =
		new_default_gate_bootstrapping_parameters(security_bits);
	if (params == NULL)
		return -2;

	uint32_t seed[] = {314, 1592, 657};
	tfhe_random_generator_setSeed(seed, 3);

	TFheGateBootstrappingSecretKeySet* key =
		new_random_gate_bootstrapping_secret_keyset(params);
	if (key == NULL)
		return -1;

	if (export) {
		FILE* secret_key = fopen(SECRETKEY, WRITEMODE);
		export_tfheGateBootstrappingSecretKeySet_toFile(secret_key, key);
		fclose(secret_key);

		FILE* cloud_key = fopen(CLOUDKEY, WRITEMODE);
		export_tfheGateBootstrappingCloudKeySet_toFile(cloud_key, &key->cloud);
		fclose(cloud_key);
	}

	delete_gate_bootstrapping_parameters(params);
	delete_gate_bootstrapping_secret_keyset(key);
	return 0;
}

int
encrypt16(int16_t msg, uint8_t export, const char* outfile, const char* mode)
{
	uint32_t bits = 16;

	FILE* secret_key = fopen(SECRETKEY, READMODE);
	TFheGateBootstrappingSecretKeySet* key =
		new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
	fclose(secret_key);

	const TFheGateBootstrappingParameterSet* params = key->params;

	LweSample* ciphertext = new_gate_bootstrapping_ciphertext_array(16, params);

	for (uint32_t i = 0; i < bits; i++)
		bootsSymEncrypt(&ciphertext[i], (msg >> i)&1, key);

	if (export) {
		FILE* encdata = fopen(outfile, mode);
		for (uint32_t i = 0; i < bits; i++)
			export_gate_bootstrapping_ciphertext_toFile(encdata, &ciphertext[i], params);
		fclose(encdata);
	}

	delete_gate_bootstrapping_secret_keyset(key);
	delete_gate_bootstrapping_ciphertext_array(bits, ciphertext);
	return 0;
}

int32_t
decrypt32(const char* infile, const int bits)
{
	uint32_t ret = 0;

	FILE* secret_key = fopen(SECRETKEY, READMODE);
	TFheGateBootstrappingSecretKeySet* key =
		new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
	fclose(secret_key);

	const TFheGateBootstrappingParameterSet* params = key->params;

	LweSample* msg = new_gate_bootstrapping_ciphertext_array(bits, params);

	FILE* data = fopen(infile, READMODE);
	if (data == NULL) {
		delete_gate_bootstrapping_secret_keyset(key);
		delete_gate_bootstrapping_ciphertext_array(bits, msg);
		return -1;
	}
	for (uint32_t i = 0; i < bits; i++)
		import_gate_bootstrapping_ciphertext_fromFile(data, &msg[i], params);

	for (uint32_t i = 0; i < bits; i++) {
		int tmp = bootsSymDecrypt(&msg[i], key);
		ret |= (tmp << i);
	}

	delete_gate_bootstrapping_secret_keyset(key);
	delete_gate_bootstrapping_ciphertext_array(bits, msg);
	return ret;
}

void
initdb(int16_t* data)
{

	for (uint32_t i = 0; i < DATABASE_SIZE; i++) {
		data[i] = rand() % 65536;
	}
}

int
cmdToServer(const char* cmd)
{
	int sid, conn, c;
	struct sockaddr_in server, client;
	char send_buffer[1024];

	if ((sid = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die("Socket creation\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (connect(sid, (struct sockaddr *) &server, sizeof(struct sockaddr_in)))
		die("Connecting to server\n");

	send(sid, cmd, sizeof(cmd), 0);
	return 0;
}

int
main(int argc, char **argv)
{
	int32_t ret = -1;
	char buffer[2];
	int16_t search = 2017;
	int16_t data[DATABASE_SIZE];
	initdb(data);

	if ((ret = generate(110, 1)) == -1)
	       die("Could not generate secret key set...\n");

	if (ret == -2)
	       die("Could not set parameters...\n");

	printf("Input command (type h for help): ");
	while (1) {
		printf(">");
		if ((fgets(buffer, 2, stdin)) == NULL)
			die("Reding stdin...\n");
		buffer[2] = '\0';

		if (strcmp(buffer, "h") == 0)
			printf("Commands: h (help), q (quit), e (encrypt db and search), c (get server to compute), d (decrypt result), p (print result), s (show values), u (update search term)\n");

		if (strcmp(buffer, "q") == 0) {
			printf("You chose this...\n");
			break;
		}

		if (strcmp(buffer, "e") == 0) {
			for (uint32_t i = 0; i < DATABASE_SIZE; i++)
				encrypt16(data[i], 1, ENC_DB, APPENDMODE);
			encrypt16(search, 1, ENC_INPUT, WRITEMODE);
		}

		if (strcmp(buffer, "d") == 0) {
			ret = decrypt32(HE_RESULT, DATABASE_SIZE);
				if (ret == -1)
					printf("Decryption failed...\n");
		}

		if (strcmp(buffer, "s") == 0) {
			printf("db: [");
			for (uint32_t i = 0; i < DATABASE_SIZE; i++)
				printf("%d ", data[i]);
			printf("]\nsearch term: %d\n", search);
		}

		if (strcmp(buffer, "c") == 0) {
			cmdToServer("e");
		}

		if (strcmp(buffer, "u") == 0) {
			printf("Input new search term: ");
			scanf("%d", &search);
		}

		if (strcmp(buffer, "p") == 0) {
			if (ret == -1) {
				printf("Decrypt before print...\n");
			}
			else{
				if (!ret) {
					printf("Found no matches for %d", search);
				}
				else {
					for (uint32_t i = 0; i < DATABASE_SIZE; i++) {
						if ((ret >> i) & 1)
							printf("Found match for %d at index %d\n", search, i);
					}
				}
			}
		}
	}

	return 0;
}
