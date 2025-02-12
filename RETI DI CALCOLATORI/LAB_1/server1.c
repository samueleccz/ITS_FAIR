/* Simple UDP server  with bidirectional connection*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct{
	int value;
	char key[100];
}option1;

typedef struct{
	int value;
	char key[100];
}option2;

int main(int argc, char**argv)
{ int sockfd, n;
  extern int errno;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in );

   option1 recvMSG;
   option1 sendMSG;

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
   char choice[10];

////////////////////////////////////////////
	int sockfd2;
	struct sockaddr_in remote_server;
	socklen_t len2 = sizeof(struct sockaddr_in);

	sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&remote_server, 0, len2);
	remote_server.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.2.3", &(remote_server.sin_addr));
	remote_server.sin_port = htons(8080);

	option2 sendMSG2;
	option2 recvMSG2;
////////////////////////////////////////////

  for (;;)
  {	ssize_t cho = recvfrom(sockfd, choice, 10, 0, (struct sockaddr *) &remote_addr, &len);

	if(choice[0] == 's'){
		printf("Selezionata opzione scrittura, attendo dati\n");
		ssize_t recv_size = recvfrom(sockfd, &recvMSG, sizeof(recvMSG), 0,(struct sockaddr*) &remote_addr, &len);
		printf("From IP:%s Port:%d key:%s value:%d \n", inet_ntoa(remote_addr.sin_addr),  ntohs(remote_addr.sin_port), recvMSG.key, recvMSG.value);

		FILE *file = fopen("keys.txt", "r");
		char line[100];
		char msg[100];
		char *lineUp;
		int b = 0;
		while(fgets(line, 100, file)){
			lineUp = strtok(line, ":");
			strtok(NULL, ":");

			if(strcmp(lineUp, recvMSG.key) == 0){
				printf("chiave trovata, operazione scartata\n");
				strcpy(msg, "Chiave Presente, operazione rifiutata");
				sendto(sockfd, msg, 100, 0, (struct sockaddr*) &remote_addr, len);
				b = 1;
				break;
			}
		}
				fclose(file);

		if(b == 0){
			printf("dobbiamo mandare all'altro server per il controllo\n");
			//SERVER ESTERNO
			sendto(sockfd2, choice, 100, 0, (struct sockaddr*) &remote_server, len2);
			sendto(sockfd2, recvMSG.key, 100, 0, (struct sockaddr*) &remote_server, len2);
			int resp = 0;
			//
			ssize_t recvResp = recvfrom(sockfd2, &resp, 4, 0, (struct sockaddr*)&remote_server, &len2);
			if(resp == 1){
				strcpy(msg, "Operazione rifiutata, chiave già presente nel server2");
				sendto(sockfd, msg, 100, 0, (struct sockaddr *) &remote_addr, len);
			}else{
				FILE* write = fopen("keys.txt", "a");
				char newline[100];
				strcpy(newline, recvMSG.key);
				strcat(newline, ":");
				char number[10];
				sprintf(number, "%d", recvMSG.value);
				strcat(newline, number);
				strcat(newline, "\n");
				fputs(newline, write);
				fclose(write);
				strcpy(msg, "Scrittura avvenuta con successo");
				sendto(sockfd, msg, 100, 0, (struct sockaddr *) &remote_addr, len);
			}
		}

	}else if(choice[0] == 'l'){
		printf("Scelta opzione lettura, attendo dati\n");
		ssize_t recv = recvfrom(sockfd, &recvMSG, sizeof(recvMSG), 0, (struct sockaddr*) &remote_addr, &len);
		printf("From IP:%s Port:%d key:%s value:%d \n", inet_ntoa(remote_addr.sin_addr),  ntohs(remote_addr.sin_port), recvMSG.key, recvMSG.value);
		FILE* file = fopen("keys.txt", "r");
		char *key;
		char line[100];
		char copy[100];
		char copy2[100];
			strcpy(copy2, "");
		char msg1[100];
		int bl = 0;
		while(fgets(line, 100, file)){

			strcpy(copy, line);

			key = strtok(line, ":");
			strtok(NULL, ":");

			if(strcmp(key, recvMSG.key) == 0){
				printf("Chiave trovata, %s\n", copy);
				sendto(sockfd, copy, 100, 0, (struct sockaddr*)&remote_addr, len);
				bl=1;
				break;
			}
		}

		if(bl == 0){
			printf("Ricerca nel secondo server in corso\n");
			sendto(sockfd2, choice, 100, 0, (struct sockaddr*) &remote_server, len2);
			sendto(sockfd2, recvMSG.key, 100, 0, (struct sockaddr*)&remote_server, len2);
			int esit = 0;
			ssize_t recvesit = recvfrom(sockfd2, &esit, 4, 0, (struct sockaddr*)&remote_server, &len);

			if(esit == 0){
				printf("Il secondo server non ha trovato nulla\n");
				strcpy(copy2, "Non è sta trovata\n");
				sendto(sockfd, copy2, 100, 0, (struct sockaddr*)&remote_addr, len);
			}else{
				printf("Il secondo server ha trovato la chiave\n");
				ssize_t recv2 = recvfrom(sockfd2, &copy2, 100, 0, (struct sockaddr*)&remote_server, &len2);
				printf("%s\n", copy2);
				sendto(sockfd, copy2, 100, 0, (struct sockaddr*)&remote_addr, len);
			}
		}

		fclose(file);
	}else if(choice[0] = 'c'){
		printf("Scelta opzione cancellazione, attendo dati\n");
		ssize_t recv = recvfrom(sockfd, &recvMSG, sizeof(recvMSG), 0, (struct sockaddr*)&remote_addr, &len);
		printf("From IP:%s Port:%d key:%s value:%d \n", inet_ntoa(remote_addr.sin_addr),  ntohs(remote_addr.sin_port), recvMSG.key, recvMSG.value);
		FILE* file = fopen("keys.txt", "r");
		FILE* temp = fopen("temp.txt", "w");
		char line[100];
		char *temp_s;
		int bol = 0;
		int temp_int = 0;
		int pointer = 0;

		char msg[100];

		while(fgets(line, 100, file)){
			temp_s = strtok(line, ":");
			strtok(NULL, ":");
			if(strcmp(temp_s, recvMSG.key)== 0){
				pointer = temp_int;
				printf("Chiave trovata alla riga: %d\n", pointer);
				bol = 1;
				break;
			}
			temp_int++;
		}

		fclose(file);

		if(bol == 1){
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
			printf("cancellazione eseguita con successo\n");
			strcpy(msg, "Cancellazione eseguita");
			sendto(sockfd, msg, 100, 0, (struct sockaddr*)&remote_addr, len);
		}else{
			printf("controllo server due\n");
			sendto(sockfd2, choice, 100, 0, (struct sockaddr*) &remote_server, len2);
			sendto(sockfd2, recvMSG.key, 100, 0, (struct sockaddr*)&remote_server, len2);
			int esit2 = 0;
			ssize_t recvresp = recvfrom(sockfd2, &esit2, 4, 0, (struct sockaddr*)&remote_server, &len2);

			if(esit2 == 1){
				strcpy(msg, "Cancellazione eseguita nel secondo server");
				sendto(sockfd, msg, 100, 0, (struct sockaddr*)&remote_addr, len);
			}else{
				strcpy(msg, "Cancellazione non eseguita, chiave inesistente");
				sendto(sockfd, msg, 100, 0, (struct sockaddr*)&remote_addr, len);
			}
		}
	}
  }
}

