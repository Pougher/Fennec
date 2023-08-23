#ifndef FENNEC_FILEIO_H
#define FENNEC_FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

/* @description
 * Reads a file into a character buffer. This is allocated on the heap and
 * therefore must be freed after you are finished using it. Returns NULL if the
 * file cannot be read, so therefore it is advised that you check for null
 * pointers after calling this function.
 *
 * @argument
 * The path to the file that is to be read
 */
char *fennec_read_file(char*);

/*
 * @description
 * Writes a character buffer to a file. If the file already exists, then in is
 * overwritten with the data supplied to the function
 *
 * @argument
 * The name of the file
 *
 * @argument
 * The buffer that is to be written to the filke
 *
 * @argument the length of the buffer
 */
void fennec_write_file(char*, char*, size_t);

#endif
