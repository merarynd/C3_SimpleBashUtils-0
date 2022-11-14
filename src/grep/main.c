#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define BUFFER_SIZE 512

void main(char *pattern, FILE *f) {
  int t;
  regex_t re;
  char buffer[BUFFER_SIZE];

  if ((t = regcomp(&re, pattern, REG_NOSUB)) != 0) {
    regerror(t, &re, buffer, sizeof(buffer));
    fprintf(stderr, "grep: %s (%s)\n", buffer, pattern);
    return;
  }

  while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
    if (regexec(&re, buffer, 0, NULL, 0) == 0) {
      fputs(buffer, stdout);
    }
  }
  regfree(&re);
}