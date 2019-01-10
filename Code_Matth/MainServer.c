/// Code Main, regroupe toutes les fonctionnalités nécessaires       ///
/// au projet actuellement mises en place pour le fonctionnement     ///
/// côté serveur.                                                     ///


//Inclusions nécessaires
#include "inclusions.h"





////////////////////////////////////////////////////////////////////////
/////////////////////     MAIN     /////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	int a = A;  //Attention gestion étrange des define: nécessite changement élémentaire ici pour être pris en compte
	printf("Succès global serveur, %d\n\n", a);
	
	char buffer[BUF_SIZE];
	int current = 0; //Nombre actuel de clients
	Client clients[MAX_CLIENTS]; //Liste des clients
	
	fd_set rdfs; 
	
	/* creation of service sockets */
	SOCKET socketConnection = init_connection_server(PORTConnection);
	SOCKET socketChat = init_connection_server(PORTChat);
	
	int max = socketConnection;
	max = socketChat > max ? socketChat : max;
	
	while (1) {
		int i = 0;
		FD_ZERO(&rdfs);

		/* add STDIN_FILENO */
		FD_SET(STDIN_FILENO, &rdfs);
		
		/* add connection socket */
		FD_SET(socketChat, &rdfs);
		FD_SET(socketConnection, &rdfs);
		
		/* add socket for each client */
		for(i = 0; i < current; i++){
			FD_SET(clients[i].sChat, &rdfs);
			FD_SET(clients[i].sConnection, &rdfs);
		}
		
		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1){
			perror("select()");
			exit(errno);
		}
		
		/* something from standard input : i.e keyboard */
		if(FD_ISSET(STDIN_FILENO, &rdfs))
		{
			/* stop process when type on keyboard */
			break;
		}
		
		else if(FD_ISSET(socketConnection, &rdfs)){
			/* Un nouveau client se connecte aux services */
			printf("Patientez pendant qu'un client se connecte sur le port %d...\n", PORTConnection);
			SOCKADDR_IN csin = { 0 };
			socklen_t crecsize = sizeof(csin);
			SOCKET cConnectionSock = accept(socketConnection, (SOCKADDR *)&csin, &crecsize);
			printf("Un client se connecte avec la socket %d de %s:%d\n", cConnectionSock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
			
			if(cConnectionSock == SOCKET_ERROR){
				perror("accept()");
				continue;
			}
			
			
			int cChatSock = accept(socketChat, (SOCKADDR *)&csin, &crecsize);
			
			/* On complète les services du client et ses infos*/
			Client c = {NULL};
			c.sConnection = cConnectionSock;
			c.sChat = cChatSock;
			
			/* after connecting the client sends its name */
			if(read_from_client(cConnectionSock, buffer) == -1){
				/* disconnected */
				continue;
			}
			
			strncpy(c.name, buffer, BUF_SIZE - 1);
			clients[current] = c;
			current++;	
			printf("Nom recu: %s \n", c.name);
			max = cConnectionSock > max ? cConnectionSock : max;
			max = cChatSock > max ? cChatSock : max;
			FD_SET(cChatSock, &rdfs);
		}	
		
		else {
			int i = 0;
			for(i = 0; i < current; i++){
				
				// a client is talking 
				if(FD_ISSET(clients[i].sChat, &rdfs)) {
					
					Client client = clients[i];
					int c = read_from_client(clients[i].sChat, buffer);
					
					//client disconnected 
					if( c == 0 ) {
						
						strncpy(buffer, client.name, BUF_SIZE - 1);
						strncat(buffer, " absent !", BUF_SIZE - strlen(buffer) - 1);
						printf("Message envoyé : %s\n", client.name);
						sendMessage(clients, client, current, buffer, 1); //broadcast alert
						closesocket(clients[i].sChat);
						removeClient(clients, i, &current);
						printf("Il reste %d clients\n", current);
					}
					
					else{
						sendMessage(clients, client, current, buffer, 0);
					}
					break;
				}
			}
		}
	}
	
	clearClients(clients, current);
	end_connection_server(socketConnection);
	end_connection_server(socketChat);
	printf("Fermeture du serveur terminée\n");
	
	return EXIT_SUCCESS;
}