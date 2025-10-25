#ifndef MY_REPLACE_PREFIX
#define MY_REPLACE_PREFIX

int replace_prefixes_all(char **m3u_files, int size, char *replace_str);
int replace_prefix(char *dir_path, char *m3u_file, char *replace_str);

#endif
