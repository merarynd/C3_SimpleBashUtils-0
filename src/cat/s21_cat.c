#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void parser();
int flag();

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int T;
  int E;
} opt;

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  flag(options);
}

void parser(int argc, char *argv[], opt *options) {
  int opt;
  int option_index;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options->b = 1;
        break;
      case 'e':
        options->e = 1;
        options->v = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 't':
        options->t = 1;
        options->v = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'T':
        options->T = 1;
        break;
      case 'E':
        options->E = 1;
        break;
      default:
        fprintf(stderr, "cat: illegal option -- %c\n", opt);
        printf("usage: cat [-benstuv] [file ...]\n");
        // exit(1);
    }
  }
}

int flag(opt options) {
  printf("flag_b = %d\n", options.b);
  printf("flag_e = %d\n", options.e);
  printf("flag_n = %d\n", options.n);
  printf("flag_s = %d\n", options.s);
  printf("flag_t = %d\n", options.t);
  printf("flag_v = %d\n", options.v);
  printf("flag_T = %d\n", options.T);
  printf("flag_E = %d\n", options.E);
  printf("\n");
}

// void reader(char *argv[], opt *options) {
//   FILE *fp = fopen(argv[optind], "r");
//   if () {
//   } else {
//     printf("No such file or directory");
//     exit(1);
//   }
// }