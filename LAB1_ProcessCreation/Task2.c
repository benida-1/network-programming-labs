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
        printf("Client: Handling the request...\n");
        printf("Client: PID = %d, My Parent's PID = %d\n", getpid(), getppid());
        sleep(2);           //Simulate some processing time
        exit(0);            //Child exits after completing the task
    } else {
        //Parent process (Server)
        printf("Server: Created a child process to handle a client.\n");
        printf("Server PID = %d, Child PID = %d\n", getpid(), pid);
        //wait for the child to finish
        wait(NULL);
        printf("Server: Client (PID = %d) has finished handling the request.\n", pid);
    }

    return 0;
}
