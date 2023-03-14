#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BUFFER 1024 // line buffer
#define MAX_ARGS 64
#define SEPARATORS " \t\n"  // token separators (space, tab, newline)

int main(int argc, char * argv[]) {

    char * symbol = ">>>";
    char buffer[MAX_BUFFER]; // setting max length
    char * args[MAX_ARGS]; // setting max length

    while (!feof(stdin)) { // main loop until end of file/interrupt
        fputs(symbol, stdout); // print the symbol (writing to standard output)
        if (fgets(buffer, MAX_BUFFER, stdin)) {
            int i = 0;
            char ** hold = strtok(buffer, SEPARATORS); // 'hold' holds the result of tokenising so we can add to args
            while (hold != NULL && i < MAX_ARGS) { // while there is something to tokenise, and we aren't over max length
                args[i] = hold; // add token to list
                i++;
                hold = strtok(buffer, SEPARATORS); // get next token ready
            }

            args[i] = NULL; // last element must be null

        }

    }

    return 0;

}