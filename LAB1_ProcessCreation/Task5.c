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
            perror("Fork failed");
            continue; // Try next client
        }

        if (pid == 0) {
            // Child process
            printf("Client %d:\n", i+1);
            printf("  -> My PID is %d\n", getpid());
            printf("  -> My parent’s PID is %d\n", getppid());
            sleep(2); // Simulate some work
            printf("  -> Client %d (PID %d) has completed its task.\n", i+1, getpid());
            exit(0);
        }

        // Parent process
        successful_forks++;
    }

    // Wait for all child processes
    for (int i = 0; i < successful_forks; i++) {
        wait(NULL);
    }

    printf("\nServer: Total number of clients handled = %d\n", successful_forks);
    return 0;
}
