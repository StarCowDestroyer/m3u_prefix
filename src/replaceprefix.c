#include "../include/replaceprefix.h"
#include "../include/stringutils.h"
#include <stdio.h>

// replaces prefixes in only one m3u file
int replace_prefix(char *m3u_file, char *replace_str) {
  FILE *m3u_f;
  m3u_f = fopen(m3u_file, "r");
  if (m3u_f == NULL) {
    printf("ERROR\nFailed to open %s\n", m3u_file);
  }

  return 0;
}

int replace_prefixes_all(char **m3u_files, int size, char *replace_str);
