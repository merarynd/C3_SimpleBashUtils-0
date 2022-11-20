#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
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

int pars(int argc, char *argv[], opt *options);
void read_f(int i, char *argv[], opt *options);

#endif  //  SRC_CAT_S21_CAT_H_