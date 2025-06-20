#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "syncfifo";
    int fd;
    char buffer[100];
    char ack[] = "ACK from client (one FIFO)";

    sleep(2); // Simulate client readiness

    // Step 1: Open FIFO to read message
    fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("Client: open for reading");
        exit(1);
    }
    read(fd, buffer, sizeof(buffer));
    printf("Client: Received message: %s\n", buffer);
    close(fd);

    // Step 2: Reopen FIFO to send acknowledgment
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("Client: open for writing");
        exit(1);
    }
    write(fd, ack, sizeof(ack));
    printf("Client: Sent acknowledgment to server.\n");
    close(fd);

    return 0;
}
