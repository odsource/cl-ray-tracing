#include "util.h"

void *malloc_or_die(size_t size)
{
        void *p;
        if ((p = malloc(size)) == NULL)
                exit(EXIT_FAILURE);

        return p;
}

int read_src_from_file(const char *path, char **src)
{
        FILE *f = fopen(path, "r");
        if (!f) {
                LOG_ERROR_F("errno %d, %s", errno, strerror(errno));
                return FAILURE;
        }

        if (fseek(f, 0, SEEK_END))
                return FAILURE;

        long bytes;
        if ((bytes = ftell(f)) == EOF) {
                LOG_ERROR_F("errno %d, %s", errno, strerror(errno));
                return FAILURE;
        }

        if (fseek(f, 0, SEEK_SET))
                return FAILURE;

        *src = (char *)malloc_or_die(bytes * sizeof(char));

        size_t read;
        if ((fread(*src, sizeof(char), bytes, f)) < bytes)
                if (feof(f))
                        LOG_ERROR("Unexpected end of file");

        fclose(f);

        return SUCCESS;
}
