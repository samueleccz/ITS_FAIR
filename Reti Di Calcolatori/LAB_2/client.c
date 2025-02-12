/* Simple UDP client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define N 10

typedef struct{
	char resources[N][100];
	int quantities[N];
	int n;
}resource;

typedef struct{
	char resource[N][100];
	int n;
}resource2;

typedef struct{
	char resource[100];
	int id;
}resource3;


int main(int argc, char**argv)
{ int sockfd, n;
  struct sockaddr_in remote_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  int id = 0;


  if (argc != 3)
  { printf("usage:  UDPclient <remote_IP remote_port>\n");
    return 1;
  }

  if((sockfd=socket(AF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }

  memset(&remote_addr,0,len);
  remote_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr));
  remote_addr.sin_port=htons(atoi(argv[2]));
  int nr = 0;
  char c[100] = "i";
  resource recvMSG;
  resource2 recvMSG2;
  resource3 sendMSG;

  while (1){

	if(c[0] == 'i'){
		sendto(sockfd, c, 100, 0, (struct sockaddr *)&remote_addr, len);
		ssize_t recv = recvfrom(sockfd, &nr, sizeof(nr), 0, (struct sockaddr*)&remote_addr, &len);
		ssize_t recvID = recvfrom(sockfd, &id, sizeof(id), 0, (struct sockaddr*) &remote_addr, &len);
		//printf("%d : %d\n", nr, id);
	}

	printf("Seleziona un operazione: \n");
	fgets(c, 100, stdin);
	sendto(sockfd, c, 100, 0, (struct sockaddr *)&remote_addr, len);


	if(c[0] == 'e'){
		printf("LISTA RISORSE LIBERE: \n");
		ssize_t recv = recvfrom(sockfd, &recvMSG, sizeof(recvMSG), 0, (struct sockaddr*)&remote_addr, &len);

		for(int i=0; i<recvMSG.n; i++){
			printf("%s:%d\n ", recvMSG.resources[i], recvMSG.quantities[i]);
		}
	}

	if(c[0] == 'u'){
		printf("LISTA RISORSE RISERVATE: \n");
		sendto(sockfd, &id, sizeof(id), 0, (struct sockaddr*)&remote_addr, len);

		ssize_t recv = recvfrom(sockfd, &recvMSG2, sizeof(recvMSG2), 0, (struct sockaddr*)&remote_addr, &len);

		for(int i=0; i<recvMSG2.n; i++){
			printf("%s\n", recvMSG2.resource[i]);
		}
	}

	if(c[0] == 'b'){
		printf("SELEZIONA UNA RISORSA DA BLOCCARE: \n");
		fgets(sendMSG.resource, 100, stdin);
		sendMSG.id = id;
			sendMSG.resource[strlen(sendMSG.resource) - 1] = '\0';
			printf("%s:%d\n", sendMSG.resource, sendMSG.id);
		sendto(sockfd, &sendMSG, sizeof(sendMSG), 0, (struct sockaddr*)&remote_addr, len);

		char r[100];

			ssize_t recv2 = recvfrom(sockfd, r, sizeof(r), 0, (struct sockaddr*)&remote_addr, &len);
			printf("%s\n", r);


	}if(c[0] == 'q'){
		break;
	}
  }
}
