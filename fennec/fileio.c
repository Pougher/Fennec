#include "fileio.h"

char *fennec_read_file(char *filename) {
    FILE* fp;
    long file_size;

    fp = fopen(filename, "rb");
    if (!fp) {
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    // sizeof(char) used just in case
    char *buffer = calloc(sizeof(char), file_size + 1);
    if (!buffer) {
        fclose(fp);
        fennec_log_error("FILE* Memory allocation failed");
        return NULL;
    }

    if (1 != fread(buffer, file_size, 1, fp)) {
        fclose(fp);
        free(buffer);
        fennec_log_error("FILE* Read failed");
        return NULL;
    }

    fclose(fp);
    return buffer;
}
