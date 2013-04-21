#include <stdio.h>

struct buffer {
  const char *path;
  FILE *file;
  int size;
};

buffer* buffer_create();
void buffer_destroy(buffer *b);

buffer* buffer_open(const char *path, const char *mode);
int buffer_close(buffer *b);

