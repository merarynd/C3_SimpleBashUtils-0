
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D_SIMVOL 4096
void parser();
void grep();
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
  if (!flags.f && !flags.e) {
    snprintf(file, D_SIMVOL, "%s", argv[optind++]);
  }
  if (argc - optind > 1) {
  }
  for (int i = optind; i < argc; i++) {
    grep(&flags, file, argv[i]);
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
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'f':
        flags->f = 1;
        sprintf(f_pattern, "%s", optarg);
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        fprintf(stderr, "grep: illegal option -- %c\n", opt);
        printf("usage: grep [eivclnhsfo] [file ...]\n");
        break;
    }
  }
}

void grep(struct options *flags, char *pattern, char *namef) {
  // int fl = REG_EXTENDED;
  char text[D_SIMVOL] = {0};
  regex_t reg;
  FILE *fp;
  fp = fopen(namef, "r");
  if (fp != NULL) {
    if (flags->i) {
      regcomp(&reg, pattern, REG_ICASE);
    } else {
      regcomp(&reg, pattern, REG_EXTENDED);
    }
    regmatch_t pmatch[1];
    int line = 0, nl = 1;
    while (fgets(text, D_SIMVOL - 1, fp) != NULL) {
      int match = 0;
      int success = regexec(&reg, text, 1, pmatch, 0);
      if (strchr(text, '\n') == NULL) {
        strcat(text, "\n");
      }
      if (success == 0 && !flags->v) {
        match = 1;
      }
      if (success == REG_NOMATCH && flags->v) {
        match = 1;
      }
      if (match && !flags->l && !flags->c && flags->n) {
        printf("%d:", nl);
      }
      if (match && !flags->l && !flags->c && !flags->o) {
        printf("%s", text);
      }
      if (match && flags->o) {
        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
          printf("%c", text[i]);
        }
        printf("\n");
      }
      line += match;
      nl++;
    }
    if (flags->l && line > 0) {
      printf("%s\n", namef);
    }
    if (flags->c && !flags->l) {
      printf("%d\n", line);
    }
    regfree(&reg);
    fclose(fp);
  }
}

// void(char *pattern, char *argv[]) {
//   int buf, i = 0;
//   FILE *fp = fopen(argv[i], "r");
//   if (fp == NULL) {
//     fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
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
