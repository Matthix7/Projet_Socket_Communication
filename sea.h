#ifndef SERVER_H
#define SERVER_H

#ifdef WIN32

#include <winsock2.h>

#elif defined (linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#define CRLF		"\r\n"
#define PORTConnection  6530
#define PORTWind		6531
#define PORTChat	 	6532
#define PORTList        6533
#define PORTUpdate      6534
#define MAX_CLIENTS 	100

#define BUF_SIZE	1024

#include "client.h"

static void init(void);
static void end(void);
static void app(void);
static int init_connection(int port);
static void end_connection(int sock);
static int readClient(SOCKET sock, char *buffer);
static void writeClient(SOCKET sock, const char *buffer);
static void sendMessage(Client *clients, Client client, int current, const char *buffer, char from_server);
static void removeClient(Client *clients, int to_remove, int *current);
static void clearClients(Client *clients, int current);

void  *threadUp( void * arg[] );
void update(Client *clients, int *current);


#endif /* guard */
