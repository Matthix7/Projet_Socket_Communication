/// Code Main, regroupe toutes les fonctionnalités nécessaires       ///
/// au projet actuellement mises en place pour le fonctionnement     ///
/// côté serveur.                                                     ///


//Inclusions nécessaires
#include "inclusions.h"


///////      Gestion de la modification du vent côté client       //////
////////////////////////////////////////////////////////////////////////


void* wind_client(){
		
	
}



////////    Exécution en parallèle de la fonction précédente    ////////
////////////////////////////////////////////////////////////////////////


int create_thread_client_wind(){
	pthread_t thread_client_wind;
	int res = pthread_create( & thread_client_wind, NULL, wind_client, NULL);
	if (res) {printf("Thread de vent non créé");}
	return res;
}


*/
