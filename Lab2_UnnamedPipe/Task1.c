#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid;

    pid = fork();   //Create a child process

    if(pid == 0 ){
        //child process
        printf("This is the client. I am handling the request.\n");
        printf("My PID = %d, My parent's PID = %d\n", getpid(), getppid());
        exit(0);  //Child exits after completing the task
    } else {
        //Parent process
        printf("This is the server. I have created a child process to handle a client.\n");
        printf("Parent PID = %d, Child PID = %d\n", getpid(), pid);
        //wait for the child to finish
        wait(NULL);
        printf("Client (PID = %d) has finished handling the request.\n", pid);
    }

    return 0;
}
