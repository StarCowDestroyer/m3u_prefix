#include <stdio.h>
#include <stdlib.h>

#include "../include/argparse.h"

int main(int argc, char *argv[]) {
  char **m3u_files = NULL;
  int size;
  if (argc == 2) {
    get_m3u_files(argv[1], &m3u_files, &size);

    printf("M3U FILES:\n");
    for (int i = 0; i < size; i++) {
      printf("%s ", m3u_files[i]);
    }
  }
}
