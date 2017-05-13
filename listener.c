#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    int file;
    int size;
    char *data;
    char buffer[512] = {'\0'};

    if((file = open("/tmp/mapped", O_RDONLY, 0644)) == -1){
        puts("Failed to open file (read).");
    }
    size = 512;//getpagesize();
    if((data = mmap(NULL, size, PROT_READ, MAP_SHARED, file, 0)) == -1){
        perror("mmap");
    }
    close(file);
    for(;;){
        //printf("%s\n", data);
        if(strcmp(data, buffer) != 0){
            strcpy(buffer,data);
            system("clear");
            printf("%s\n", data);
        }
        for(int i = 0; data[i] != '\0'; ++i){
            if(data[i] == 0x04 || data[i] == 0x03){
                munmap(data, size);
                exit(0);
            }
        }
    }
}
