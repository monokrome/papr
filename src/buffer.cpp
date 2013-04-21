#include <stdlib.h>
#include <buffer.h>

/**
 * Create a new buffer.
 */
extern "C" buffer* buffer_create() {
  return (buffer *) malloc(sizeof(buffer));
}

/**
 * Free memory for the provided buffer.
 */
extern "C" void buffer_destroy(buffer *b) { free(b); }

