CC = gcc
CF =-Wall -Werror -Wextra

all: s21_cat

s21_cat : s21_cat.c
	$(CC) $(CF) s21_cat.c -o s21_cat
	make clean

clean:
	rm -rf *.o

rebuild: all clean