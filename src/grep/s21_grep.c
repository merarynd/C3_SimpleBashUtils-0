#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define BUFFER_SIZE 512

void parser();
void reader();
void flag();
void grep(char *pattern, FILE *f);
// int regexec(const regex_t *preg, const char *string, size_t nmatch,
//             regmatch_t *pmatch, int eflags);

// int regcomp(regex_t *preg, const char *pattern, int cflags);

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

typedef struct {
  regoff_t rm_so;
  regoff_t rm_eo;
} regmatch_t;

int main(int argc, char *argv[]) {
  opt options = {0};
  char *pattern;
  FILE *fp;
  parser(argc, argv, &options);
  flag(options);
  for (int i = optind; i < argc; i++) {
    reader(i, argv);
    grep(pattern, fp);
  }
  return 0;
}

void parser(int argc, char *argv[], opt *options) {
  int opt = 0;
  int option_index;
  static struct option long_options[] = {
      // {"number-nonblank", no_argument, NULL, 'b'},
      // {"number", no_argument, NULL, 'n'},
      // {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                            &option_index)) != -1) {
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

void reader(int i, char *argv[]) {
  int buf;
  FILE *fp = fopen(argv[i], "r");
  if (fp == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
  } else {
    int rev;
    while ((buf = fgetc(fp)) != EOF) {
      printf("%c", buf);
      rev = buf;
    }
    fclose(fp);
    fp = NULL;
  }
}

void grep(char *pattern, FILE *fp) {
  int t;
  regex_t re;
  char buffer[BUFFER_SIZE];

  if ((t = regcomp(&re, pattern, REG_NOSUB)) != 0) {
    regerror(t, &re, buffer, sizeof(buffer));
    fprintf(stderr, "grep: %s (%s)\n", buffer, pattern);
    return;
  }

  while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
    if (regexec(&re, buffer, 0, NULL, 0) == 0) {
      fputs(buffer, stdout);
    }
  }
  regfree(&re);
}