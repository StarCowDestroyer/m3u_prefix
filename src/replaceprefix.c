#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/replaceprefix.h"
#include "../include/stringutils.h"

#define BUFFER_REALLOC_SIZE 256

char *build_file_path(char *dir_path, char *file_name) {
    size_t dir_len = strlen(dir_path);
    size_t file_len = strlen(file_name);
    int needs_slash = 0;
    if (dir_path[dir_len - 1] != '/') {
        needs_slash = 1;
        strcat(dir_path, "/");
    }
    char *path_to_file = (char *)malloc(dir_len + needs_slash + file_len + 1);
    if (path_to_file == NULL) {
        printf("ERROR\nfailed to allocate memory for file path string\n");
        exit(1);
    }
    path_to_file[0] = '\0'; // empty string
    if (dir_len) {
        strcat(path_to_file, dir_path);
    }
    if (file_len) {
        strcat(path_to_file, file_name);
    }

    return path_to_file;
}

char *copym3ufile(char *m3u_dir, char *m3u_file) {
    char *path_to_file = build_file_path(m3u_dir, m3u_file);
    if (!path_to_file) {
        return NULL;
    }

    FILE *m3u_f = fopen(path_to_file, "r");
    if (m3u_f == NULL) {
        printf("ERROR\nIn replace_prefix.\nFailed to open %s\n.", path_to_file);
        free(path_to_file);
        return NULL;
    }

    // char *file_str = (char *)malloc(BUFFER_REALLOC_SIZE);
    // file_str[0] = '\0';
    // size_t file_str_size = 0;
    // char buffer[BUFFER_REALLOC_SIZE];
    // while (fgets(buffer, BUFFER_REALLOC_SIZE - 1, m3u_f)) {
    //     size_t buf_str_size = strlen(buffer);
    //     char *p = (char *)realloc(file_str, buf_str_size + file_str_size +
    //     1); if (!p) {
    //         printf("ERROR\ncouldnt realloc memory for file_str\n");
    //         free(p);
    //         fclose(m3u_f);
    //         free(path_to_file);
    //     }
    //     file_str = p;
    //     strcat(file_str, buffer);
    //     file_str_size += buf_str_size;
    //     file_str[file_str_size] = '\0';
    // }
    // fclose(m3u_f);
    //

    // get file size
    fseek(m3u_f, 0, SEEK_END);
    size_t file_size = ftell(m3u_f);
    fseek(m3u_f, 0, SEEK_SET);

    // Allocate buffer for entire file
    char *file_str = (char *)malloc(file_size + 1);
    if (!file_str) {
        printf("ERROR\nFailed to allocate memory for file content\n");
        fclose(m3u_f);
        free(path_to_file);
        return NULL;
    }

    // read entire file at once
    size_t bytes_read = fread(file_str, 1, file_size, m3u_f);
    file_str[bytes_read] = '\0';

    fclose(m3u_f);
    free(path_to_file);

    return file_str;
}

// replaces prefixes in only one m3u file
int replace_prefix(char *m3u_dir, char *m3u_file, char *prefix, char *replace) {
    // // apri file in lettura, copia tutto in una stringa, usa stringutils per
    // // sostituire apri lo stesso file in scrittura e copia la stringa
    // modificata char *file_str = copym3ufile(m3u_dir, m3u_file);
    // printf("COPIATO\n");
    // printf("FILE:\n%s\n", file_str);
    //
    // strreplace(&file_str, prefix, replace);
    // printf("RIMPIAZZATO\n");
    //
    // // char *file_path = build_file_path(m3u_dir, m3u_file);
    // // FILE *m3u_f = fopen(file_path, "w");
    // // fprintf(m3u_f, file_str);
    //
    // printf("FILE:\n%s", file_str);
    // free(file_str);
    char *file_str = copym3ufile(m3u_dir, m3u_file);
    if (!file_str) {
        return 0;
    }

    if (!strreplace(&file_str, prefix, replace)) {
        printf("ERROR\nFailed to replace string in %s\n", m3u_file);
        free(file_str);
        return 0;
    }

    char *file_path = build_file_path(m3u_dir, m3u_file);
    if (!file_path) {
        free(file_str);
        return 0;
    }

    FILE *m3u_f = fopen(file_path, "w");
    if (!m3u_f) {
        printf("ERROR\nFailed to open %s for writing\n", file_path);
        free(file_str);
        free(file_path);
        return 0;
    }

    fprintf(m3u_f, "%s", file_str);
    fclose(m3u_f);
    free(file_path);
    free(file_str);

    return 1;
}

int replace_prefixes_all(char **m3u_files, int size, char *m3u_dir,
                         char *prefix, char *replace) {
    for (int i = 0; i < size; i++) {
        replace_prefix(m3u_dir, m3u_files[i], prefix, replace);
        printf("FILE %d:\n%s\n\n", i, m3u_files[i]);
    }

    return 1;
}
