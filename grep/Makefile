CFLAGS = gcc -Wall -Werror -Wextra

ALL: clean s21_grep

s21_grep:
	$(CFLAGS) s21_grep.c open_file.c parser_flags.c func_regex.c flag_o.c -o s21_grep

clean:
	rm -rf s21_grep
	rm -rf ../.clang-format

test_func:ALL
	sh test_func_grep.sh

test_leak:ALL
	sh test_leak_grep.sh

style:
	cp ../../materials/linters/.clang-format ../../src
	clang-format -n s21_grep.c
	clang-format -n open_file.c
	clang-format -n parser_flags.c
	clang-format -n func_regex.c
	clang-format -n flag_o.c
	clang-format -n s21_grep.h
