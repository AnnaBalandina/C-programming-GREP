#include "s21_grep.h"

const struct option long_res[] = {
    {"e", no_argument, 0, 'e'}, {"i", no_argument, 0, 'i'},
    {"v", no_argument, 0, 'v'}, {"c", no_argument, 0, 'c'},
    {"l", no_argument, 0, 'l'}, {"n", no_argument, 0, 'n'},
    {"h", no_argument, 0, 'h'}, {"s", no_argument, 0, 's'},
    {"f", no_argument, 0, 'f'}, {"o", no_argument, 0, 'o'},
    {NULL, 0, NULL, 0}};

const char *short_res = "e:ivclnhsf:o";

void parser_flags(int argc, char **argv, fl *res) {
  int rez = 0;
  opterr = 0;
  while ((rez = getopt_long(argc, argv, short_res, long_res, NULL)) != -1) {
    opterr = 0;
    switch (rez) {
      case 'e':
        res->e = 1;
        strcpy(res->par_pat[res->ind_pat], optarg);
        res->ind_pat++;
        res->count_flags++;
        break;

      case 's':
        res->s = 1;
        break;

      case 'f':
        res->f = 1;
        FILE *f;
        char str[BUFSIZ] = {0};
        if ((f = fopen(optarg, "r")) == NULL) {
          if (!res->s) {
            printf("grep: %s: No such file or directory\n", optarg);
          }
        } else {
          while (!feof(f)) {
            fgets(str, 1024, f);
            for (int i = 0; str[i] != '\0'; i++) {
              if (str[i] == '\n' && i != 0) {
                str[i] = '\0';
              }
            }
            strcpy(res->par_pat[res->ind_pat], str);
            res->ind_pat++;
          }
        }
        fclose(f);
        res->count_flags++;
        break;

      case 'i':
        res->i = 1;
        break;

      case 'v':
        res->v = 1;
        break;

      case 'c':
        res->c = 1;
        res->flag_any++;
        break;

      case 'l':
        res->l = 1;
        res->flag_any++;
        break;

      case 'n':
        res->n = 1;
        res->flag_any++;
        break;

      case 'h':
        res->h = 1;
        res->flag_any++;
        break;

      case 'o':
        res->o = 1;
        res->flag_any++;
        break;

      case '?':
        break;
    }
  }
  if (res->count_flags == 0) {
    strcpy(res->par_pat[res->ind_pat], argv[optind]);
    optind++;
    res->ind_pat++;
  }

  if (optind < argc) {
    for (int i = optind; i < argc; i++) {
      strcpy(res->par_file[res->ind_file], argv[i]);
      res->ind_file++;
    }
  }
}
