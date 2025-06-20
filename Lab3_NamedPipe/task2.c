#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe1[2]; // Parent to child
    int pipe2[2]; // Child to parent

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // --- Child Process ---
        close(pipe1[1]); // Close unused write end of pipe1
        close(pipe2[0]); // Close unused read end of pipe2

        int received;
        read(pipe1[0], &received, sizeof(received));
        close(pipe1[0]);

        int result = received * 2;
        write(pipe2[1], &result, sizeof(result));
        close(pipe2[1]);

        printf("Child: Received %d, processed it to %d and sent it back.\n", received, result);
        exit(0);
    } else {
        // --- Parent Process ---
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2

        int value = 10;
        write(pipe1[1], &value, sizeof(value));
        close(pipe1[1]);

        int final_result;
        read(pipe2[0], &final_result, sizeof(final_result));
        close(pipe2[0]);

        wait(NULL); // Wait for child to finish
        printf("Parent: Sent %d, received processed result %d from child.\n", value, final_result);
    }

    return 0;
}
