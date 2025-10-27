#ifndef MY_STRING_UTILS
#define MY_STRING_UTILS

/*
 * finds first occurrence of s2 in s1 and
 * returns index of s1 where s2 starts.
 * returns -1 if s2 is not contained in s1.
 */
// int strfind(const char *s1, const char *s2);

/*
 * finds first occurrence of s2 in s1 and
 * replaces s2 in s1 with repl, returns 1
 * if s2 is contained in s1, 0 if not
 */
int strreplace(char **s1, const char *toreplace, const char *repl);

#endif
