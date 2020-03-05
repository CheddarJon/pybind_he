#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>

TFheGateBootstrappingSecretKeySet*
generateKeys(const int security_bits, int export_keys, TFheGateBootstrappingParameterSet* params)
{
	/* Sets parameters according to security specs, exports the keys if export_keys is set.
	 * Returns pointer to the secret key set and sets params.
	 */
	params = new_default_gate_bootstrapping_parameters(security_bits);

	uint32_t seed[] = {314, 1592, 657};
	tfhe_random_generator_setSeed(seed, 3);
	TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

	if (export_keys) {
		FILE* secret_key = fopen("secret.key", "wb");
		export_tfheGateBootstrappingSecretKeySet_toFile(secret_key, key);
		fclose(secret_key);

		FILE* cloud_key = fopen("cloud.key", "wb");
		export_tfheGateBootstrappingCloudKeySet_toFile(cloud_key, &key->cloud);
		fclose(cloud_key);
	}
	return key;
}

int die(const char* msg)
{
	fprintf(stderr, msg);
	return -1;
}


int main(int argc, char **argv)
{
	TFheGateBootstrappingSecretKeySet* key;
	TFheGateBootstrappingParameterSet* params;

	if ((key = generateKeys(110, 0, params)) == NULL)
	       die("Could not generate secret key set...");

	if (params == NULL)
	       die("Could not set parameters...");

	return 0;
}
