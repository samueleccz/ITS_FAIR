/* Simple UDP server  with bidirectional connection*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct{
	char key[100];
	int value;
}option2;

int main(int argc, char**argv)
{ int sockfd, n;
  extern int errno;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in );
  option2 recvMSG2;
  option2 sendMSG2;
	strcpy(recvMSG2.key, "");
  	strcpy(sendMSG2.key, "");
  if(argc < 2)
  { printf("Use: server listening_PORT");
	return 0;
  }

  if((sockfd=socket(PF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }

  memset(&local_addr,0,sizeof(local_addr));
  local_addr.sin_family = AF_INET;
  local_addr.sin_port=htons(atoi(argv[1]));
  if(bind(sockfd, (struct sockaddr *) &local_addr, len)<0)
  { printf("\nBinding error! Error code n.%d \n",errno);
    return -1;
  }
   char choose[100];
   char linecontrol[100];
	strcpy(linecontrol, "");

   for (;;){
	ssize_t chosing = recvfrom(sockfd, choose, 100, 0, (struct sockaddr*)&remote_addr, &len);
	choose[1] = '\0';
	printf("choose: %s\n", choose);
	if(choose[0] == 's'){
		printf("Selezionata opzione scrittura\n");
		ssize_t recv = recvfrom(sockfd, linecontrol, 100, 0, (struct sockaddr*)&remote_addr, &len);
		printf("FROM IP: %s msg: %s \n", inet_ntoa(remote_addr.sin_addr), linecontrol);

		FILE* file = fopen("keys.txt", "r");
		char line[100];
		char *lineUp;
		int response = 0;

		while(fgets(line, 100, file)){
			lineUp = strtok(line, ":");
			strtok(NULL, ":");
			if(strcmp(lineUp, linecontrol) == 0){
				response = 1;
			}
		}
			if(response == 1){
				printf("chiave trovata, operazione scartata");
				response = 1;
				sendto(sockfd, &response, 4, 0, (struct sockaddr*)&remote_addr, len);
			}else{
				printf("Chiave non trovata, invio risposta al server 1\n");
				sendto(sockfd, &response, 4, 0, (struct sockaddr*)&remote_addr, len);
			}

	}else if(choose[0] == 'l'){
		printf("Selezionata opzione lettura\n");
		ssize_t recv = recvfrom(sockfd, linecontrol, 100, 0, (struct sockaddr*)&remote_addr, &len);
		printf("FROM IP: %s msg: %s \n", inet_ntoa(remote_addr.sin_addr), linecontrol);

		FILE* file = fopen("keys.txt","r");
		char line[100];
		char *strtokker;
		int esit = 0;
		char copy[100] = "";
		while(fgets(line, 100, file)){
			strcpy(copy, line);
			strtokker = strtok(line, ":");
			strtok(NULL, ":");

			if(strcmp(linecontrol, strtokker) == 0){
				printf("Chiave trovata. invio coppia in corso %s\n", copy);
				esit = 1;
				sendto(sockfd, &esit, 4, 0, (struct sockaddr*)&remote_addr, len);
				sendto(sockfd, copy, 100, 0, (struct sockaddr*)&remote_addr, len);
				break;
			}

		}

		if(esit == 0){
			printf("Chiave non trovata, invio esito negativo\n");
			sendto(sockfd, &esit, 100, 0, (struct sockaddr*)&remote_addr, len);
		}

	}else if(choose[0] == 'c'){
		printf("Selezionata opzione cancellazione\n");
		char line[100];
		char *strtokker;
		int esit=0;
		int pointer=0;
		int temp_int=0;
		ssize_t recv = recvfrom(sockfd, linecontrol, 100, 0, (struct sockaddr*)&remote_addr, &len);
		printf("FROM IP: %s msg: %s \n", inet_ntoa(remote_addr.sin_addr), linecontrol);

		FILE* file = fopen("keys.txt", "r");
		FILE* temp = fopen("temp.txt", "w");
		while(fgets(line, 100, file)){
			strtokker = strtok(line, ":");
			strtok(NULL, ":");
			if(strcmp(linecontrol, strtokker) == 0){
				esit = 1;
				printf("Chiave trovata\n");
				pointer = temp_int;
				break;
			}
			temp_int++;
		}

		fclose(file);

		if(esit == 1){
			file = fopen("keys.txt", "r");
			temp_int = 0;
			while(fgets(line, 100, file)){
				if(temp_int != pointer){
					fputs(line, temp);
				}
				temp_int++;
			}
				fclose(file);
				fclose(temp);
				remove("keys.txt");
				rename("temp.txt", "keys.txt");
				printf("Cancellazione effettuata con successo\n");
				sendto(sockfd, &esit, 4, 0, (struct sockaddr*)&remote_addr, len);

		}else{
			printf("Chiave non trovata\n");
			sendto(sockfd, &esit, 4, 0, (struct sockaddr*)&remote_addr, len);

		}
	}
 }
}

