#ifndef MY_REPLACE_PREFIX
#define MY_REPLACE_PREFIX

int replace_prefixes_all(char **m3u_files, int size, char *m3u_dir,
                         char *prefix, char *replace);
int replace_prefix(char *dir_path, char *m3u_file, char *prefix, char *replace);

#endif
