#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFFER 1024 // line buffer
#define MAX_ARGS 64
#define SEPARATORS " \t\n"  // token separators (space, tab, newline)

int main(int argc, char * argv[]) {

    char symbol = ">>>";

    while (!feof(stdin)) { // main loop until end of file/interrupt
        fputs(symbol, stdout); // print the symbol
        if (fgets())

    }

    return 0;

}