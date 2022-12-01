#include "s21_grep.h"

void open_file(fl *res) {
  int count_str_match;
  int count_all_str;

  int op_f = 0;
  while (op_f < res->ind_file) {
    FILE *f;
    char str[1024];
    count_str_match = 0;
    count_all_str = 0;
    f = fopen(res->par_file[op_f], "r");
    if (f == NULL) {
      if (!res->s) {
        fprintf(stderr, "grep: %s: No such file or directory\n",
                res->par_file[op_f]);
        op_f++;
        continue;
      }
    } else {
      while (!feof(f)) {
        if (fgets(str, sizeof(str), f)) {
          if (str[strlen(str) - 1] != '\n') {
            strcat(str, "\n");
          }
          count_all_str++;

          // -o
          if ((res->o) && (!res->c) && (!res->l)) {
            flag_o(res, str, op_f, count_all_str);
          }

          // no flags
          if ((res->flag_any == 0) && (func_regex(res, str))) {
            if (res->ind_file > 1) {
              printf("%s:", res->par_file[op_f]);
            }
            printf("%s", str);
          }
          // -i
          if (res->i) {
            func_regex(res, str);
          }
          // -c -l -n
          if (res->c || res->l || res->n) {
            if (func_regex(res, str)) {
              count_str_match++;
            }
          }
          // -l
          if ((res->l) && (func_regex(res, str))) {
            if (count_str_match == 1) {
              if (res->c) {
                count_str_match = 1;
                break;
              }
              printf("%s\n", res->par_file[op_f]);
            }
          }

          // -n
          if ((res->n) && (!res->o) && (func_regex(res, str)) && (!res->l) &&
              (!res->c)) {
            if (res->ind_file > 1) {
              if (!res->h) {
                printf("%s:", res->par_file[op_f]);
              }
            }
            printf("%d:", count_all_str);
            printf("%s", str);
          }

          //-h
          if ((res->h) && (!res->o) && (func_regex(res, str)) && (!res->c) &&
              (!res->l) && (!res->n)) {
            printf("%s", str);
          }
        }
      }
    }
    // -c
    if (res->c) {
      if (!res->h) {
        if (res->ind_file > 1) {
          printf("%s:", res->par_file[op_f]);
        }
      }
      printf("%d\n", count_str_match);
      if (res->l) {
        if (func_regex(res, str)) {
          printf("%s\n", res->par_file[op_f]);
        }
      }
    }

    fclose(f);
    op_f++;
  }
}
