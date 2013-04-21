struct buffer {
  char *path;
};

buffer* buffer_create();
void buffer_destroy(buffer *b);

