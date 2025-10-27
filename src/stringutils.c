#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * finds first occurrence of s2 in s1 and
 * returns index of s1 where s2 starts.
 * returns -1 if s2 is not contained in s1.
 */
int strfind(char *s1, const char *s2, int starting_point) {
    int size1 = strlen(s1);
    char *start = s1 + starting_point;

    char *find = strstr(start, s2);
    if (!find) {
        return -1;
    } else {
        return size1 - strlen(find);
    }
}

/*
 * finds first occurrence of s2 in s1 and
 * replaces s2 in s1 with repl, returns 1
 * if s2 is contained in s1, -1 if not
 */
int strreplace(char **file_ptr, const char *torepl, const char *repl) {
    int file_length = strlen(*file_ptr);
    int torepl_length = strlen(torepl);
    int repl_length = strlen(repl);

    int indexes[file_length / torepl_length];
    int i = 0;

    indexes[i] = strfind(*file_ptr, torepl, torepl_length);
    while (indexes[i] != -1) {
        i++;
        indexes[i] = strfind(*file_ptr, torepl, indexes[i - 1] + torepl_length);
    }
    // now we have to replace #i words
    int new_file_length = file_length - i * (torepl_length - repl_length);
    char *new_file = (char *)malloc(new_file_length);
    assert(new_file);

    int count = 0;
    int i2 = 0;
    for (int i = 0; i < new_file_length; i++) {
        if (indexes[count] == i) {
            // inserisci repl
            for (int j = 0; j < repl_length; j++) {
                new_file[j] = repl[j];
            }
            count++;
            i += repl_length;
            i2 += torepl_length;
        }
        new_file[i] = (*file_ptr)[i2];
        i2++;
    }

    return 1;
}
