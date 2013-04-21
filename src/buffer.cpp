#include <stdlib.h>
#include <buffer.h>
#include "types.h"

/**
 * Create a new buffer.
 */
extern "C" buffer* buffer_create() {
  return (buffer *) malloc(sizeof(buffer));
}

/**
 * Open a specific file and return it as a buffer.
 */
extern "C" buffer* buffer_open(const char *path, const char *mode) {
  buffer *b = buffer_create();

  (*b).path = path;
  (*b).file = fopen(path, mode);

  return b;
}

/**
 * Close the file related to the provided buffer.
 */
extern "C" int buffer_close(buffer *b) {
  int result = fclose((*b).file);

  buffer_destroy(b);

  return result;
}

/**
 * Free memory for the provided buffer.
 */
extern "C" void buffer_destroy(buffer *b) { free(b); }
