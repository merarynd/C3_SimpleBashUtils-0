#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void parser();
void reader();
void flag();
int regcomp(regex_t *preg, const char *regex, int cflags);
int regexec(const regex_t *preg, const char *string, size_t nmatch,
            regmatch_t pmatch[], int eflags);
size_t regerror(int errcode, const regex_t *preg, char *errbuf,
                size_t errbuf_size);
void regfree(regex_t *preg);

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

// typedef struct Node {
//   int value;
//   struct Node *next;
// } Node;

int main(int argc, char *argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  flag(options);
  for (int i = optind; i < argc; i++) {
    reader(i, argv, &options);
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

void reader(int i, char *argv[], opt *options) {
  int buf, ter = 0, flag;
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

void grep() {
  int regcomp(regex_t * preg, const char *regex, int cflags);
  int regexec(const regex_t *preg, const char *string, size_t nmatch,
              regmatch_t pmatch[], int eflags);
  size_t regerror(int errcode, const regex_t *preg, char *errbuf,
                  size_t errbuf_size);
  void regfree(regex_t * preg);
}