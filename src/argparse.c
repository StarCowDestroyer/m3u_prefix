#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>

#include "../include/argparse.h"
#include <unistd.h>

void print_help(char *exec_alias) {
  printf("USAGE:\n");
  printf("\t%s <path/to/m3u/library> <replace string> <path/to/music/dir>",
         exec_alias);

  printf("ARGUMENTS:\n");
  printf("\t<path/to/m3u/library>\t\tPath to m3u files to modify\n");
  printf("\t<replace string>\t\tString to match prefix to replace\n");
  printf("\t<path/to/music/dir>\t\tPath to directory where music files are "
         "stored\n");
}

int get_m3u_files(char *m3u_path, char ***m3u_files_out, int *size_out) {
  DIR *m3u_dir;
  struct dirent *entry;

  m3u_dir = opendir(m3u_path);
  if (m3u_dir == NULL) {
    printf("ERROR\n\tCannot open m3u directory\n");
    exit(1);
  }

  char **m3u_files = NULL;
  size_t count = 0;

  while ((entry = readdir(m3u_dir)) != NULL) {
    // ignore "." and ".." directories
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
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

  *size_out = count;
  *m3u_files_out = m3u_files;
  return 1;
}

args_t parse_args(int argc, char **argv) {
  // defaults
  args_t args = {
      .m3u_path = NULL,
      .music_path = NULL,
      .replace_str = NULL,
  };

  if (argc != ARGS_EXPECTED_SIZE) {
    print_help(argv[0]);
    return args;
  }

  args.m3u_path = argv[1];
  args.replace_str = argv[2];
  args.music_path = argv[3];

  return args;
}
