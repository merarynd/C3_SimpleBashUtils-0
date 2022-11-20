#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define D_SIMVOL 4096

void parser();
void grep();
void reader();

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
  char f_pattern[D_SIMVOL] = {0};
  struct options flags = {0};
  parser(argc, argv, &flags, f_pattern);
  // flag(&flags);
  char file[D_SIMVOL] = {0};
  int rev = 0;
  if (!flags.f && !flags.e) {
    snprintf(file, D_SIMVOL, "%s", argv[optind++]);
  }
  if (argc - optind > 1) {
    rev = 1;
  }
  for (int i = optind; i < argc; i++) {
    grep(flags, file, argv[i]);
  }
  return 0;
}
void parser(int argc, char *argv[], struct options *flags, char *f_pattern) {
  int opt = 0;
  const char *flag_options = "e:ivclnhsf:o";
  while ((opt = getopt_long(argc, argv, flag_options, NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        flags->e = 1;
        sprintf(f_pattern, "%s", optarg);
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
        sprintf(f_pattern, "%s", optarg);
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

// void flag(struct options *flags) {
//   printf("flag_e = %d\n", options.e);
//   printf("flag_i = %d\n", options.i);
//   printf("flag_v = %d\n", options.v);
//   printf("flag_c = %d\n", options.c);
//   printf("flag_l = %d\n", options.l);
//   printf("flag_n = %d\n", options.n);
//   printf("flag_h = %d\n", options.h);
//   printf("flag_s = %d\n", options.s);
//   printf("flag_f = %d\n", options.f);
//   printf("flag_o = %d\n", options.o);
//   printf("\n");
// }

// void flag_f(char *pattern, char *namef) {
//   int buf, i = 0;
//   FILE *fp = fopen(namef, "r");
//   if (fp == NULL) {
//     fprintf(stderr, "grep: %s: No such file or directory\n", namef);
//     i = -1;
//   } else {
//     int rev;
//     while ((buf = fgetc(fp)) != EOF) {
//       if (rev == 13 || rev == 10) pattern[i++] = '|';
//       if (rev != 13 && rev != 10) pattern[i++] = rev;
//     }
//   }
//   if (pattern[i - 1] == '|') {
//     pattern[i - 1] = '\0';
//   }
//   fclose(fp);
//   fp = NULL;
// }

void grep(struct options flags, char *pattern, char *namef) {
  int fl = REG_EXTENDED;
  char text[D_SIMVOL] = {0};
  regex_t reg;
  FILE *fp;
  fp = fopen(namef, "r");
  if (fp != NULL) {
    regcomp(&reg, pattern, fl);
    reader(flags, fp, reg, namef);
    regfree(&reg);
    fclose(fp);
  }
}

void reader(struct options flags, FILE *fp, regex_t reg, char *file) {
  char text[D_SIMVOL] = {0};
  regmatch_t pmatch[1];
  while (fgets(text, D_SIMVOL - 1, fp) != NULL) {
    int match = 0;
    int success = regexec(&reg, text, 1, pmatch, 0);
    if (success == 0 && !flags.v) {
      match = 1;
    }
    if (match && !flags.l && !flags.c && !flags.o) {
      printf("%s", text);
    }
    if (match && flags.o) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", text[i]);
      }
      printf("\n");
    }
  }
}