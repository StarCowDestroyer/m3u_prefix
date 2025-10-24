#include <stdio.h>
#include <stdlib.h>

#include "../include/argparse.h"

int main(int argc, char *argv[]) {
  // char **m3u_files = NULL;
  // int size;
  // if (argc == 2) {
  //   get_m3u_files(argv[1], &m3u_files, &size);
  //
  //   printf("M3U FILES:\n");
  //   for (int i = 0; i < size; i++) {
  //     printf("%s ", m3u_files[i]);
  //   }
  // }

  args_t args = parse_args(argc, argv);
  // printf("ARGS:\n%s, %s, %s\n", args.m3u_path, args.replace_str,
  //        args.music_path);
  char **m3u_files = NULL;
  int size;
  if (!get_m3u_files(argv[1], &m3u_files, &size)) {
    printf("ERROR\nfailed to read m3u files\n");
    return 1;
  }

  // replace_text(m3u_files, args.replace_str, args.music_path);
  // free_m3u_files(&m3u_files);
  return 0;
}
