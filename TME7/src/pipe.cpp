// 1. Fork, exec, pipe
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv) {
    if(argc < 4) {
        perror("Not enough arguments. Usage : \" pipe cmd1 | cmd2\"");
        return -1;
    }

    int i = 0; // index du pipe

    for(i=0; i<argc; i++){
        if(strcmp(argv[i], "|") == 0) {
            argv[i] = NULL;
            break;
        }
    }

    int pipeDesc[2];
    pid_t pid_fils;

    if(pipe(pipeDesc) == -1){
        perror("pipe error");
        exit(1);
    }

    if((pid_fils = fork()) == -1){
        perror("fork error");
        exit(2);
    }

    if(pid_fils == 0){ //fils
        dup2(pipeDesc[1], STDOUT_FILENO);
        close(pipeDesc[1]);
        close(pipeDesc[0]);
        if(execv(argv[1], argv+1)== -1) {
            perror("execv error");
            exit(3);
        }
    }

    else { /* père */
        dup2(pipeDesc[0],STDIN_FILENO);
        close (pipeDesc[0]);
        close (pipeDesc[1]);
        if (execv(argv[i+1], argv+i+1) == -1) {
            perror ("execl"); exit (3);
        }
    }

    return 0;
}
