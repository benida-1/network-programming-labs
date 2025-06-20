#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> 

int main() {
    int fd[2]; // fd[0] = read end, fd[1] = write end
    pid_t pid;

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(fd[1]); // Close unused write end
        int received_value;
        read(fd[0], &received_value, sizeof(received_value));
        close(fd[0]);
        printf("Child: Received value = %d\n", received_value);
    } else {
        // Parent process
        close(fd[0]); // Close unused read end
        int value_to_send = 10;
        write(fd[1], &value_to_send, sizeof(value_to_send));
        close(fd[1]);
       // wait(NULL); // Wait for child to finish
    }

    return 0;
}
