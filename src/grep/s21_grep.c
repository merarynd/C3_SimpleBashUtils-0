#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define D_SIMVOL 4096

void parser();
void reader();
void flag();
// void grep();

typedef struct options {
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
} opt;

int main(int argc, char *argv[]) {
  char pattern[D_SIMVOL] = {0};
  opt options = {0};
  parser(argc, argv, &options);
  reader(pattern, &options);
  flag(options);
  // grep(argv, pattern, &options);
  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  int opt = 0;
  char str[D_SIMVOL] = {0};
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
        sprintf(str, "%s %d %c", optarg);
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        options->f = 1;
        sprintf(str, "%s %d %c", optarg);
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", opt);
        printf("usage: grep [eivclnhsfo] [file ...]\n");
        exit(1);
    }
  }
}

void flag(opt options) {
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

void reader(char *pattern, char *argv[]) {
  int buf, i = 0;
  FILE *fp = fopen(argv[i], "r");
  if (fp == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
  } else {
    int rev;
    while ((buf = fgetc(fp)) != EOF) {
      if (rev == 13 || rev == 10) pattern[i++] = '|';
      if (rev != 13 && rev != 10) pattern[i++] = rev;
    }
  }
  if (pattern[i - 1] == '|') {
    pattern[i - 1] = '\0';
  }
  fclose(fp);
  fp = NULL;
}
