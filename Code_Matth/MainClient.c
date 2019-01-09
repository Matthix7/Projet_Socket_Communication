/// Code Main, regroupe toutes les fonctionnalités nécessaires       ///
/// au projet actuellement mises en place pour le fonctionnement     ///
/// côté client.                                                     ///


//Inclusions nécessaires
#include "inclusions.h"











////////////////////////////////////////////////////////////////////////
/////////////////////     MAIN     /////////////////////////////////////
////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	if(argc < 2)
    {
      printf("Usage : %s [address] [nickname]\n", argv[0]);
      return EXIT_FAILURE;
    }
    
    char* address = argv[1];
    SOCKET socketChat = init_connection_client(address, PORTChat);
    printf("Connexion à socketChat sur le port 6532\n");
    end_connection_client(socketChat);
    
    
    
    

    return EXIT_SUCCESS;
}
