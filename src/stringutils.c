#include <assert.h>
#include <stddef.h>
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
 * replaces all occurrences of torepl with repl
 */
// int strreplace(char **file_ptr, const char *torepl, const char *repl) {
//     int file_length = strlen(*file_ptr);
//     int torepl_length = strlen(torepl);
//     int repl_length = strlen(repl);
//
//     int indexes[file_length / torepl_length];
//     int i = 0;
//
//     indexes[i] = strfind(*file_ptr, torepl, 0);
//     while (indexes[i] != -1) {
//         i++;
//         indexes[i] = strfind(*file_ptr, torepl, indexes[i - 1] +
//         torepl_length); printf("indexes[%d] %d\n", i, indexes[i]);
//     }
//     // now we have to replace #i words
//     int new_file_length = file_length - (i * (torepl_length - repl_length));
//     char *new_file = (char *)malloc(new_file_length);
//     assert(new_file);
//
//     int count = 0;
//     int i2 = 0;
//     i = 0;
//     while (i < new_file_length) {
//         if (indexes[count] == i) {
//             // inserisci repl
//             for (int j = 0; j < repl_length; j++) {
//                 new_file[j + i] = repl[j];
//             }
//             indexes[count + 1] += -(count + 1) * (torepl_length -
//             repl_length); count++; i += repl_length; i2 += torepl_length;
//             new_file[i] = '\0';
//         }
//         new_file[i] = (*file_ptr)[i2];
//         new_file[i + 1] = '\0';
//         i++;
//         i2++;
//     }
//
//     free(*file_ptr);
//     *file_ptr = new_file;
//     (*file_ptr)[new_file_length] = '\0';
//
//     return 1;
// }
int strreplace(char **file_ptr, const char *torepl, const char *repl) {
    if (!file_ptr || !*file_ptr || !torepl || !repl) {
        return 0;
    }

    // size_t e' un unsigned int creato apposta per mantenere tutte le posizioni
    // indirizzabili di un pc a 64 (o 32) bit e quindi si usa per le size di
    // array
    size_t file_length = strlen(*file_ptr);
    size_t torepl_length = strlen(torepl);
    size_t repl_length = strlen(repl);

    // count occurrences first
    size_t count = 0;
    const char *pos = *file_ptr;
    while ((pos = strstr(pos, torepl)) != NULL) {
        count++;
        pos += torepl_length;
    }

    if (count == 0) {
        return 1;
    }

    // Calculate new size and allocate memory
    size_t new_length = file_length + count * (repl_length - torepl_length) + 1;
    char *new_file = (char *)malloc(new_length);
    if (!new_file) {
        return 0;
    }

    // Perform replacement
    const char *read_pos = *file_ptr;
    char *write_pos = new_file;

    while ((pos = strstr(read_pos, torepl)) != NULL) {
        // copy everything up to the match
        size_t chunk_size = pos - read_pos;
        memcpy(write_pos, read_pos, chunk_size);
        write_pos += chunk_size;

        // copy the replacement
        memcpy(write_pos, repl, repl_length);
        write_pos += repl_length;

        // move read position past the replaced text
        read_pos = pos + torepl_length;
    }

    // copy the remaining part
    strcpy(write_pos, read_pos);

    // free old buffer and update pointer
    free(*file_ptr);
    *file_ptr = new_file;
    (*file_ptr)[new_length] = '\0';

    return 1;
}
