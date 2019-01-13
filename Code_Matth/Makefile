#      Ecrire dans terminal      #
#             make               #


default: MainServer MainClient

MainServer: MainServer.c
	gcc -pthread -o MainServer MainServer.c


MainClient: MainClient.c
	gcc -pthread -o MainClient MainClient.c
	


execServer: MainServer
	./MainServer
	
execClient: MainClient
	./MainClient

