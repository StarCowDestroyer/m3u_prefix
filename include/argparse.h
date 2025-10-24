#ifndef MY_ARGPARSE
#define MY_ARGPARSE
#include <stdlib.h>

typedef struct {
  char *m3u_path;
  char *replace_str;
  char *music_path;
} args_t;

args_t parse_args(int argc, char **argv);
int get_m3u_files(char *m3u_path, char ***m3u_files_out, int *size_out);
#endif
