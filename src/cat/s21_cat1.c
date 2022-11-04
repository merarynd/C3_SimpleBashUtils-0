#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd = 0, rb = 1;
    char c = 0;

    fd = open(argv[2], O_RDONLY);
    if (fd < 0) {
        printf("fail");
    } else {
        while (rb > 0) {
            rb = read(fd, &c, 1);
            if (rb < 0) {
                printf("failrrrrr");
                break;
            }
            if (rb == 0) {
                break;
            }
            printf("%c", c);
        }
    }
    if (argv[1][0] = '-') {
        switch (argv[1][1]) {
            case 'b':
                printf("1");
                break;
            case 'e':
                printf("2");
                break;
            case 'n':
                printf("3");
                break;
            case 's':
                printf("4");
                break;
            case 't':
                printf("5");
                break;
            case 'v':
                printf("6");
                break;
            case 'E':
                printf("7");
                break;
            case 'T':
                printf("8");
                break;
        }
    } else {
        printf("ERROR");
    }
    return 0;
}

int flag_b(int argc, char* argv[]) {

}

int flag_e(int argc, char* argv[]) {

}

int flag_n(int argc, char* argv[]) {

}

int flag_s(int argc, char* argv[]) {

}

int flag_tt(int argc, char* argv[]) {

}

int flag_v(int argc, char* argv[]) {

}

int flag_E(int argc, char* argv[]) {

}
 int flag_T(int argc, char* argv[]) {

 }