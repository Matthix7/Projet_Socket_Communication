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

#include "sea.h"
#include "boat.h"

/////////// necessary 
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
///////////

static void proc(void)
{
   /* creation of service sockets */
   SOCKET socketConnection = init_connection(PORTConnection);
   SOCKET socketChat = init_connection(PORTChat);
   SOCKET socketWind = init_connection(PORTWind);
   SOCKET socketList = init_connection(PORTList);
   SOCKET socketUpdate = init_connection(PORTUpdate);
   
   char buffer[BUF_SIZE];
   /* index for the array */
   int current = 0;
   int max = socketConnection;
   /* an array for all clients */
   Client clients[MAX_CLIENTS];

   fd_set rdfs;



	/* update service for a thread */
	
	
	pthread_t threadC;
	

	void *arg[2] = {clients,&current};
    if(pthread_create(&threadC, NULL, threadUp,arg) == -1) {

		return EXIT_FAILURE;
    }



   while(1)
   {
      int i = 0;
      FD_ZERO(&rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &rdfs);

      /* add connection socket */
      FD_SET(socketConnection, &rdfs);
      FD_SET(socketChat, &rdfs);
      FD_SET(socketWind, &rdfs);
      FD_SET(socketList, &rdfs);
      FD_SET(socketUpdate, &rdfs);

      /* add socket for each client */
      for(i = 0; i < current; i++)
      {
			FD_SET(clients[i].sConnection, &rdfs);
			FD_SET(clients[i].sChat, &rdfs);
			FD_SET(clients[i].sWind, &rdfs);
			FD_SET(clients[i].sList, &rdfs);
			FD_SET(clients[i].sUpdate, &rdfs);

      }

      if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      /* something from standard input : i.e keyboard */
      if(FD_ISSET(STDIN_FILENO, &rdfs))
      {
         /* stop process when type on keyboard */
         break;
      }
      else if(FD_ISSET(socketConnection, &rdfs))
      {
         /* new client */
         
         SOCKADDR_IN csin = { 0 };
         size_t sinsize = sizeof csin;
         int csock = accept(socketConnection, (SOCKADDR *)&csin, &sinsize);
         if(csock == SOCKET_ERROR)
         {
            perror("accept()");
            continue;
         }

         /* after connecting the client sends its name */
         if(readClient(csock, buffer) == -1)
         {
            /* disconnected */
            continue;
         }
         
         
		int chatSock = accept(socketChat, (SOCKADDR *)&csin, &sinsize);
		int windSock = accept(socketWind, (SOCKADDR *)&csin, &sinsize);
		int listSock = accept(socketList, (SOCKADDR *)&csin, &sinsize);
		int updateSock = accept(socketUpdate, (SOCKADDR *)&csin, &sinsize);

		/* what is the new maximum fd ? */
		max = csock > max ? csock : max;
        max = chatSock > max ? chatSock : max;
		max = windSock > max ? windSock : max;
		max = listSock > max ? listSock : max;
		max = updateSock > max ? updateSock : max;
		
		FD_SET(csock, &rdfs);
		FD_SET(chatSock, &rdfs);
		FD_SET(windSock, &rdfs);
		FD_SET(listSock, &rdfs);
		FD_SET(updateSock, &rdfs);
		
		
		Client c = {NULL};
		c.sConnection = csock;
		c.sChat = chatSock;
		c.sWind = windSock;
		c.sList = listSock;
		c.sUpdate = updateSock;
		strncpy(c.name, buffer, BUF_SIZE - 1);
		clients[current] = c;
		current++;
		}
      
      
      else
      {
         int i = 0;
         for(i = 0; i < current; i++)
         {
            // a client is talking 
            if(FD_ISSET(clients[i].sChat, &rdfs))
            {
               Client client = clients[i];
               int c = readClient(clients[i].sChat, buffer);
               //client disconnected 
               if(c == 0)
               {
                  closesocket(clients[i].sChat);
                  removeClient(clients, i, &current);
                  strncpy(buffer, client.name, BUF_SIZE - 1);
                  strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                  sendMessage(clients, client, current, buffer, 1); //send to all clients for now #broadcast maggle
               }
               else
               {
                  sendMessage(clients, client, current, buffer, 0);
               }
               break;
            }
         }
      }
      
      
   }

   clearClients(clients, current);
   end_connection(socketChat);
   end_connection(socketConnection);
   end_connection(socketWind);
   end_connection(socketUpdate);
   end_connection(socketList);
}


/////////////////////
static void clearClients(Client *clients, int current)
{
   int i = 0;
   for(i = 0; i < current; i++)
   {
	  closesocket(clients[i].sConnection);
      closesocket(clients[i].sChat);
      closesocket(clients[i].sWind);
      closesocket(clients[i].sList);
      closesocket(clients[i].sUpdate);
   }
}

static void removeClient(Client *clients, int to_remove, int *current)
{
   /* we remove the client in the array */
   memmove(clients + to_remove, clients + to_remove + 1, (*current - to_remove - 1) * sizeof(Client));
   /* number client - 1 */
   (*current)--;
}

static void sendMessage(Client *clients, Client sender, int current, const char *buffer, char from_server)
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
         writeClient(clients[i].sChat, message);
      }
   }
}


/////////////////////////////


void  *threadUp( void * arg[] ){
	update(arg[0],arg[1]);
	pthread_exit(NULL) ;
	
}

void update(Client *clients, int *current){
	char buffer[5]= "is ok";
	while(1)
	{
		sleep(5);
		int i = 0;
		for(i =0; i<*current; i++){
			
			if(send(clients[i].sUpdate, buffer, strlen(buffer), 0) < 0)
			{
				perror("send()");
				exit(errno);
			}
			int x = -1;
			int y = -1;
			recv(clients[i].sUpdate, &x, sizeof(int),0);
			recv(clients[i].sUpdate, &y, sizeof(int),0);
			//printf(" x et y : %d , %d \n",x,y);
		}
	}
	
}


/////////////////////////////////////////////////////////////////////////
static int init_connection(int port)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   sin.sin_addr.s_addr = htonl(INADDR_ANY);
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }

   if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
   {
      perror("listen()");
      exit(errno);
   }

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

static int readClient(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = 0;

   return n;
}

static void writeClient(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}

//////////////////////////
int main(int argc, char **argv)
{
   init();

   proc();

   end();

   return EXIT_SUCCESS;
}













