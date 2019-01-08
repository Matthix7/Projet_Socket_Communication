#      Ecrire dans terminal      #
#      make -f MakeClient.mk     #

default: MainClient execClient 

MainServer: MainServer.c
	gcc -Wall -g MainServer.c -o MainServer

MainClient: MainClient.c
	gcc -Wall -g MainClient.c -o MainClient


execServer: MainServer
	./MainServer
	
execClient: MainClient
	./MainClient
