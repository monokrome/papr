#include <stdlib.h>
#include <buffer.h>
#include "types.h"

/**
 * Reset a buffer's data to defaults.
 */
extern "C" void buffer_reset(buffer *b) {
  (*b).path = NULL;
  (*b).file = 0;
  (*b).size = 0;
  (*b).modified = false;
  (*b).firstSegment = NULL;
}

/**
 * Create a new buffer.
 */
extern "C" buffer* buffer_create() {
  auto *b = (buffer *) malloc(sizeof(buffer));

  buffer_reset(b);

  return b;
}

/**
 * Open a specific file and return it as a buffer.
 */
extern "C" buffer* buffer_open(const char *path, const char *mode) {
  auto *b = (buffer *) malloc(sizeof(buffer));

  (*b).path = path;
  (*b).file = fopen(path, mode);
  (*b).modified = false;

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
  auto result;

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
extern "C" void buffer_destroy(buffer *b) {
  if ((*b).firstSegment != NULL) {
    buffer_segment_destroy((*b).firstSegment);
  }

  free(b);
}

/**
 * Reset the contents of a bufferSegment to defaults.
 */
extern "C" void buffer_segment_reset(bufferSegment *segment) {
  // TODO: Initialize (*segment).content.

  (*segment).previousSegment = NULL;
  (*segment).nextSegment = NULL;
}

/**
 * Creates a new buffer segment.
 */
extern "C" bufferSegment* buffer_segment_create() {
  auto *segment = (bufferSegment *) malloc(sizeof(bufferSegment));

  buffer_segment_reset(segment);

  return segment;
}

/**
 * Unlink the provided segment from it's list. Returns a replacement for it.
 *
 * Unlinks the provided segment from it's list. Returns the previous segment
 * unless one does not exist. At which point, it will return the next segment.
 * The return value is useful in the following ways:
 *
 * - If this returns NULL, you have unlinked all segments in the list. Any
 *   related buffers do not have any content at this time.
 *
 * - If this returns the segment which was segment.previousSegment, then the
 *   chain is still in tact.
 *
 * - If this returns the segment which was segment.nextSegment, the returned
 *   segment should be the new firstSegment in any related buffers.
 */
extern "C" bufferSegment* buffer_segment_unlink(bufferSegment *segment) {
  auto *replacement;

  // Set up previousSegment.nextSegment to point to this segment's nextSegment 
  if ((*segment).previousSegment != NULL) {
    (*(*segment).previousSegment).nextSegment = (*segment).nextSegment;

    replacement = (*segment).previousSegment;
  }
  else {
    replacement = (*segment).nextSegment;
  }

  (*segment).previousSegment = NULL;
  (*segment).nextSegment = NULL;

  return replacement;
}

/**
 * Free memory related to the provided buffer segment.
 */
extern "C" void buffer_segment_destroy(bufferSegment *segment) {
  // TODO: Decide whether the unlink here should be assumed or not
  buffer_segment_unlink(segment);

  free(segment);
}

