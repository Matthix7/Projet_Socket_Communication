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

static int init_connection(int port){
	
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
	printf("Listage du port %d...\n", PORTConnection);
	
	/* Si la socket ne fonctionne pas */
	if(sock_err == SOCKET_ERROR)
	{
		perror("listen()");
		exit(errno);
	}

	return sock;
}










////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////      CÔTE CLIENT     /////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////












////////////////////////////////////////////////////////////////////////
/////////////////////     MAIN     /////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	
	printf("Succès sock\n");
	
	
	
	return EXIT_SUCCESS;
}
