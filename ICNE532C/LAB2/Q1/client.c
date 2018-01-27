#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
int main(){
	int clientSocket, portNum, nBytes;
	char buffer[100001];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	addr_size = sizeof(serverAddr);
	int limit;
	printf("Enter a message :\n");
	scanf("%s", buffer);
	printf("Enter max data size in a packet :\n");
	scanf("%d", &limit);

	int tot_len = strlen(buffer);
	int ct = 1;
	unsigned char* ptr = (unsigned char*) buffer;
	while(tot_len){

	printf("Fragment no : %d\n", ct);
	clock_t t;

	int size_pck;
	if(tot_len >= limit) size_pck = limit;
	else size_pck = tot_len;
	sendto(clientSocket,ptr,size_pck,0,(struct sockaddr *)&serverAddr,addr_size);

	printf("Sent fragment :%d , data: ", ct);

	for(int i=0;i<size_pck;i++) printf("%c", ptr[i]);
	printf("\n\n");
	ptr = ptr + size_pck;
	tot_len -= size_pck;
	ct++;
	sleep(1);
	printf("Received from server : %s\n",buffer);

  }
  close(clientSocket);
  return 0;
}
