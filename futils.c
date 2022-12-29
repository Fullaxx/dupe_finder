#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <errno.h>

long file_size(const char *path, int v)
{
	struct stat stat_buf;
	int stat_ret = stat(path, &stat_buf);

	if(stat_ret != 0) {
		if(errno == ENOENT) {
			if(v) { fprintf(stderr, "%s does not exist!\n", path); }
			return -1;
		} else {
			if(v) { fprintf(stderr, "stat(%s) failed! %s\n", path, strerror(errno)); }
			return -2;
		}
	}

	if(!S_ISREG(stat_buf.st_mode)) {
		if(v) { fprintf(stderr, "%s is not a regular file!\n", path); }
		return -3;
	}

	return (long)stat_buf.st_size;
}

// Return 1 if path is a regular file
// Return 0 if path is not a regular file
// Return -1 if path does not exist
// Return -2 upon error
int is_regfile(const char *path, int v)
{
	struct stat stat_buf;
	int stat_ret;

	stat_ret = stat(path, &stat_buf);
	if(stat_ret != 0) {
		if(errno == ENOENT) {
			if(v) { fprintf(stderr, "%s does not exist!\n", path); }
			return -1;
		} else {
			if(v) { fprintf(stderr, "stat(%s) failed! %s\n", path, strerror(errno)); }
			return -2;
		}
	}

	if(S_ISREG(stat_buf.st_mode)) { return 1; }

	if(v) { fprintf(stderr, "%s is not a regular file!\n", path); }
	return 0;
}

// Return 1 if path is a directory
// Return 0 if path is not a directory
// Return -1 if path does not exist
// Return -2 upon error
int is_dir(const char *path, int v)
{
	struct stat stat_buf;
	int stat_ret;

	stat_ret = stat(path, &stat_buf);
	if(stat_ret != 0) {
		if(errno == ENOENT) {
			if(v) { fprintf(stderr, "%s does not exist!\n", path); }
			return -1;
		} else {
			if(v) { fprintf(stderr, "stat(%s) failed! %s\n", path, strerror(errno)); }
			return -2;
		}
	}

	if(S_ISDIR(stat_buf.st_mode)) { return 1; }

	if(v) { fprintf(stderr, "%s is not a directory!\n", path); }
	return 0;
}
