/// Code relatif au traitement des modification du vent.///


//Inclusions nécessaires
#include "inclusions.h"


typedef struct{
 // Structure pour passer les arguments au thread
   Client* perso;
   char* adresse;
   t_vent* Wind;
}Arg_wind_client;


int create_thread_client_wind(char* address, Client* perso, t_vent* Wind);
void* wind_client(void *arg);




