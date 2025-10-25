#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/replaceprefix.h"
#include "../include/stringutils.h"

#define BUFFER_REALLOC_SIZE 256

// replaces prefixes in only one m3u file
int replace_prefix(char *m3u_dir, char *m3u_file, char *replace_str) {
  FILE *m3u_f;
  char *path_to_file = strcat(strcat(path_to_file, m3u_dir), m3u_file);
  m3u_f = fopen(path_to_file, "r");
  if (m3u_f == NULL) {
    printf("ERROR\nIn replace_prefix.\nFailed to open %s\n.", m3u_file);
  }

  // apri file in lettura, copia tutto in una stringa, usa stringutils per
  // sostituire apri lo stesso file in scrittura e copia la stringa modificata
  char *file_str = NULL;
  char *buf = NULL;
  buf = (char *)malloc(BUFFER_REALLOC_SIZE);
  while (fgets(buf, BUFFER_REALLOC_SIZE - 1, m3u_f)) {
    strcat(file_str, buf);
  }
  printf("%s\n", file_str);

  return 0;
}

int replace_prefixes_all(char **m3u_files, int size, char *replace_str);
