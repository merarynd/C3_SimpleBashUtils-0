CC = gcc
CF = -c -Wall -Werror -Wextra

all: s21_cat clean

s21_cat.: s21_cat.o
	$(CC) s21_cat.o -o

s21_cat.o:s21_cat.c
	$(CC) $(CF) s21_cat.c -o s21_cat.o

clean:
	rm -rf *.o

rebuild: all clean