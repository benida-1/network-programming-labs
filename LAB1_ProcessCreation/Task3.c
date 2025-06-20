#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  int num_clients;
  printf("Enter number of Clients to handle: ");
  scanf("%d", &num_clients);
  
  for (int i=0; i<num_clients; i++){
    pid_t pid = fork();
    
    if(pid == 0){
      //Child process (Client)
      printf("Client %d: Handling request. PID = %d, Parent PID = %d\n", i+1, getpid(), getppid());
      sleep(2);
      printf("Client %d (PID = %d) completed request.\n", i+1, getpid());
      exit(0);
    }
    //Parent process continues to create more clients 
  }
  
  //Parents waits for all clients to finish
  for(int i = 0; i< num_clients; i++){
    wait(NULL);
  }
  
  printf("Server: All client requests have been handled.\n");
  return 0;
  
}
