///  Code Socket, regroupe toutes les structures et fonctions        ///
///  nécessaires pour la communication par sockets.                  ///
///////////////      Schémas de sockets inspirés de        /////////////
////////////    http://sdz.tdct.org/sdz/les-sockets.html     ///////////


//Inclusions nécessaires
#include "inclusions.h"




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////     CÔTE SERVEUR     /////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////




///////////////////     Initialisation de la connection     ////////////
////////////////////////////////////////////////////////////////////////

int init_connection_server(int port){
	
	/* Socket et contexte d'adressage du serveur */
	SOCKADDR_IN sin;
	SOCKET sock;
	socklen_t recsize = sizeof(sin);

	/* Socket et contexte d'adressage du client */
	SOCKADDR_IN csin;
	SOCKET csock;
	socklen_t crecsize = sizeof(csin);

	int sock_err;

	/* Création d'une socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Si la socket est invalide */
	if(sock == INVALID_SOCKET){
		perror("socket");
		exit(errno);
	}

	/* Configuration */
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

	/* Si la socket ne fonctionne pas */
	if(sock_err == SOCKET_ERROR)
	{
	  perror("bind()");
	  exit(errno);
	}

	/* Démarrage du listage (mode server) */
	sock_err = listen(sock, MAX_CLIENTS);
	printf("Listage du port %d...\n", port);

	/* Si la socket ne fonctionne pas */
	if(sock_err == SOCKET_ERROR)
	{
		perror("listen()");
		exit(errno);
	}

	return sock;
}


///////////////////          Fin de la connection           ////////////
////////////////////////////////////////////////////////////////////////

void end_connection_server(SOCKET sock, SOCKET csock)
{
    printf("Fermeture de la socket client\n");
	closesocket(csock);
	printf("Fermeture de la socket serveur\n");
	closesocket(sock);
	printf("Fermeture du serveur terminée\n");
}


///////////////////       Réception données clients         ////////////
////////////////////   déconnection du client si erreur   ///////////////

int read_from_client(Client* clients, int current, int id_client, SOCKET sock, char *buffer)
{
   int n = recv(sock, buffer, BUF_SIZE - 1, 0);
   Client client = clients[id_client]; 
   
   if( (n == SOCKET_ERROR) || (buffer[0] == 'q'))
   {
      perror("recv()");
      /* if recv error we disconnect the client */
      n = 0;
      
      strncpy(buffer, client.name, BUF_SIZE - 1);
	  removeClient(clients, id_client, &current);
	  strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
	  sendMessage(clients, client, current, buffer, 1); //broadcast alert
   }

   buffer[n] = 0;

   return n;
}


///////////////////          Suppression du client          ////////////
////////////////////////////////////////////////////////////////////////

void removeClient(Client *clients, int to_remove, int *current)
{
	/* we close active sockets */
	closesocket(clients[to_remove].sConnection);
    closesocket(clients[to_remove].sChat);
    closesocket(clients[to_remove].sWind);
    closesocket(clients[to_remove].sList);
    closesocket(clients[to_remove].sUpdate);
	
   /* we remove the client in the array */
   memmove(clients + to_remove, clients + to_remove + 1, (*current - to_remove - 1) * sizeof(Client));
   /* number client - 1 */
   (*current)--;
}



///////////////////      Envoi d'un message au client       ////////////
////////////////////////////////////////////////////////////////////////

void write_to_client(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}


///////////////////    Envoi d'un message en broadcast      ////////////
////////////////////////////////////////////////////////////////////////

void sendMessage(Client *clients, Client sender, int current, const char *buffer, char from_server)
{
   int i = 0;
   char message[BUF_SIZE];
   message[0] = 0;
   for(i = 0; i < current; i++)
   {
      /* we don't send message to the sender */
      if(sender.sChat != clients[i].sChat)
      {
         if(from_server == 0)
         {
            strncpy(message, sender.name, BUF_SIZE - 1);
            strncat(message, " : ", sizeof message - strlen(message) - 1);
         }
         strncat(message, buffer, sizeof message - strlen(message) - 1);
         write_to_client(clients[i].sChat, message);
      }
   }
}





////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////      CÔTE CLIENT     /////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////



///////////////////     Initialisation de la connection     ////////////
////////////////////////////////////////////////////////////////////////

int init_connection_client(const char *address, int port)
{
	/* Création de la socket */
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };
   struct hostent *hostinfo;

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }
   
	/* Configuration de la connexion */
   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;
	
	/* Si le client n'arrive pas à se connecter */
   if(connect(sock,(SOCKADDR *) &sin, sizeof(sin)) == SOCKET_ERROR)
   {
      perror("Impossible de se connecter\n");
      exit(errno);
   }

   return sock;
}



///////////////////          Fin de la connection           ////////////
////////////////////////////////////////////////////////////////////////

void end_connection_client(SOCKET sock)
{
   printf("Fin de communication\n");
   closesocket(sock);
}


///////////////////       Réception données serveur         ////////////
////////////////////////////////////////////////////////////////////////

int read_from_server(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(errno);
   }

   buffer[n] = 0;

   return n;
}



////////////////      Envoi d'un message au serveur      ///////////////
////////////////////////////////////////////////////////////////////////

void write_to_server(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}



////////////////////////////////////////////////////////////////////////
////////////////////////     MAIN     //////////////////////////////////
////////////////////////////////////////////////////////////////////////
/*
int main(int argc, char **argv){
	
	printf("Succès sock\n");
	
	
	
	return EXIT_SUCCESS;
}
*/
