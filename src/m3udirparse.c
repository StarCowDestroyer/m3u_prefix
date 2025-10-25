#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#include "../include/argparse.h"
#include "../include/m3udirparse.h"

int get_m3u_files(char *m3u_path, char ***m3u_files_out, int *size_out) {
  DIR *m3u_dir;
  struct dirent *entry;

  m3u_dir = opendir(m3u_path);
  if (m3u_dir == NULL) {
    printf("ERROR\n\tCannot open m3u directory\n");
    print_help(m3u_path);
    exit(1);
  }

  char **m3u_files = NULL;
  size_t count = 0;

  while ((entry = readdir(m3u_dir)) != NULL) {
    // ignore "." and ".." directories and non m3u files
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ||
        strstr(entry->d_name, ".m3u") == NULL) {
      continue;
    }

    m3u_files = (char **)realloc(m3u_files, (count + 1) * sizeof(char *));
    if (m3u_files == NULL) {
      printf("ERROR\n\tm3u_files array out of memory\n");
      closedir(m3u_dir);
      exit(1);
    }

    m3u_files[count] = strdup(entry->d_name);
    if (!m3u_files[count]) {
      printf("ERROR\n\tstrdup failed\n");
      closedir(m3u_dir);
      exit(1);
    }

    count++;
  }

  closedir(m3u_dir);

  *size_out = count;
  *m3u_files_out = m3u_files;
  return 1;
}
