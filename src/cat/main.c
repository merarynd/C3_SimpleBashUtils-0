#include<stdio.h>

int main() {
	FILE *file;
	char name[177];
	char i = 0;
	file = fopen("resr.txt", "a");
	while (i < 177) {
		printf("%s\n",name[i]);
		i++;
	}
	fclose(file);
	file = NULL;
	return 0;
}