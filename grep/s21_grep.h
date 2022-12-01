#if !defined(S21_GREP_H)
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX = 100

typedef struct all_flugs {
  int e, i, v, c, l, n, h, s, f, o, ind_pat, ind_file, count_flags, flag_any;
  char par_pat[40][990];
  char par_file[40][990];
} fl;

void parser_flags(int argc, char **argv, fl *res);

void open_file(fl *res);

int func_regex(fl *res, char *str);

void flag_o(fl *res, char *str, int op_f, int count_all_str);

#endif  // S21_GREP_H
