#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int num_clients;
    printf("Enter number of clients to handle: ");
    scanf("%d", &num_clients);

    int successful_forks = 0;

    for (int i = 0; i < num_clients; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            // fork failed
            perror("Error: Failed to create child process");
            continue; // continue creating other clients
        }

        if (pid == 0) {
            // Child process
            printf("Client %d: Handling request. PID = %d, Parent PID = %d\n", i+1, getpid(), getppid());
            sleep(2);
            printf("Client %d (PID = %d) completed request.\n", i+1, getpid());
            exit(0);
        }

        // Parent process
        successful_forks++;
    }

    // Wait for all successfully created child processes
    for (int i = 0; i < successful_forks; i++) {
        wait(NULL);
    }

    printf("Server: All client requests have been handled.\n");
    return 0;
}
