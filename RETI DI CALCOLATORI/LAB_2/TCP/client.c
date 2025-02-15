/* Sample TCP client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define N 10

typedef struct{
	int id;
	char resource[100];
}block_resource;

typedef struct{
	char resource[N][100];
	int quantity[N];
	int count;
}list_resource;


int main(int argc, char**argv)
{ int sockfd,n;
  struct sockaddr_in local_addr, dest_addr;
  char sendline[1000];

   block_resource sendMSG;
   list_resource recvMSG2;

   int id = 0;

  if (argc != 3)
  { printf("usage:  client IP_address <Port\n");
    return 1;
  }

  sockfd=socket(AF_INET,SOCK_STREAM,0);

  memset( &dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
  dest_addr.sin_port = htons(atoi(argv[2]));

  connect(sockfd, (struct sockaddr *) &dest_addr, sizeof(dest_addr));

	strcpy(sendline, "i");
	send(sockfd, sendline, strlen(sendline), 0);

	if(sendline[0] == 'i'){
		printf("INIZIALIZZAZIONE DELL'HOST IN CORSO\n");
		ssize_t recvfrom = recv(sockfd, &id, sizeof(id), 0);
		printf("id: %d\n", id);
	}

  while (1)
  {
    printf("INSERISCI UN OPERZIONE: ");
    fgets(sendline, 100, stdin);
    send(sockfd, sendline, strlen(sendline), 0);

   	if(sendline[0] == 'u'){
		send(sockfd, &id, sizeof(id), 0);

   	 	ssize_t recvfrom = recv(sockfd, &recvMSG2, sizeof(recvMSG2), 0);
	 	printf("RISORSE RISERVATE ALL'UTENTE \n");

		for(int i=0; i<recvMSG2.count; i++){
			printf("RISORSA [%d]: %s:%d\n", i, recvMSG2.resource[i], recvMSG2.quantity[i]);
		}

   	}else if(sendline[0] == 'l'){
		printf("RISORSE LIBERE\n");

		ssize_t recvfrom = recv(sockfd, &recvMSG2, sizeof(recvMSG2), 0);

		for(int i=0; i<recvMSG2.count; i++){
			printf("RISORSA [%d]: %s:%d\n", i, recvMSG2.resource[i], recvMSG2.quantity[i]);

		}
	}else if(sendline[0] == 'b'){
		printf("SELEZIONA RISORSA DA BLOCCARE: \n");
		fgets(sendMSG.resource, 100, stdin);
		sendMSG.resource[strlen(sendMSG.resource)-1] = '\0';

		sendMSG.id = id;

		send(sockfd, &sendMSG, sizeof(sendMSG), 0);

		char response[100];

		ssize_t recv_r= recv(sockfd, response, sizeof(response), 0);

		printf("%s\n", response);
	}else if(sendline[0] == 'q'){
		break;
	}
    }
}
