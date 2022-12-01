#include "s21_grep.h"

void flag_o(fl *res, char *str, int op_f, int count_all_str) {
  regex_t re;
  regmatch_t pmatch[100];
  int status;
  char *ps;
  int ifn = 0;

  for (int i = 0; i < res->ind_pat; i++) {
    if (res->i) {
      status = regcomp(&re, res->par_pat[i], REG_EXTENDED | REG_ICASE);
    } else {
      status = regcomp(&re, res->par_pat[i], REG_EXTENDED);
    }
    ps = str;
    int print_o = 0;
    /* Найти все соответствия */
    while (!(status = regexec(&re, ps, 1, pmatch, 0))) {
      for (int j = pmatch->rm_so; j < pmatch->rm_eo; j++) {
        if (res->ind_file > 1 && print_o == 0) {
          if (!res->h) {
            printf("%s:", res->par_file[op_f++]);
            print_o = 1;
          }
        }
        if (res->n && ifn == 0) {
          printf("%d:", count_all_str);
          ifn = 1;
        }
        printf("%c", ps[j]);
      }
      printf("\n");
      ps += pmatch[0].rm_eo;
    }
    regfree(&re);
  }
}
