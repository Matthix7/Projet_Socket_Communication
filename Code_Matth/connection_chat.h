/// Code relatif à l'enregistrement et à la discussion entre clients.///


//Inclusions nécessaires
#include "inclusions.h"


typedef struct{
 // Structure pour passer les arguments au thread
   int argc;
   char **argv;
}Arg;

int create_thread_client_connection_chat(Client client, int argc, char **argv);
void* connection_chat_client(void* argument);

int create_thread_server_connection_chat();
void* connection_chat_server();

