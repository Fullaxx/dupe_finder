#ifdef USE_GETLINE
#define _GNU_SOURCE
#else
#define _XOPEN_SOURCE 700
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototypes */
void process_file(char *);
void init_hash_table(void);
void destroy_hash_table(void);

static void chomp(char *buf)
{
	int l;
	if(!buf) { return; }
	l = strlen(buf)-1;
	if(l >= 0) {
		if(buf[l] == '\n') { buf[l] = '\0'; }
		if(buf[l] == '\r') { buf[l] = '\0'; }
	}
}

static void process_stdin(void)
{
#ifdef USE_GETLINE
	size_t n;
	ssize_t bytes;
#else
	char *retval;
	char buf[8192];
#endif

	char *line = NULL;
	FILE *input = stdin;

	while(!feof(input)) {
#ifdef USE_GETLINE
		n=0; bytes = getline(&line, &n, input);
		if(bytes < 0) { break; }
#else
		memset(&buf[0], 0, sizeof(buf));
		retval = fgets(buf, sizeof(buf), input);
		if(!retval) { break; }
		line = strdup(buf);
#endif

		chomp(line);
		process_file(line);
		free(line);
		line = NULL;
	}

	if(line) { free(line); }
}

/*	If we have nothing to process on the command line,
	Then process a list of files from stdin
*/
int main(int argc, char *argv[])
{
	init_hash_table();

	if(argc == 1) {
		process_stdin();
	} else {
		while(--argc > 0) { process_file(argv[argc]); }
	}

	destroy_hash_table();
	return 0;
}
