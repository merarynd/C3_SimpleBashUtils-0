#include <fcntl.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void parser();
void reader();
void flag();
void grep();

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
	opt options = { 0 };
	parser(argc, argv, &options);
	for (int i = optind; i < argc; i++) {
		reader(i, argv, &options);
		grep(argv, &options);
	}
	return 0;
}

void parser(int argc, char *argv[], opt *options) {
	int opt = 0;
	char str[4096] = { 0 };
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        options->e = 1;
		sprintf(str, 4096, optarg);
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
		sprintf(str, 4096, optarg);
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

void grep(char *argv[], opt *options) {
	char pattern[4096] = { 0 };
	int flags = REG_EXTENDED;
	regex_t reg;
	int i;
	FILE *fp = fopen(argv[i], "r");
	if (fp != NULL) {
		regcomp(&reg, pattern, flags);
		char text[4096] = { 0 };
		regmatch_t pmatch[1];
		int line_matches = 0, nline = 1;
		line_matches += match;
		nline++;
	}
	regfree(&reg);
	fclose(fp);
}