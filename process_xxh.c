#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <qlibc/qlibc.h>

#include "futils.h"

/* Prototypes */
int file_xxh64(const char *, unsigned long *);
#define HSIZE (((64/8)*2)+1)

#define GET_WITH_NEWMEM (true)
qhashtbl_t *qht;

/*	Create a qhashtbl of every filename we get stored by md5sum
	If the md5sum of this file has no entry, it is the first with that md5sum value: save only
	If the md5sum from this file returns an entry in the qhashtbl, print both and wipe filename keeping md5sum
	All future matching md5sum values will get printed, but we don't reprint anything that has already been printed
*/
void process_file(char *file)
{
	int err, is_rfile;
	unsigned long digest;
	char hash[HSIZE];
	char *val_ptr;

	if(!file) { return; }
	is_rfile = is_regfile(file, 0);
	if(is_rfile != 1) { return; }

	err = file_xxh64(file, &digest);
	if(err) { /*fprintf(stderr, "COULD NOT HASH FILE: %s\n", file);*/ return; }
	snprintf(hash, sizeof(hash), "%016lx", digest);

	val_ptr = qht->get(qht, hash, NULL, GET_WITH_NEWMEM);
	if(!val_ptr) {
		qht->put(qht, hash, file, strlen(file)+1);
	} else {
		printf("%s %s\n", hash, file);
		if(strlen(val_ptr) > 0) {
			printf("%s %s\n", hash, val_ptr);
		}
		free(val_ptr);
		file[0] = 0;
		qht->put(qht, hash, file, 1);
	}
}

void init_hash_table(void)
{
	qht = qhashtbl(0, QHASHTBL_THREADSAFE);
}

void destroy_hash_table(void)
{
	qht->free(qht);
}
