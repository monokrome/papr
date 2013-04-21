#include <stdio.h>

struct buffer {
  const char *path;    // NULL or path to file buffer links to
  FILE *file;          // File descriptor for file or 0
  int size;            // Size of the loaded file or -1

  bool modified;       // true if the buffer's content differs from it's file
};

buffer* buffer_create();
void buffer_destroy(buffer *b);

buffer* buffer_open(const char *path, const char *mode);
int buffer_close(buffer *b);

void buffer_reset(buffer *b);

