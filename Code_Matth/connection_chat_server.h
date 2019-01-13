/// Code relatif à l'enregistrement et à la discussion entre clients.///

#ifndef CC2_H
#define CC2_H


//Inclusions nécessaires
#include "inclusions.h"




typedef struct{
 // Structure pour passer les arguments au thread
   Test addtest;
}Arg_chat_server;


int create_thread_server_connection_chat();
void* connection_chat_server();

#endif
