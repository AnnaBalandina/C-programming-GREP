#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc > 2) {
    fl res = {0};

    parser_flags(argc, argv, &res);
    open_file(&res);
  }
  return 0;
}