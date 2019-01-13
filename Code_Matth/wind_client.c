/// Code relatif au traitement des modification du vent.///

//Inclusions nécessaires
#include "inclusions.h"


///////      Gestion de la modification du vent côté client       //////
////////////////////////////////////////////////////////////////////////


void* wind_client(void* arg){
	Arg_wind_client* argument = (Arg_wind_client*) arg;
	Client* Perso = argument->perso;
	char* address = argument->adresse;
	t_vent* Wind = argument->Wind;
	SOCKET socketWind = init_connection_client(address, PORTWind);
	char buffer[BUF_SIZE];
	int max = socketWind;
	
	fd_set rdfs;
	
	
	while(1){
      
		FD_ZERO(&rdfs);
		/* add the socket */
		FD_SET(socketWind, &rdfs);
		
		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1){
			perror("select()");
			exit(errno);
		}
		
		//On reçoit une modification du vent
		if(FD_ISSET(socketWind, &rdfs)){
			int n = read_from_server(socketWind, buffer);
			//  server down 
			if(n == 0){printf("Server disconnected !\n");break;}
			else{
				int F = atoi(&buffer[0]);
				char dir = (char) buffer[1];
				t_vent* vent = malloc(sizeof(t_vent));
				Wind->force_vent = F;
				Wind->direction_vent = dir;
				printf("Modification du vent : %d%c\n", Wind->force_vent, Wind->direction_vent);
			}
		}
	}
    end_connection_client(socketWind);
}



////////    Exécution en parallèle de la fonction précédente    ////////
////////////////////////////////////////////////////////////////////////


int create_thread_client_wind(char* address, Client* perso, t_vent* Wind){
	pthread_t thread_client_wind;
	Arg_wind_client* arg = malloc(sizeof(Arg_wind_client));
	arg->adresse = address;
	arg->perso = perso;
	arg->Wind = Wind;
	int res = pthread_create( & thread_client_wind, NULL, wind_client, (void*) arg);
	if (res) {printf("Thread de vent non créé");}
	free(arg);
	return res;
}

