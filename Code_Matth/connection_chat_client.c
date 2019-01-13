/// Code relatif à l'enregistrement et à la discussion entre clients.///


//Inclusions nécessaires
#include "inclusions.h"

///////   Gestion de la conection et des discussions côté client  //////
////////////////////////////////////////////////////////////////////////


void* connection_chat_client(void* add)
{
	Client* test = add;
	test->toto = test->toto + 1;
}


////////    Exécution en parallèle de la fonction précédente    ////////
////////////////////////////////////////////////////////////////////////

int create_thread_client_connection_chat(Client* pclient){
	pthread_t thread_client_connection_chat;
	/*Arg* arg = malloc(sizeof *arg);
	arg->addtest = &Titi;*/
	void* add = (void*) pclient;
	int res = pthread_create( & thread_client_connection_chat, NULL, connection_chat_client, (void*) pclient);
	//if (res) {free(arg);}
	return res;
}







	
