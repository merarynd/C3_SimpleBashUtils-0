#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initFlags();
void processing();
void fun_grep();

struct flageee {
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
} allFlags;

int main(int argc, char *argv[]) {
  struct flageee choice;
  // initFlags(&choice);
  int countFile;
  char pattern[10000] = {0};
  if (argc > 2) {
    processing(argc, argv, pattern, &choice);
    if (!choice.f && !choice.e) {
      strcat(pattern, argv[optind]);
      optind++;
    }
    countFile = argc - optind;
    while (optind < argc) {
      fun_grep(pattern, countFile, argv[optind], &choice);
      optind++;
    }
  }
  return 0;
}

void processing(int argc, char *argv[], char *pattern, struct flageee *choice) {
  int x, wordCount = 0;
  ;
  while ((x = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1)
    switch (x) {
      case 'e':
        choice->e = 1;
        break;
      case 'i':
        choice->i = 1;
        break;
      case 'v':
        choice->v = 1;
        break;
      case 'c':
        choice->c = 1;
        break;
      case 'l':
        choice->l = 1;
        break;
      case 'n':
        choice->n = 1;
        break;
      case 'h':
        choice->h = 1;
        break;
      case 's':
        choice->s = 1;
        break;
      case 'f':
        choice->f = 1;
        break;
      case 'o':
        choice->o = 1;
        break;
      default:
        printf("grep");
    }
}

void fun_grep(char *pattern, int countFile, char *fileName,
              struct flageee *choice) {
  char arr_str[10000] = {0};
  int countLine = 1;
  int countStrc = 0;
  int tf_l = 0;
  FILE *file;
  file = fopen(fileName, "r");
  if (file) {
    regex_t reg;
    if (choice->i) {
      regcomp(&reg, pattern, REG_ICASE);
    } else {
      regcomp(&reg, pattern, REG_EXTENDED);
    }
    regmatch_t pmatch[1];
    while (fgets(arr_str, sizeof(arr_str), file) != NULL) {
      if (strchr(arr_str, '\n') == NULL) {
        strcat(arr_str, "\n");
      }
      int success = regexec(&reg, arr_str, 1, pmatch, 0);
      if ((success == 0 && !choice->v) ||
          (choice->v && success == REG_NOMATCH)) {
        if (countFile > 1 && !choice->h && !choice->c && !choice->l) {
          printf("%s:", fileName);
        }
        tf_l = 1;
        if (choice->n && !choice->l && !choice->c) {
          printf("%d:", countLine);
        }
        if (!choice->l && !choice->c &&
            (!choice->o || (choice->v && choice->o))) {
          printf("%s", arr_str);
        }
        if (choice->o && !choice->c && !choice->l) {
          char *line = arr_str;
          while (success == 0) {
            for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
              printf("%c", line[i]);
            }
            printf("\n");
            while (pmatch[0].rm_eo != 0) {
              pmatch[0].rm_eo--;
              line++;
            }
            success = regexec(&reg, line, 1, pmatch, 0);
          }
        }
        countStrc += 1;
      }
      countLine += 1;
    }
    if (choice->c && choice->l && countStrc) {
      countStrc = 1;
    }
    if (choice->c) {
      if (countFile > 1 && !choice->h) {
        printf("%s:", fileName);
      }
      printf("%d\n", countStrc);
    }
    if (choice->l && tf_l == 1) {
      printf("%s\n", fileName);
    }
    regfree(&reg);
  } else if (!choice->s) {
    fprintf(stderr, "grep: %s: No such file or directory\n", fileName);
  }
  fclose(file);
}
