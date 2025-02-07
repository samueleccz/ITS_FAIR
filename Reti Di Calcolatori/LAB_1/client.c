/* Simple UDP client */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

typedef struct{
	int value;
	char key[100];
}option1;

int main(int argc, char**argv)
{ int sockfd, n;
  struct sockaddr_in remote_addr;

  option1 sendMSG;
  option1 recvMSG;
  char read[100];

  socklen_t len = sizeof(struct sockaddr_in);

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

char choose[100];
char msg[100];
char value[100];
char response[100];


while(1){
	printf("Scegli un opzione: ");
	fgets(choose, 100, stdin);

	if(choose[0] == 's'){
		sendto(sockfd, choose, strlen(choose), 0, (struct sockaddr *) &remote_addr, len);
		printf("scegli una chiave: ");
		fgets(msg, 100, stdin);
		printf("scegli un valore: ");
		fgets(value, 100, stdin);

		strcpy(sendMSG.key, msg);

		sendMSG.key[strlen(sendMSG.key)-1] = '\0';
		sendMSG.value = atoi(value);
		sendto(sockfd, &sendMSG, sizeof(sendMSG), 0, (struct sockaddr *) &remote_addr, len);

		ssize_t recv = recvfrom(sockfd, response, 100, 0, (struct sockaddr*) &remote_addr, &len);
		printf("FROM IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), response);

		ssize_t recv2 = recvfrom(sockfd, response, 100, 0, (struct sockaddr*)&remote_addr, &len);
		printf("FROM IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), response);

	}else if(choose[0] == 'l'){
		sendto(sockfd, choose, strlen(choose), 0, (struct sockaddr *) &remote_addr, len);
		printf("Scegli una chiave: ");
		fgets(msg, 100, stdin);
		sendMSG.value=0;
		msg[strlen(msg)-1] = '\0';
		strcpy(sendMSG.key, msg);
		int esit=0;

		ssize_t recv = recvfrom(sockfd, response, 100, 0, (struct sockaddr*)&remote_addr, &len);
		printf("FROM IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), response);

	}else if(choose[0] == 'c'){
		sendto(sockfd, choose, strlen(choose), 0, (struct sockaddr *) &remote_addr, len);
		printf("Scegli una chiave: ");
		char key[100];
		fgets(key, 100, stdin);
		key[strlen(key)-1]= '\0';
		strcpy(sendMSG.key, key);
		sendMSG.value = 0;
		sendto(sockfd, &sendMSG, sizeof(sendMSG), 0, (struct sockaddr *) &remote_addr, len);

		ssize_t recv = recvfrom(sockfd, response, 100, 0 , (struct sockaddr*)&remote_addr, &len);
		printf("FROM IP:%s Port:%d msg:%s \n", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), response);
	}else if(choose[0] == 'e')
		break;

	}
}
