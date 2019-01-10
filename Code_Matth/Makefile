#      Ecrire dans terminal      #
#             make               #


default: MainServer MainClient

MainServer: MainServer.c
	gcc -g MainServer.c -o MainServer

MainClient: MainClient.c
	gcc -Wall -g MainClient.c -o MainClient


execServer: MainServer
	./MainServer
	
execClient: MainClient
	./MainClient

