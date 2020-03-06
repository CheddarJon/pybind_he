#include "utils.h"

typedef void (*EVAL_FUNC_PTR)(LweSample*, const LweSample*, const LweSample*, const int,
		const TFheGateBootstrappingCloudKeySet*);

// elementary full comparator gate that is used to compare the i-th bit:
//   input: ai and bi the i-th bit of a and b
//          lsb_carry: the result of the comparison on the lowest bits
//   algo: if (a==b) return lsb_carry else return b
void compare_bit(LweSample* result, const LweSample* a, const LweSample* b,
		const LweSample* lsb_carry, LweSample* tmp,
		const TFheGateBootstrappingCloudKeySet* ck)
{
	bootsXNOR(tmp, a, b, ck);
	bootsMUX(result, tmp, lsb_carry, a, ck);
}

// this function compares two multibit words, and puts the max in result
void minimum(LweSample* result, const LweSample* a, const LweSample* b, const int bits,
		const TFheGateBootstrappingCloudKeySet* ck)
{
	LweSample* tmps = new_gate_bootstrapping_ciphertext_array(2, ck->params);

	//initialize the carry to 0
	bootsCONSTANT(&tmps[0], 0, ck);
	//run the elementary comparator gate n times
	for (int i=0; i<bits; i++) {
		compare_bit(&tmps[0], &a[i], &b[i], &tmps[0], &tmps[1], ck);
	}
	//tmps[0] is the result of the comparaison: 0 if a is larger, 1 if b is larger
	//select the max and copy it to the result
	for (int i=0; i<bits; i++) {
		bootsMUX(&result[i], &tmps[0], &b[i], &a[i], ck);
	}

	delete_gate_bootstrapping_ciphertext_array(2, tmps);
}

int
eval(EVAL_FUNC_PTR func, const int bits)
{
	FILE* cloud_key = fopen(CLOUDKEY, READMODE);
	TFheGateBootstrappingCloudKeySet* ck =
		new_tfheGateBootstrappingCloudKeySet_fromFile(cloud_key);
	fclose(cloud_key);

	const TFheGateBootstrappingParameterSet* params = ck->params;

	LweSample* ciphertext = new_gate_bootstrapping_ciphertext_array(bits, params);
	LweSample* result = new_gate_bootstrapping_ciphertext_array(bits, params);

	FILE* data = fopen(CIPHER_FILE, READMODE);
	for (uint8_t i = 0; i < bits; i++)
		import_gate_bootstrapping_ciphertext_fromFile(data, &ciphertext[i], params);
	fclose(data);

	func(result, ciphertext, ciphertext, bits, ck);

	FILE* output = fopen(DATA_FILE, WRITEMODE);
	for (uint8_t i = 0; i < bits; i++)
		export_gate_bootstrapping_ciphertext_toFile(output, &result[i], params);
	fclose(output);

	delete_gate_bootstrapping_ciphertext_array(bits, ciphertext);
	delete_gate_bootstrapping_ciphertext_array(bits, result);
	delete_gate_bootstrapping_cloud_keyset(ck);
	return 0;
}

int
main()
{
	EVAL_FUNC_PTR f;
	f = minimum;
	eval(f, 16);
}
