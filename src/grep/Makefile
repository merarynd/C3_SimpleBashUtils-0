CC = gcc
CF =-Wall -Werror -Wextra

all: s21_cat

s21_cat : s21_grep.c
	$(CC) $(CF) s21_grep.c -o s21_grep
	make clean

clean:
	rm -rf *.o

rebuild: all clean