#include <stdio.h>
#include <unistd.h>
#include "logger.h"

int
main(void) {
  const char * err, * msg;
  struct log * l;

  // l = logger_descriptor(STDOUT_FILENO, &err);
  l = logger_filename("/dev/stdout", &err);
  if (l == NULL) {
    printf("Error creating logger\n");
    printf("Error trace : %s\n", err);
  }

  msg = "Hello World!";
  logger_write(l, "Hello World!\n", &err);
  logger_write(l, "abbcccddddeeeeeffffffg\n", &err);

  return 0;
}
