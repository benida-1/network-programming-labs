#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "syncfifo";
    int fd;
    char buffer[100];
    char message[] = "Hello from server with one FIFO!";

    sleep(1); // Simulate delay to ensure client is ready

    // Step 1: Write to FIFO
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("Server: open for writing");
        exit(1);
    }
    write(fd, message, sizeof(message));
    printf("Server: Sent message to client.\n");
    close(fd);

    // Step 2: Reopen FIFO to receive acknowledgment
    fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("Server: open for reading");
        exit(1);
    }
    read(fd, buffer, sizeof(buffer));
    printf("Server: Received acknowledgment: %s\n", buffer);
    close(fd);

    return 0;
}
