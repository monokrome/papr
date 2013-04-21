#include <stdio.h>
#include <string>

/**
 * Used to store the entire contents of a buffer in a doubly linked list.
 */
struct bufferSegment {
  std::string content;            // The content of this segment

  bufferSegment *previousSegment; // The segment which prefixes this segment
  bufferSegment *nextSegment;     // The segment which suffixes this segment
};

/**
 * Stores information about a specific buffer available for editing.
 */
struct buffer {
  const char *path;               // NULL or path to file buffer links to
  FILE *file;                     // File descriptor for file or 0
  int size;                       // Size of the loaded file or -1

  bufferSegment *firstSegment;    // A doubly linked list of gaps in the buffer

  bool modified;                  // true if the buffer's content differs from it's file
};

void buffer_reset(buffer *b);

buffer* buffer_create();
void buffer_destroy(buffer *b);

buffer* buffer_open(const char *path, const char *mode);
int buffer_close(buffer *b);

void buffer_segment_reset(bufferSegment *segment);
bufferSegment* buffer_segment_create();
void buffer_segment_destroy(bufferSegment *gap);

