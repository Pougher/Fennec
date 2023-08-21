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

#endif
