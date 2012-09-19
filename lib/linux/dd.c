#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int open_input_file(char * fn) {
  return open(fn, O_RDONLY);
}

int open_output_file(char * fn) {
  return open(fn, O_WRONLY);
}

int dd(int in_fd, int out_fd, size_t buffersize) {
  char * buffer;
  size_t pagesize = sysconf(_SC_PAGESIZE);
  size_t count;

  /* Memory should be page-aligned to avoid issues with funny drivers. */
  if(posix_memalign((void**) &buffer, pagesize, buffersize) != 0 || buffer == NULL) {
    fprintf(stderr, "Failed to allocate buffer.\n");
    return 1;
  }

  printf("read_offset: %d; write_offset: %d\n", lseek(in_fd, 0, SEEK_CUR), lseek(out_fd, 0, SEEK_CUR));

  memset(buffer, 0, buffersize);
  while((count = read(in_fd, buffer, buffersize)) != 0) {
    if(write(out_fd, buffer, count) < count) {
      fprintf(stderr, "Failed to write the buffer to output.\n");
      goto error;
    }
    memset(buffer, 0, buffersize);
  }

  if(count == -1) {
    fprintf(stderr, "Failed to write the buffer to output.\n");
    goto error;
  }

  free(buffer);

  return 0;

  error:
    if(buffer != NULL) {
      /* Clear buffer to avoid any security problems */
      memset(buffer, 0, buffersize);
      free(buffer);
    }
    return 1;
}
