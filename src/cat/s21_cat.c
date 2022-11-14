#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void parser();
void reader();

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
  for (int i = optind; i < argc; i++) {
    reader(i, argv, &options);
  }
  return 0;
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
        exit(1);
    }
  }
}

void reader(int i, char *argv[], opt *options) {
  int buf, ter = 0, flag;
  FILE *fp = fopen(argv[i], "r");
  if (fp == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
  } else {
    int rev;
    int count = 1;
    while ((buf = fgetc(fp)) != EOF) {
      flag = 1;
      if (options->s) {
        if (buf == '\n') {
          ter++;
        }
        if (buf != '\n') {
          ter = 0;
        }
      }
      if ((options->s) && (ter > 2)) {
        continue;
      }
      if ((flag == 1) && (options->b)) {
        if ((buf != '\n') && (options->b) && (count == 1)) {
          printf("%6d\t", count++);
        } else if ((buf != '\n') && (options->b) && (rev == '\n')) {
          printf("%6d\t", count++);
        }
        flag++;
      }

      if ((flag == 1) && (options->n)) {
        if ((count == 1) && (options->n)) {
          printf("%6d\t", count++);
        } else if ((rev == '\n') && (options->n)) {
          printf("%6d\t", count++);
        }
        flag++;
      }
      if ((buf == '\t') && ((options->T) || (options->t))) {
        printf("^");
        buf = 'I';
      }
      if ((buf == '\n') && ((options->e) || (options->E))) {
        printf("$");
      }
      if ((options->v) && (buf != '\n') && (buf != '\t')) {
        if (((buf >= 0) && (buf < 9)) || ((buf > 10) && (buf < 32)) ||
            ((buf > 126) && (buf <= 160))) {
          printf("^");
          if (buf > 126) {
            buf = buf - 64;
          } else {
            buf = buf + 64;
          }
        }
      }
      printf("%c", buf);
      rev = buf;
    }
    fclose(fp);
    fp = NULL;
  }
}
