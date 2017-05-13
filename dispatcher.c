#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/fcntl.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <string.h>


//http://stackoverflow.com/questions/6698161/getting-raw-input-from-console-using-c-or-c
/* Initialize new terminal i/o settings */
static struct termios old, new1;
void initTermios(int echo) {
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    new1 = old; /* make new settings same as old settings */
    new1.c_lflag &= ~ICANON; /* disable buffered i/o */
    new1.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
    tcsetattr(0, TCSANOW, &new1); /* use these new terminal i/o settings now */
}



int main(void)
{

    struct termios term;
    cfmakeraw(&term);

    int file;
    int size;
    char *data;

    initTermios(1);

    file = open("/tmp/mapped", O_CREAT|O_RDWR|O_TRUNC, 0644);
    size = 512;//getpagesize();
    posix_fallocate(file, 0, size);
    errno = 0;
    if((data = mmap(NULL, size, PROT_WRITE, MAP_SHARED, file, 0)) == NULL){
        perror("mmap");
        exit(1);
    }
    close(file);
    char *c;
    for(;;){
    //NOTE: Ctrl+D (EOT) only works when Enter is pressed afterward.
        c = fgets(data, size, stdin);
        for(int i = 0; c[i] != '\0'; ++i){
            if(c[i] == 0x04 || c[i] == 0x03){
                munmap(data, size);
                data = '\0';
                exit(0);
            }
            if(c[i] == '\n'){
                memset(&data[0], 0, 4096);
            }
        }

        //c = getchar();
        //write(data, c, 1);
    }
}
