/// Code Socket, regroupe toutes les structures et fonctions        ///
/// nécessaires pour la communication par sockets.                  ///

#ifndef SOCK_H
#define SOCK_H

#include "inclusions.h"
////////////////////////////////////////////////////////////////////////
///////////      Paramètres communication côté serveur     /////////////
////////////////////////////////////////////////////////////////////////


typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#define PORTConnection  6530
#define PORTWind 		6531
#define PORTChat	 	6532
#define PORTList        6533
#define PORTUpdate      6534



int init_connection_server(int port);
void end_connection_server(SOCKET sock);
int read_from_client(SOCKET sock, char *buffer);
void removeClient(Client **clients, int to_remove, int *current);
void write_to_client(SOCKET sock, const char *buffer);
void sendMessageChat(Client **clients, Client *sender, int current, const char *buffer, char from_server);
void sendMessageWind(Client **clients, int current, const char *buffer);
void sendMessageConnection(Client **clients, int current, const char *buffer);
void clearClients(Client **clients, int current);


////////////////////////////////////////////////////////////////////////
///////////      Paramètres communication côté client      /////////////
////////////////////////////////////////////////////////////////////////


int init_connection_client(const char *address, int port);
void end_connection_client(int sock);
int read_from_server(SOCKET sock, char *buffer);
void write_to_server(SOCKET sock, const char *buffer);

















#endif
