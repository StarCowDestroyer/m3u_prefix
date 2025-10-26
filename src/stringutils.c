#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * finds first occurrence of s2 in s1 and
 * returns index of s1 where s2 starts.
 * returns -1 if s2 is not contained in s1.
 */
int strfind(const char *s1, const char *s2) {
    int size1 = strlen(s1);
    int size2 = strlen(s2);

    char *find = strstr(s1, s2);
    if (!find) {
        return -1;
    } else {
        return size1 - strlen(find);
    }
}

/*
 * finds first occurrence of s2 in s1 and
 * replaces s2 in s1 with repl, returns 1
 * if s2 is contained in s1, 0 if not
 */
int strreplace(char **s, const char *torepl, const char *repl) {
    int file_length = strlen(*s);
    int torepl_length = strlen(torepl);
    int repl_length = strlen(repl);

    char *file = malloc(file_length);
    if (!file) {
        printf("ERRORE\n\tfailed to allocate memory in strreplace\n");
        free(file);
        exit(1);
    }
    memcpy(file, *s, file_length);
    free(*s);

    int index = strfind(file, torepl);

    // ora devo togliere torepl_length - repl_length caratteri a partire da
    // index
    for (int i = 0; file[index + torepl_length + i] != '\0'; i++) {
        file[index + i] = file[index + torepl_length + i];
    }
    file[file_length - torepl_length] = '\0';

    char *p =
        (char *)realloc(file, file_length - (torepl_length - repl_length));
    if (!p) {
        printf("ERROR\n\tfailed to reallocate memory for file string in "
               "strreplace\n");
        free(file);
        exit(1);
    }
    file = p;

    for (int i = 0; file[index + repl_length + i] != '\0'; i++) {
        file[index + i] = file[index + repl_length + i];
    }
    file[file_length - (torepl_length - repl_length)] = '\0';
    // e aggiungere i repl_length caratteri sempre a partire da index

    for (int i = 0; i < repl_length; i++) {
        file[index + i] = repl[i];
    }

    *s = file;

    return 1;
}
