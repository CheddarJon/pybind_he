#include "bl_crypto.h"

#define DB_SIZE 5

static EVP_PKEY *server_pk;

unsigned char *aesKey;
unsigned char *aesIV;
int aeskeylen;

int
database_search(unsigned char *search, unsigned char *db, const int size)
{
	int ret, i;
	db[size] = '\0';
	unsigned char *tdb = db;
	unsigned char *ts = search;

	ret = 0;
	i = 0;

	if (db == NULL)
		die("db null in database_search...\n");

	while (*tdb != '\0') {
		if (*tdb == *ts) {
			tdb++;
			ts++;
		}

		if (*ts == '\0' && (*tdb == '\0' || *tdb == '\n')) {
			ret |= (1 << i++);
			tdb++;
			ts = search;
		}
		if (*ts != *tdb) {
			while (*tdb != '\n') {
				if (*++tdb == '\0')
					break;
			} tdb++;
			i++;
			ts = search;
		}
	}
	return ret;
}

int
db_search_wrapper()
{
	unsigned char *mock_db = "Hej\nHallå\nTjena\nTja\nTjenixen\nGoddag\nTjena";
	unsigned char *enc_db;
	unsigned char *ret_db;
	int mock_db_len = strlen(mock_db) + 1;
	int enc_db_len;

	setup(&server_pk, &aesKey, &aesIV);
	enc_db = (unsigned char *)malloc(sizeof(unsigned char) * (size_t) (mock_db_len * 4));
	ret_db = (unsigned char *)malloc(sizeof(unsigned char) * (size_t) mock_db_len);

	// Encrypt
	enc_db_len = envelope_seal(&server_pk, mock_db, mock_db_len,
			&aesKey, &aeskeylen, aesIV, enc_db);

	// Wait for client to select op.
	// Decrypt db and compute.
	envelope_open(server_pk, enc_db, enc_db_len, aesKey, aeskeylen, aesIV, ret_db);

	int tmp = database_search("Tjena", ret_db, mock_db_len);
	printf("Return: %d\n", tmp);

	envelope_seal(&server_pk, ret_db, mock_db_len,
			&aesKey, &aeskeylen, aesIV, enc_db);

	teardown(aesKey, aesIV);
	free(enc_db);
	free(ret_db);
	return 0;
}

int
main(int argc, char *argv[])
{
	db_search_wrapper();
	return 0;
}
