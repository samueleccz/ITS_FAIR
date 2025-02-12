/* Simple UDP server  with bidirectional connection*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
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
  extern int errno;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in );
  int id = 0;

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


	FILE *fileN = fopen("resource.txt", "r");
	char lineN[100];
	int nr = 0;
		while(fgets(lineN, 100, fileN)){
			nr++;
		}

	resource sendMSG;
	resource2 sendMSG2;
	resource3 recvMSG;


 for (;;)
  {

	char choose[100];
	ssize_t recv = recvfrom(sockfd, choose, 100, 0, (struct sockaddr*)&remote_addr, &len);

		if(choose[0] == 'i'){
			sendto(sockfd, &nr, sizeof(nr), 0, (struct sockaddr*)&remote_addr, len);
			id++;
			sendto(sockfd, &id, sizeof(id), 0, (struct sockaddr*)&remote_addr, len);
		}

		if(choose[0] == 'e'){
			printf("Ritorno elenco\n");
			FILE* file = fopen("resource.txt", "r");
			char line[100];
			char *tok_resource;
			int tok_quantity;
			char *temp_tok;
			int counter=0;

			while(fgets(line, 100, file)){
				tok_resource = strtok(line, "#");
				temp_tok = strtok(NULL, "#");

				tok_quantity = atoi(temp_tok);

				if(tok_quantity > 0){
					strcpy(sendMSG.resources[counter], tok_resource);
					sendMSG.quantities[counter] = tok_quantity;
					printf(" INVIATA = %s:%d\n", sendMSG.resources[counter], sendMSG.quantities[counter]);
					counter++;
				}
			}

			sendMSG.n = counter;
			sendto(sockfd, &sendMSG, sizeof(sendMSG), 0, (struct sockaddr*)&remote_addr, len);

		}else if(choose[0] == 'u'){
			int recvid = 0;
			printf("Selezioneto user resources\n");
			ssize_t recv = recvfrom(sockfd, &recvid, sizeof(recvid), 0, (struct sockaddr*)&remote_addr, &len);
			printf("%d\n", recvid);
			FILE* read = fopen("resource.txt", "r");
			char* tok1;
			char* tok2;
			char* tok_id;
			char line[100];
			sendMSG2.n = 0;
			int counter = 0;

			while(fgets(line, 100, read)){
				tok1 = strtok(line, "#");
				tok2 = strtok(NULL, "#");
				tok_id = strtok(NULL, "#");
				while(tok_id){
					if(atoi(tok_id) == recvid){
						tok1[strlen(tok1)] = '\0';
						strcpy(sendMSG2.resource[counter], tok1);
						sendMSG2.n++;
						printf("RISORSA RISERVATA= %s , NUMERO= %d\n", sendMSG2.resource[counter], sendMSG2.n);
						counter++;
						break;
					}

					tok_id = strtok(NULL, "#");
				}
			}
			sendto(sockfd, &sendMSG2, sizeof(sendMSG2), 0, (struct sockaddr*)&remote_addr, len);

		}else if(choose[0] == 'b'){
			ssize_t recv = recvfrom(sockfd, &recvMSG, sizeof(recvMSG), 0, (struct sockaddr*)&remote_addr, &len);
			printf("USER:%d HA RICHIESTO IL BLOCCO DELLA RISORSA:%s\n", recvMSG.id, recvMSG.resource);
			FILE* read = fopen("resource.txt", "r");
			char line[100];
			char *tok_r;
			char *tok_q;
			int q;
			char *quant;
			int bol = 0;

			int temp_c = 0;
			int counter = 0;
			char copy_l[100];

			char copy[100];

			while(fgets(line, 100, read)){
				strcpy(copy_l, line);
				//printf("COPY_L: %s\n", copy_l);
				tok_r = strtok(line, "#");

				if(strcmp(tok_r, recvMSG.resource) == 0){
					counter = temp_c;
					tok_q = strtok(NULL, "#");
					q = atoi(tok_q);

					if(q > 0){
						bol = 1;
					}

					break;
				}
				temp_c++;
			}

			int temp_counter = 0;
			int temp_counter2 = 0;
			int indice = 0;

			//printf("LEN: %d\n", strlen(copy_l));

			while(temp_counter != strlen(copy_l)){
				//printf("COUNTER: %d, COPY[]: %c\n", temp_counter, copy_l[temp_counter]);
				if(copy_l[temp_counter] == '#'){
					temp_counter2++;
					//printf("temp_counter2: %d, indice#: %d\n", temp_counter2, temp_counter);

					if(temp_counter2 == 2){
						indice = temp_counter;
					}
				}

				temp_counter++;
			}

				//printf("INDICE #: %d\n", indice);


			int cunter = indice+1;
			char copy_id[100];
				strcpy(copy_id, "");
			int counter_copy = 0;
				//strcpy(copy_id, "c");

			//printf("%s : %d\n", copy_id, strlen(copy_id));

			while(cunter < (strlen(copy_l)-1)){
				//printf("copyl[%d]: %c\n", cunter, copy_l[cunter]);

				copy_id[counter_copy] = copy_l[cunter];

				cunter++;
				counter_copy++;
			}

			//copy_id[strlen(copy_id)-1] = '\0';
			printf("copy id %s\n", copy_id);

				char qt[10];
					strcpy(qt, " ");
			if(strcmp(copy_id," ") != 0){
				printf("COPY PIENA\n");
				strcat(copy, tok_r);
				strcat(copy, "#");
					int qn = q-1;
					sprintf(qt, "%d", qn);
				strcat(copy, qt);
				strcat(copy, "#");
				strcat(copy, copy_id);
					char new_id[10];
					sprintf(new_id, "%d", recvMSG.id);
				strcat(copy, new_id);

				for(int i=0; i<strlen(copy); i++){
					copy[i] = copy[i+1];
				}
				copy[strlen(copy)] = '\n';
			}else{
				printf("COPY VUOTA\n");
				strcat(copy, tok_r);
				strcat(copy, "#");
					int qn = q-1;
					sprintf(qt, "%d", qn);
				strcat(copy, qt);
				strcat(copy, "#");
					char new_id[10];
					sprintf(new_id, "%d", recvMSG.id);
				strcat(copy, new_id);

				for(int i=0; i<strlen(copy); i++){
					copy[i] = copy[i+1];
				}
				copy[strlen(copy)] = '\n';
			}

			printf("COMPLETE: %s\n", copy);


			strcpy(copy_id, " ");
			strcpy(tok_r, " ");
			strcpy(tok_q, " ");
			//printf("copy id %s\n", copy_id);

			fclose(read);

			char response[100];
			if(bol == 1){
				printf("RISORSA LIBERA, BLOCCAGGIO IN CORSO\n");


				FILE* file = fopen("resource.txt", "r");
				FILE* temp = fopen("temp.txt", "w");
				char line[100];
				int row = 0;

				printf("INDICE RIGA: %d\n", counter);

					while(fgets(line, 100, file)){
						if(row != counter){
							fputs(line, temp);
						}
						row++;
					}
					fputs(copy, temp);
					strcpy(copy, " ");

					fclose(file);
					fclose(temp);

					remove("resource.txt");
					rename("temp.txt", "resource.txt");

				strcpy(response, "RISORSA BLOCCATA CON SUCCESSO	");
				sendto(sockfd, response, sizeof(response), 0, (struct sockaddr*)&remote_addr, len);
			}else{
				printf("RISORSA OCCUPATA O INESISTENTE\n");
				strcpy(response, "RISORSA OCCUPATA O INESISTENTE");
				sendto(sockfd, response, sizeof(response), 0, (struct sockaddr*)&remote_addr, len);
			}
		}
  }
}

