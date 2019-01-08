/// Code Socket, regroupe toutes les structures et fonctions        ///
/// nécessaires pour la communication par sockets.                  ///


////////////////////////////////////////////////////////////////////////
///////////      Paramètres communication côté serveur     /////////////
////////////////////////////////////////////////////////////////////////
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#define PORTConnection  6530
#define MAX_CLIENTS 	100
#define BUF_SIZE	1024


int init_connection(int port);

////////////////////////////////////////////////////////////////////////
///////////      Paramètres communication côté client      /////////////
////////////////////////////////////////////////////////////////////////




















#define A 10 //test
