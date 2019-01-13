/// Code relatif à l'enregistrement et à la discussion entre clients.///

#ifndef CC_H
#define CC_H


//Inclusions nécessaires
#include "inclusions.h"



/*
typedef struct{
 // Structure pour passer les arguments au thread
   Test addtest;
}Arg_chat_client;
*/

int create_thread_client_connection_chat(Client* pclient);
void* connection_chat_client(void* argument);

#endif
