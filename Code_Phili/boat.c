#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>


#include "boat.h"

///////////////////////
static void init(void)
{
#ifdef WIN32
   WSADATA wsa;
   int err = WSAStartup(MAKEWORD(2, 2), &wsa);
   if(err < 0)
   {
      puts("WSAStartup failed !");
      exit(EXIT_FAILURE);
   }
#endif
}

static void end(void)
{
#ifdef WIN32
   WSACleanup();
#endif
}

///////////////////////
static void proc(const char *address, const char *name)
{
	SOCKET socketConnection = init_connection(address, PORTConnection);


	char buffer[BUF_SIZE];

	fd_set rdfs;

	/* send our name */
	write_server(socketConnection, name);

	SOCKET socketChat = init_connection(address, PORTChat);
	SOCKET socketWind = init_connection(address, PORTWind);
	SOCKET socketList = init_connection(address, PORTList);
	SOCKET socketUpdate = init_connection(address, PORTUpdate);


	int max = socketConnection;
	max = socketChat > max ? socketChat : max;
	max = socketWind > max ? socketWind : max;
	max = socketList > max ? socketList : max;
	max = socketUpdate > max ? socketUpdate : max;
	
	
	/* chat service for a thread */
	pthread_t threadC, threadM;
	

	void *argChat[2] = {socketChat,max};
    if(pthread_create(&threadC, NULL, threadChat,argChat) == -1) {

		return EXIT_FAILURE;
    }
    
    void *argUpdate[2]= {socketUpdate,max};
    if(pthread_create(&threadM, NULL, threadUp,argUpdate) == -1) {

		return EXIT_FAILURE;
    }
    
	/* as long as it remains connected */
   while(1)
   {
      FD_ZERO(&rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &rdfs);

      /* add the socket */
	  FD_SET(socketConnection, &rdfs);



      if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }
      
      
      if(FD_ISSET(socketConnection, &rdfs))
      {
         int n = read_server(socketChat, buffer);
        //  server down 
         if(n == 0)
         {
            printf("Server disconnected !\n");
            break;
         }
         //puts(buffer);
      }
 
   }

   end_connection(socketChat);
   end_connection(socketConnection);
}



////////////////////////////
static int init_connection(const char *address, int port)
{
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

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
      perror("connect()");
      exit(errno);
   }

   return sock;
}

//////////////////////////////
static void end_connection(int sock)
{
   closesocket(sock);
}



////////////////////////////////////////////////////////////////////////
static int read_server(SOCKET sock, char *buffer)
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


static void write_server(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}

////////////////////////////////////////////////////////////////////////

void  *threadChat( void * arg[] )
{
	char buffer[BUF_SIZE];
	int max = arg[1];
	
	SOCKET sock = arg[0];
	fd_set rdchat;

	while (1){
	FD_ZERO(&rdchat);

	/* add STDIN_FILENO */
	FD_SET(STDIN_FILENO, &rdchat);

	/* add the socket */
	FD_SET(sock, &rdchat);

	if(select(max + 1, &rdchat, NULL, NULL, NULL) == -1)
	{
		perror("select()");
		exit(errno);
	}
	if(FD_ISSET(STDIN_FILENO, &rdchat))
      {
         fgets(buffer, BUF_SIZE - 1, stdin);
         {
            char *p = NULL;
            p = strstr(buffer, "\n");
            if(p != NULL)
            {
               *p = 0;
            }
            else
            {
               /* fclean */
               buffer[BUF_SIZE - 1] = 0;
            }
         }
         write_server(sock, buffer);
      }
	else if(FD_ISSET(sock, &rdchat))
      {
         int n = read_server(sock, buffer);
        //  server down 
         if(n == 0)
         {
            printf("chat disconnected !\n");
            break;
         }
         puts(buffer);
      }
	}
	pthread_exit(NULL) ;
}



void  *threadUp( void * arg[] )
{
	char buffer[BUF_SIZE];
	int max = arg[1];
	
	SOCKET sock = arg[0];
	fd_set rdmaj;

	while (1){
	FD_ZERO(&rdmaj);

	/* add STDIN_FILENO */
	FD_SET(STDIN_FILENO, &rdmaj);

	/* add the socket */
	FD_SET(sock, &rdmaj);

	if(select(max + 1, &rdmaj, NULL, NULL, NULL) == -1)
	{
		perror("select()");
		exit(errno);
	}
	if(FD_ISSET(sock, &rdmaj))
	{
		int n = read_server(sock, buffer);
		//  server down 
		if(n == 0)
		{
			printf("maj disconnected !\n");
			break;
		}
		// new local position
		else 
		{
			int x = 3;
			int y = 5;
			send(sock, &x, sizeof(int),0);
			send(sock, &y, sizeof(int),0);
		}
		//puts(buffer);
	}
	
	}
	pthread_exit(NULL) ;
}




////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
   if(argc < 2)
   {
      printf("Usage : %s [address] [nickname]\n", argv[0]);
      return EXIT_FAILURE;
   }

   init();

   proc(argv[1], argv[2]);

   end();

   return EXIT_SUCCESS;
}
