#include <stdio.h>

#include "xxhash.h"

static int xxh64_FILE(FILE *f, XXH64_hash_t *digest)
{
	size_t n;
	char buf[4096];
	XXH64_state_t *state = XXH64_createState();
	if(!state) { return -1; }

	XXH64_reset(state, 0);
	while ((n = fread(buf, 1, sizeof(buf), f)) != 0) {
		XXH64_update(state, buf, n);
	}

	*digest = XXH64_digest(state);
	XXH64_freeState(state);
	return 0;
}

int file_xxh64(char *path, unsigned long *digest)
{
	int z;
	FILE *f;

	f = fopen(path, "r");
	if(!f) { fprintf(stderr, "fopen(%s, r) FAIL!\n", path); return -1; }

	z = xxh64_FILE(f, digest);
	fclose(f);
	if(z) { fprintf(stderr, "xxh64_FILE(%s) FAIL!\n", path); return -2; }

	return 0; 
}
