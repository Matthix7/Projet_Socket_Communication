#      Ecrire dans terminal      #
#             make               #


default: MainServer MainClient

MainServer: MainServer0.c
	gcc -pthread -o MainServer MainServer0.c


MainClient: MainClient0.c
	gcc -pthread -o MainClient MainClient0.c
	


execServer: MainServer
	./MainServer
	
execClient: MainClient
	./MainClient

