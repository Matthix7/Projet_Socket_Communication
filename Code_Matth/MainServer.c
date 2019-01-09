/// Code Main, regroupe toutes les fonctionnalités nécessaires       ///
/// au projet actuellement mises en place pour le fonctionnement     ///
/// côté serveur.                                                     ///


//Inclusions nécessaires
#include "inclusions.h"








////////////////////////////////////////////////////////////////////////
/////////////////////     MAIN     /////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv){
	int a = A;  //Attention gestion étrange des define: nécessite changement élémentaire ici pour être pris en compte
	printf("Succès global serveur, %d\n\n", a);
	
	
	SOCKET socketConnection = init_connection_server(PORTChat);
	
	printf("Patientez pendant que le client se connecte sur le port %d...\n", PORTChat);
	SOCKADDR_IN csin = { 0 };
    socklen_t crecsize = sizeof(csin);
    SOCKET csock = accept(socketConnection, (SOCKADDR *)&csin, &crecsize);
	printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
	
	
	end_connection_server(socketConnection, csock);
	
	
	
	return EXIT_SUCCESS;
}
