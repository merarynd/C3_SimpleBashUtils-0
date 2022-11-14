#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void parser();
void reader();
void flag();

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

typedef struct Node {
  int value;
  struct Node *next;
} Node;

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  flag(options);
  // for (int i = optind; i < argc; i++) {
  //   reader(i, argv, &options);
  // }
  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  int opt;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
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
        break;
      case 'o':
        options->o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", opt);
        printf("usage: grep [-benstuv] [file ...]\n");
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
