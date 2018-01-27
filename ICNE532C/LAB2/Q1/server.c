#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  char assem[100000];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  addr_size = sizeof(serverStorage);
  
  strcpy(assem, " ");
  int len,limit;
  int ct = 1;
  while(1){
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
    strcat(assem, buffer);
    printf("Last Fragment No. Added %d   data fragment added \n %s \n\n data till now %s\n\n", ct, buffer, assem);
    ct++;
    len += limit; 
  }
  exit(0);
  return 0;
}
