CC = gcc
CF = -c -Wall -Werror -Wextra

all: s21_grep clean

s21_grep.: s21_grep.o
	$(CC) s21_grep.o -o

s21_grep.o:s21_grep.c
	$(CC) $(CF) s21_grep.c -o s21_grep.o

clean:
	rm -rf *.o

rebuild: all clean