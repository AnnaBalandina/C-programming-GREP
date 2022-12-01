#include "s21_grep.h"

int func_regex(fl *res, char *str) {
  regex_t regex;
  int return_flag = 0;
  int reti;
  char msgbuf[100] = {0};
  for (int i = 0; i < res->ind_pat; i++) {
    if (res->i) {
      reti = regcomp(&regex, res->par_pat[i], REG_EXTENDED | REG_ICASE);
    } else {
      reti = regcomp(&regex, res->par_pat[i], REG_EXTENDED);
    }

    if (res->c && res->par_pat[i][0] == '.' && str[0] == '\n') {
      continue;
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
      return_flag = 1;
      regfree(&regex);
      break;
    } else if (reti == REG_NOMATCH) {
      return_flag = 0;
      // puts("No match");
    } else {
      regerror(reti, &regex, msgbuf, sizeof(msgbuf));
      fprintf(stderr, "Regex match failed: %s\n", msgbuf);
      regfree(&regex);
      exit(1);
    }
    regfree(&regex);
  }
  if (res->v) {
    if (return_flag == 0) {
      return_flag = 1;
    } else {
      return_flag = 0;
    }
  }
  return return_flag;
}