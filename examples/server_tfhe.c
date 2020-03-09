#include "utils.h"

typedef void (*EVAL_FUNC_PTR)(LweSample*, const LweSample*, const LweSample*, const int,
		const int, const TFheGateBootstrappingCloudKeySet*);

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

void
equal_bits(LweSample* result, const LweSample* a, const LweSample* b,
		LweSample* tmp,
		const TFheGateBootstrappingCloudKeySet* ck)
{
	bootsXNOR(tmp, a, b, ck);
	bootsAND(result, result, tmp, ck);
}

// this function compares two multibit words, and puts the max in result
void minimum(LweSample* result, const LweSample* a, const LweSample* b, const int bits,
		const int scrap, const TFheGateBootstrappingCloudKeySet* ck)
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

void
equal(LweSample* result, const LweSample* a, const LweSample* b, const int bits,
		const int ri, const TFheGateBootstrappingCloudKeySet* ck)
{
	/* Returns 1 if a == b
	 * Returns 0 if a != b
	 */
	LweSample* tmp = new_gate_bootstrapping_ciphertext(ck->params);
	bootsCONSTANT(&result[ri], 1, ck);

	// compare all bits of a and b
	for (uint32_t i = 0; i < bits; i++)
		equal_bits(&result[ri], &a[i], &b[i], tmp, ck);

	delete_gate_bootstrapping_ciphertext(tmp);
}

int
eval(EVAL_FUNC_PTR func, const int bits)
{
	FILE* cloud_key = fopen(CLOUDKEY, READMODE);
	TFheGateBootstrappingCloudKeySet* ck =
		new_tfheGateBootstrappingCloudKeySet_fromFile(cloud_key);
	fclose(cloud_key);

	const TFheGateBootstrappingParameterSet* params = ck->params;

	LweSample* ciphertext[2];
	LweSample* result = new_gate_bootstrapping_ciphertext_array(bits, params);

	for (uint32_t i = 0; i < 2; i++)
		ciphertext[i] = new_gate_bootstrapping_ciphertext_array(bits, params);

	FILE* data = fopen(CIPHER_FILE, READMODE);
	for (uint32_t i = 0; i < 2; i++) {
		for (uint32_t j = 0; j < bits; j++)
			import_gate_bootstrapping_ciphertext_fromFile(data, &ciphertext[i][j], params);
	} fclose(data);

	func(result, ciphertext[0], ciphertext[1], bits, 0, ck);

	FILE* output = fopen(DATA_FILE, WRITEMODE);
	for (uint32_t i = 0; i < bits; i++)
		export_gate_bootstrapping_ciphertext_toFile(output, &result[i], params);
	fclose(output);

	for (uint32_t i = 0; i < 2; i++)
		delete_gate_bootstrapping_ciphertext_array(bits, ciphertext[i]);
	delete_gate_bootstrapping_ciphertext_array(bits, result);
	delete_gate_bootstrapping_cloud_keyset(ck);
	return 0;
}

int
database_search(EVAL_FUNC_PTR func, const char* search, const char* db, const int db_size, const int bits)
{
	FILE* cloud_key = fopen(CLOUDKEY, READMODE);
	TFheGateBootstrappingCloudKeySet* ck =
		new_tfheGateBootstrappingCloudKeySet_fromFile(cloud_key);
	fclose(cloud_key);

	const TFheGateBootstrappingParameterSet* params = ck->params;

	LweSample* db_item[db_size];
	LweSample* search_term = new_gate_bootstrapping_ciphertext_array(bits, params);
	LweSample* result = new_gate_bootstrapping_ciphertext_array(db_size, params);

	for (uint32_t i = 0; i < db_size; i++)
		db_item[i] = new_gate_bootstrapping_ciphertext_array(bits, params);

	// LOADING CIPHERTEXT FROM FILE
	FILE* db_file = fopen(db, READMODE);
	for (uint32_t i = 0; i < db_size; i++) {
		for (uint32_t j = 0; j < bits; j++) {
			import_gate_bootstrapping_ciphertext_fromFile(db_file, &db_item[i][j], params);
		}
	} fclose(db_file);

	FILE* search_file = fopen(search, READMODE);
	for (uint32_t i = 0; i < bits; i++)
		import_gate_bootstrapping_ciphertext_fromFile(search_file, &search_term[i], params);
	fclose(search_file);

	// HOMOMORPHIC OPERATION
	for (uint32_t i = 0; i < db_size; i++)
		func(result, search_term, db_item[i], bits, i, ck);

	// WRITING OUTPUT TO FILE
	FILE* output = fopen(DATA_FILE, WRITEMODE);
	for (uint32_t i = 0; i < db_size; i++)
		export_gate_bootstrapping_ciphertext_toFile(output, &result[i], params);
	fclose(output);

	// CLEANUP
	for (uint32_t i = 0; i < db_size; i++)
		delete_gate_bootstrapping_ciphertext_array(bits, db_item[i]);
	delete_gate_bootstrapping_ciphertext_array(bits, search_term);
	delete_gate_bootstrapping_ciphertext_array(db_size, result);
	delete_gate_bootstrapping_cloud_keyset(ck);

	return 0;
}

int
server_handler(int id, struct sockaddr_in client)
{
	char recv_buffer[1024];
	EVAL_FUNC_PTR f;

	recv(id, recv_buffer, sizeof(recv_buffer), 0);
	close(id);

	if (strcmp(recv_buffer, "e") == 0) {
		f = equal;
	}

	printf("Starting homomorphic operations...\n");
	database_search(f, SEARCH, DATABASE, DATABASE_SIZE, 16);
	return 0;
}

int
server()
{
	/* init. */
	int sid, conn, c;
	struct sockaddr_in server, client;

	if ((sid = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		die("Socket creation");

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sid, (struct sockaddr *) &server, sizeof(server)))
		die("Binding socket");

	if (listen(sid, NUM_CLIENTS))
		die("Listening on port");

	c = sizeof(struct sockaddr_in);

	while (1) {
		printf("Waiting...\n");
		conn = accept(sid, (struct sockaddr *) &client, (socklen_t*) &c);
		if (conn == -1)
			die("Accepting new connection.");
		printf("Accepted connection...\n");

		/* Deal with new connection, implement fork(). */
		server_handler(conn, client);
	}
	return 0;
}

int
main()
{
	server();
}
