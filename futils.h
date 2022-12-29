#ifndef __FILEUTILS_H__
#define __FILEUTILS_H__

long file_size(const char *path, int v);
int is_regfile(const char *path, int v);
int is_dir(const char *path, int v);

#endif
