#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#else
#include <sys/ioctl.h>
#endif

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
