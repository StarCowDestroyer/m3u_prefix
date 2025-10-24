#include <stddef.h>
#include <stdio.h>

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
