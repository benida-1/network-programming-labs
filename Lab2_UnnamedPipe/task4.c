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
        close(pipe1[1]); // Close write end of pipe1
        close(pipe2[0]); // Close read end of pipe2

        int numbers[5];
        read(pipe1[0], numbers, sizeof(numbers)); // Read entire array
        close(pipe1[0]);

        int sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += numbers[i];
        }

        write(pipe2[1], &sum, sizeof(sum)); // Send sum back
        close(pipe2[1]);

        printf("Child: Computed sum = %d\n", sum);
        exit(0);
    } else {
        // --- Parent Process ---
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        int values[5] = {1, 2, 3, 4, 5};
        write(pipe1[1], values, sizeof(values)); // Send array
        close(pipe1[1]);

        wait(NULL); // Wait for child

        int result;
        read(pipe2[0], &result, sizeof(result)); // Read result
        close(pipe2[0]);

        printf("Parent: Received sum = %d from child.\n", result);
    }

    return 0;
}
