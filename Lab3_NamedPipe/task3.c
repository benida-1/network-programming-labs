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
        printf("Child: Received %d, processed it to %d\n", received, result);

        write(pipe2[1], &result, sizeof(result));
        close(pipe2[1]);

        exit(0);
    } else {
        // --- Parent Process ---
        close(pipe1[0]); // Close unused read end of pipe1
        close(pipe2[1]); // Close unused write end of pipe2

        int value = 10;
        printf("Parent: Sending %d to child...\n", value);
        write(pipe1[1], &value, sizeof(value));
        close(pipe1[1]);

        wait(NULL); // Ensure child has finished writing

        int final_result;
        read(pipe2[0], &final_result, sizeof(final_result));
        close(pipe2[0]);

        printf("Parent: Received processed result %d from child.\n", final_result);
    }

    return 0;
}
