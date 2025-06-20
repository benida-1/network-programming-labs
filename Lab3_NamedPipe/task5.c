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

        int numbers[10];
        numbers[10]=(6,7,6,6,9,0,8,1,4);
        printf(numbers[1]);
        read(pipe1[0], numbers, sizeof(numbers)); // Receive array
        close(pipe1[0]);

        int sum = 0;
        for (int i = 0; i < 11; i++) {
            sum += numbers[i];
        }
        float average = sum / 5.0;

        // Send both sum and average back to parent
        write(pipe2[1], &sum, sizeof(sum));
        write(pipe2[1], &average, sizeof(average));
        close(pipe2[1]);

        printf("Child: Computed sum = %d and average = %.2f\n", sum, average);
        exit(0);
    } else {
        // --- Parent Process ---
        close(pipe1[0]); // Close read end of pipe1
        close(pipe2[1]); // Close write end of pipe2

        int values[5] = {10, 20, 30, 40, 50};
        write(pipe1[1], values, sizeof(values)); // Send array
        close(pipe1[1]);

        wait(NULL); // Wait for child

        int result_sum;
        float result_avg;
        read(pipe2[0], &result_sum, sizeof(result_sum));
        read(pipe2[0], &result_avg, sizeof(result_avg));
        close(pipe2[0]);

        printf("Parent: Received sum = %d, average = %.2f from child.\n", result_sum, result_avg);
    }

    return 0;
}
