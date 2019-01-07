#ifndef CLIENT_H
#define CLIENT_H

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
#define BUF_SIZE	1024

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct
{
   SOCKET sConnection;
   SOCKET sChat;
   SOCKET sWind;
   SOCKET sList;
   SOCKET sUpdate;
   int x;
   int y;
   char name[BUF_SIZE];
}BATEAU;


#else

#error not defined for this platform

#endif

#define CRLF	 "\r\n"
#define PORTConnection  6530
#define PORTWind 		6531
#define PORTChat	 	6532
#define PORTList        6533
#define PORTUpdate      6534

#define BUF_SIZE 1024

static void init(void);
static void end(void);
static void app(const char *address, const char *name);
static int init_connection(const char *address, int port);
static void end_connection(int sock);
static int read_server(SOCKET sock, char *buffer);
static void write_server(SOCKET sock, const char *buffer);
void  *threadChat( void * arg[] );
void  *threadUp( void * arg[] );

#endif /* guard */

