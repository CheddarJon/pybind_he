#include "utils.h"

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
		FILE* parameters = fopen(PARAMS, WRITEMODE);
		export_tfheGateBootstrappingParameterSet_toFile(parameters, params);
		fclose(parameters);

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
encrypt16(int16_t msg, uint8_t export, const char* outfile)
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
		FILE* encdata = fopen(outfile, APPENDMODE);
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

int main(int argc, char **argv)
{
	int32_t ret;
	int16_t search = 2017;
	int16_t data[DATABASE_SIZE];

	for (uint32_t i = 0; i < DATABASE_SIZE; i++) {
		if ((i % 13) == 0)
			data[i] = search;
		else
			data[i] = rand() % 65536;
	}

	if ((ret = generate(110, 1)) == -1)
	       die("Could not generate secret key set...\n");

	if (ret == -2)
	       die("Could not set parameters...\n");

	for (uint32_t i = 0; i < DATABASE_SIZE; i++)
		encrypt16(data[i], 1, DATABASE);
	encrypt16(search, 1, SEARCH);
	ret = decrypt32(DATA_FILE, DATABASE_SIZE);
	if (ret == -1)
		return 0;

	printf("Result = %d\n", ret);
	for (uint32_t i = 0; i < DATABASE_SIZE; i++) {
		if ((ret >> i) & 1)
			printf("Found match: %d = %d\n", search, data[i]);
		else
			printf("No match: %d != %d\n", search, data[i]);
	}

	return 0;
}
