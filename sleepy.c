#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>

unsigned int sleep(unsigned int seconds);

int main(int argc, char * argv[]) {

    unsigned int seconds = atoi(argv[2]);

    printf("%u\n", sleep(seconds));

    return 0;

}

unsigned int sleep(unsigned int seconds) {
    return seconds;
}