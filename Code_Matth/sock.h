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
#define MAX_CLIENTS 	100
#define BUF_SIZE	    1024

typedef struct{
 /* Données inhérentes au client
  /!\ probablement incompatible avec les structures du groupe. */
   SOCKET sConnection;
   SOCKET sChat;
   SOCKET sWind;
   SOCKET sList;
   SOCKET sUpdate;
   int x;
   int y;
   char name[BUF_SIZE];
}Client;



int init_connection_server(int port);
void end_connection_server(SOCKET sock);
int read_from_client(Client* clients, int current, int id_client, SOCKET sock, char *buffer);
void removeClient(Client *clients, int to_remove, int *current);
void write_to_client(SOCKET sock, const char *buffer);
void sendMessage(Client *clients, Client sender, int current, const char *buffer, char from_server);
void clearClients(Client *clients, int current);


////////////////////////////////////////////////////////////////////////
///////////      Paramètres communication côté client      /////////////
////////////////////////////////////////////////////////////////////////


int init_connection_client(const char *address, int port);
void end_connection_client(int sock);
int read_from_server(SOCKET sock, char *buffer);
void write_to_server(SOCKET sock, const char *buffer);

















#define A 10 //test

#endif
