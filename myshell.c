#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

#define MAX_BUFFER 1024 // line buffer
#define MAX_ARGS 64
#define SEPARATORS " \t\n"  // token separators (space, tab, newline)

int main(int argc, char * argv[]) {

    char * symbol = ">>>";
    char buffer[MAX_BUFFER]; // setting max length
    char * args[MAX_ARGS]; // setting max length
    extern char ** environ;

    while (!feof(stdin)) { // main loop until end of file/interrupt
        char * pwd = getenv("PWD");
        fprintf(stdout, "%s%s", pwd, symbol); // print the symbol (writing to standard output)

        if (fgets(buffer, MAX_BUFFER, stdin)) {
            int i = 0;
            char * hold = strtok(buffer, SEPARATORS); // 'hold' holds the result of tokenising so we can add to args
            while (hold != NULL) { // while there is something to tokenise, and we aren't over max length of array
                args[i] = hold; // add token to list
                i++;
                hold = strtok(NULL, SEPARATORS); // get next token ready
            }
            // printf("%d\n", i);
            args[i] = NULL; // last element must be null

            char * cmd = args[0];

            if (*args) { // if there was an argument given
                if (strcmp(cmd, "clr") == 0) { // if clr given
                    pid_t pidclr = fork();
                    if (pidclr < 0) { // error handling
                        printf("Error creating process, fork failed.");
                        exit(1);
                    } else if (pidclr == 0) { // child process
                        execlp("clear", "clear", NULL);
                    } else {
                        wait(NULL); // parent waits for child to finish
                    } 
                } else if (strcmp(cmd, "quit") == 0) { // if quit given
                    exit(0);
                } else if (strcmp(cmd, "environ") == 0) {
                    int j = 0; // counter variable
                    while (environ[j] != NULL) { // haven't hit the end of the list
                        printf("%s\n", environ[j]);
                        j++; // move to next string
                    }
                } else if (strcmp(cmd, "dir") == 0) {
                    // if just dir, use current directory, if something extra, use that directory
                    pid_t pid = fork();

                    if (pid < 0) { // error handling
                        printf("Error creating process, fork failed.");
                        exit(1);
                    } else if (pid == 0) { // child process
                        if (args[1] == NULL) { // if it is just dir
                            execlp("ls", "ls", "-al", NULL);

                        } else if (args[1] != NULL) { // if it is dir <directory>
                            execlp("ls", "ls", "-al", args[1], NULL);
                        }
                    } else {
                        wait(NULL); // parent waits for child to finish
                    }   
                } else if (strcmp(cmd, "cd") == 0) {
                    if (args[1] == NULL) {
                        printf("You are in %s\n", pwd);
                    } else {
                        chdir(args[1]);
                        setenv("PWD", getcwd(NULL, 0), 1);
                    }

                }
            }

        }

    }

    return 0;

}