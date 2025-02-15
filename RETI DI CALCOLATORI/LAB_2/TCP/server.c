/* Sample TCP server */

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
{ int sockfd,newsockfd,n;
  struct sockaddr_in local_addr,remote_addr;
  socklen_t len;
  char mesg[1000];

   block_resource recvMSG;
   list_resource sendMSG2;

  if(argc < 2)
  {	 printf("Use: server listeing_PORT");
	 return 0;
  }

  if((sockfd=socket(AF_INET,SOCK_STREAM,0)) <0)
  { printf("\nErrore nell'apertura del socket");
    return -1;
  }
  memset((char *) &local_addr,0,sizeof(local_addr));
  local_addr.sin_family = AF_INET;
  local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  local_addr.sin_port = htons(atoi(argv[1]));

  if(bind(sockfd, (struct sockaddr *) &local_addr, sizeof(local_addr))<0)
  { printf("\nErrore nel binding. Errore %d \n",errno);
    return -1;
  }

	int id=0;
  listen(sockfd,5);

  for(;;)
  { len = sizeof(remote_addr);
    newsockfd = accept(sockfd,(struct sockaddr *)&remote_addr, &len);

    if (fork() == 0)
    { close(sockfd);
         for(;;)
      { n = recv(newsockfd,mesg,100,0);
        if(n==0) return 0;
        mesg[n] = 0;
        printf("\nPid=%d: received from %s:%d the following: %s\n",getpid(), inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), mesg );

	if(mesg[0] == 'i'){
		id++;
		printf("INIZIALIZZAZIONE DI %s in corso\n", inet_ntoa(remote_addr.sin_addr));
		ssize_t sendto = send(newsockfd, &id, sizeof(id), 0);
	}
	else if(mesg[0] == 'u'){
		printf("INVIO LISTA\n");
		int new_id;
		ssize_t recvfrom = recv(newsockfd, &new_id, sizeof(new_id), 0);
		printf("new_id: %d\n", new_id);
		FILE* file = fopen("resource.txt", "r");
		char line[100];
		char* tok_r;
		char* tok_q;
		char* tok_id;
		int count = 0;
		while(fgets(line, 100, file)){
			printf("line: %s\n", line);
			tok_r = strtok(line, "#");
			tok_q = strtok(NULL, "#");
			tok_id = strtok(NULL,  "#");

			while(tok_id){
				if((atoi(tok_id) == new_id)){
					strcpy(sendMSG2.resource[count], tok_r);
					sendMSG2.quantity[count] = atoi(tok_q);
					printf("resource[%d] = %s\n", count, sendMSG2.resource[count]);
					count++;
					break;

				}

				tok_id = strtok(NULL,  "#");
			}

  		}
			fclose(file);
			sendMSG2.count = count;
			send(newsockfd, &sendMSG2, sizeof(sendMSG2), 0);

	}else if(mesg[0] == 'l'){
		printf("RICHIESTA LISTA RISORSE LIBERE\n");

		FILE* file = fopen("resource.txt", "r");
		char line[100];
		char* tok_r;
		char* tok_q;
		char* tok_id;
		int count = 0;

		while(fgets(line, 100, file)){
			printf("line: %s\n", line);
			tok_r = strtok(line, "#");
			tok_q = strtok(NULL, "#");

			if(atoi(tok_q) > 0){
				strcpy(sendMSG2.resource[count], tok_r);
				sendMSG2.quantity[count] = atoi(tok_q);
  				printf("%s:%d\n", sendMSG2.resource[count], sendMSG2.quantity[count]);
				count++;
			}
		}
			fclose(file);
			sendMSG2.count = count;
			send(newsockfd, &sendMSG2, sizeof(sendMSG2), 0);

	}else if(mesg[0] == 'b'){
		printf("RICHIESTO BLOCCO RISORSA\n");

		ssize_t recvfrom = recv(newsockfd, &recvMSG, sizeof(recvMSG), 0);

		FILE* read = fopen("resource.txt", "r");
		char line[100];
		int count = 0;
		char* tok_r;
		char* tok_q;
		char copy[100];
			strcpy(copy, "m");
		int b = 0;
		int row = 0;
		int qt = 0;
		char copy_line[100];
			strcpy(copy_line, "m");

		while(fgets(line, 100, read)){
			strcpy(copy_line, line);
			tok_r = strtok(line, "#");
			tok_q = strtok(NULL, "#");

			if(strcmp(tok_r, recvMSG.resource) == 0){
				if(atoi(tok_q) > 0){
					b = 1;
					row = count;
					qt = atoi(tok_q);
					strcpy(copy, tok_r);
					strcat(copy, "#");
					break;
				}
			}

			count++;
		}

		fclose(read);

		FILE* temp = fopen("temp.txt", "w");
		FILE* file = fopen("resource.txt", "r");

		char line2[100];
		int count2 = 0;
		char response[100];

		if(b == 1){
			while(fgets(line2, 100, file)){
				if(count2 != row){
					fputs(line2, temp);
				}
				count2++;
			}

			qt=qt-1;
			char qts[10];
			sprintf(qts, "%d", qt);
			strcat(copy, qts);
			strcat(copy, "#");

			printf("COPY: %s\n", copy_line);
			printf("COMPLETE: %s\n", copy);

			char *tokker;
			char ids[100];
				strcpy(ids, " ");
			int count_h = 0;
			int indice = 0;
			int in = 0;

			while(in < strlen(copy_line)){
				if(copy_line[in] == '#'){
					count_h ++;
				}
				if(count_h == 2){
					indice = in;
					break;
				}
				in++;
			}
				indice = indice + 1;
			int counter_copy = indice;
			int counter_ids = 0;


			while(counter_copy < (strlen(copy_line)-1)){
				ids[counter_ids] = copy_line[counter_copy];
				ids[counter_ids+1] = '\0';
				counter_ids++;
				counter_copy++;
			}


			char id_n[10];
				sprintf(id_n, "%d", recvMSG.id);

			if(strcmp(ids, " ") == 0){
				strcat(copy, id_n);
				strcat(copy, "#");
				copy[strlen(copy)] = '\n';
			}else{
				strcat(copy, ids);
				strcat(copy, id_n);
				strcat(copy, "#");
				copy[strlen(copy)] = '\n';
			}
				printf("COMPLETE FULL: %s\n", copy);

			fputs(copy, temp);

			fclose(temp);
			fclose(file);

			strcpy(response, "RISORSA BLOCCATA CON SUCCESSO");
			send(newsockfd, response, sizeof(response), 0);
			strcpy(copy, " ");
			strcpy(ids, " ");


			remove("resource.txt");
			rename("temp.txt", "resource.txt");
		}else{
			printf("RISORSA NON DISPONIBILE (ADDENTE O BLOCCATA)\n");
			strcpy(response, "RISORSA NON DISPONIBILE (ADDENTE O BLOCCATA)");
			send(newsockfd, response, sizeof(response), 0);
			fclose(temp);
			fclose(file);
		}
	}


    }
      return 0;
    }
	else
      close(newsockfd);
  }
}
