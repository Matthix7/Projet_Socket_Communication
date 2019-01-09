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
    
    char buffer[BUF_SIZE];
	char* address = argv[1];
	
	fd_set rdfs;
	
    SOCKET socketChat = init_connection_client(address, PORTChat);
    printf("Connexion à socketChat sur le port 6532\n");
    int max = socketChat;
     
    while(1){
      
		FD_ZERO(&rdfs);

		/* add STDIN_FILENO */
		FD_SET(STDIN_FILENO, &rdfs);

		/* add the socket */
		FD_SET(socketChat, &rdfs);

		if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1){
			perror("select()");
			exit(errno);
		}
      
		if(FD_ISSET(socketChat, &rdfs)){
			/*Information venant du serveur*/
			int n = read_from_server(socketChat, buffer);
			//  server down 
			if(n == 0){
				printf("Server disconnected !\n");
				break;
			}
			else{
				puts(buffer);
			}
		}
		
		if(FD_ISSET(STDIN_FILENO, &rdfs)){
			/*Information venant du clavier client*/
			fgets(buffer, BUF_SIZE - 1, stdin);
            char *p = NULL;
            p = strstr(buffer, "\n");
            if(p != NULL){
               *p = 0;
            }
            else{
               /* fclean */
               buffer[BUF_SIZE - 1] = 0;
            }
            char* exitCondition = "Quit";
			if (strcmp(exitCondition, buffer)==0){
				break;
			}
			write_to_server(socketChat, buffer);
		}
	}

    end_connection_client(socketChat);
    
    return EXIT_SUCCESS;
}
