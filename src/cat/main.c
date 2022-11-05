#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void parser();
void flag();
void reader();
void flag_b();
void flag_n();

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
  printf("optin = %d\n", optind);
  for (int i = optind; i < argc; i++) {
    reader(i, argv, &options);
  }
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
        // flag_b(&buf);
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

void flag(opt options) {
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

void reader(int i, char *argv[], opt *options) {
  int buf, arc, buf1;
  char **arv;
  FILE *fp = fopen(argv[i], "r");
  if (fp == NULL) {
    printf("No such file or directory");
    // exit(1);

  } else {
    int count = 0;
    while ((buf = getc(fp)) != EOF) {
      printf("%c", buf);
      **arv == buf;
      if ((options->n)) {
        count = 1;
        arv[0][0] = 1;
        printf("%6d  ", ++count);
      }
      if ((buf == '\t') && (options->t)) {
        printf("^");
      }
      if ((buf == '\n') && (options->b) && (buf1 == '\n')) {
        printf("%6d  ", ++count);
      }
      if ((buf == '\n') && (options->e)) {
        printf("%c", buf);
      }
      if ((buf == '\n') && (options->s)) {
        int i;
        i++;
        if (i > 3) {
          printf("\n");
        }
      }
      buf1 = buf;
      // printf("%c", buf);
    }
    // printf("%c", buf);
    fclose(fp);
    fp = NULL;
  }
}
