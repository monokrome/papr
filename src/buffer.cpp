#include <stdlib.h>
#include <buffer.h>
#include "types.h"

/**
 * Create a new buffer.
 */
extern "C" buffer* buffer_create() {
  buffer *b = (buffer *) malloc(sizeof(buffer));

  (*b).path = NULL;
  (*b).modified = false;

  return b;
}

/**
 * Open a specific file and return it as a buffer.
 */
extern "C" buffer* buffer_open(const char *path, const char *mode) {
  buffer *b = buffer_create();

  (*b).path = path;
  (*b).file = fopen(path, mode);

  if ((*b).file) {
    fseek((*b).file, 0, SEEK_END);

    (*b).size = ftell((*b).file);
  }

  return b;
}

/**
 * Close the file related to the provided buffer.
 */
extern "C" int buffer_close(buffer *b) {
  int result;

  if ((*b).file) {
    result = fclose((*b).file);
    (*b).file = 0L;
  }
  else {
    result = -1L;
  }

  return result;
}

/**
 * Free memory for the provided buffer.
 */
extern "C" void buffer_destroy(buffer *b) { free(b); }

