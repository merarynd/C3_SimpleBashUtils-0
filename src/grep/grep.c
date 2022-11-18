#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define D_SIMVOL 4096

void parser();
void grep();
void flag();

struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

int main(int argc, char *argv[]) {
  struct options flags = {0};
  char pattern[D_SIMVOL] = {0};
  parser(argc, argv, &flags, pattern);
  flag(&flags);
  if (argc >= 3) {
    grep(argc, argv, &flags, pattern);
  }
  return 0;
}

void parser(int argc, char *argv[], struct options *flags, char pattern) {
  int opt = 0;
  const char *flag_options = "e:ivclnhsf:o";
  while ((opt = getopt(argc, argv, flag_options)) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        sprintf(pattern, D_SIMVOL, "%s", optarg);
        break;
      case 'i':
        flags->e = 1;
        break;
      case 'v':
        flags->e = 1;
        break;
      case 'c':
        flags->e = 1;
        break;
      case 'l':
        flags->e = 1;
        break;
      case 'n':
        flags->e = 1;
        break;
      case 'h':
        flags->e = 1;
        break;
      case 's':
        flags->e = 1;
        break;
      case 'f':
        flags->e = 1;
        sprintf(pattern, D_SIMVOL, "%s", optarg);
        break;
      case 'o':
        flags->e = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", opt);
        printf("usage: grep [eivclnhsfo] [file ...]\n");
        break;
    }
  }
}

void flag(struct options *flags) {
  printf("flag_e = %d\n", options.e);
  printf("flag_i = %d\n", options.i);
  printf("flag_v = %d\n", options.v);
  printf("flag_c = %d\n", options.c);
  printf("flag_l = %d\n", options.l);
  printf("flag_n = %d\n", options.n);
  printf("flag_h = %d\n", options.h);
  printf("flag_s = %d\n", options.s);
  printf("flag_f = %d\n", options.f);
  printf("flag_o = %d\n", options.o);
  printf("\n");
}

void open_file() {}

void grep(char *namef, struct options *flags, char pattern) {}