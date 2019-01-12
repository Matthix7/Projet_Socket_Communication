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
	
    SOCKET socketConnection = init_connection_client(address, PORTConnection);
    SOCKET socketChat = init_connection_client(address, PORTChat);
    int max = socketChat;
    max = socketConnection > max ? socketConnection : max;
    
    /*On envoit directement le nom sur le canal Connection*/
	write_to_server(socketConnection, argv[2]);
    
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
			/*Information venant du clavier client, à envoyer aux autres clients*/
			fgets(buffer, BUF_SIZE - 1, stdin);
			
            char *p = NULL;
            p = strstr(buffer, "\n");
            if(p != NULL){*p = 0;}
            else{buffer[BUF_SIZE - 1] = 0;}
            
            char* exitCondition = "Quit";  //Ecrire "Quit" pour une déconnection client propre
			if (strcmp(exitCondition, buffer)==0){break;}
			
			write_to_server(socketChat, buffer);
		}
	}

    end_connection_client(socketChat);
    end_connection_client(socketConnection);
    
    return EXIT_SUCCESS;
}
