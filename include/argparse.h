#ifndef MY_ARGPARSE
#define MY_ARGPARSE
#include <stdlib.h>

#define ARGS_EXPECTED_SIZE 4

typedef struct {
  char *m3u_path;
  char *replace_str;
  char *music_path;
} args_t;

args_t parse_args(int argc, char **argv);
void print_help(char *exec_alias);

#endif
