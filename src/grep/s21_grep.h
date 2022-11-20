#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define D_SIMVOL 4096

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

void parser(int argc, char *argv[], struct options *flags, char *f_pattern);
void grep(struct options *flags, char *pattern, char *namef);

#endif  //  SRC_GREP_S21_GREP_H_