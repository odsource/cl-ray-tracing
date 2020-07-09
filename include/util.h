#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "common.h" 

void *malloc_or_die(size_t size);
int read_src_from_file(const char *path, char **src);

#endif /* UTIL_H */
