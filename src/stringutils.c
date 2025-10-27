#include <assert.h>
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
 * replaces all occurrences of torepl with repl
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
    new_file[0] = '\0';

    int count = 0;
    int i2 = 0;
    i = 0;
    while (i < new_file_length) {
        if (indexes[count] == i) {
            // inserisci repl
            for (int j = 0; j < repl_length; j++) {
                new_file[j + i] = repl[j];
            }
            indexes[count + 1] += -(count + 1) * (torepl_length - repl_length);
            count++;
            i += repl_length;
            i2 += torepl_length;
            new_file[i] = '\0';
        }
        new_file[i] = (*file_ptr)[i2];
        new_file[i + 1] = '\0';
        i++;
        i2++;
    }

    free(*file_ptr);
    *file_ptr = (char *)malloc(new_file_length);
    *file_ptr = memcpy(*file_ptr, new_file, new_file_length);
    free(new_file);

    return 1;
}
