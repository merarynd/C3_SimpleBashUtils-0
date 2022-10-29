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
    if(argv[1] = 45){
        printf("rrrr");
    }
    return 0;
}
