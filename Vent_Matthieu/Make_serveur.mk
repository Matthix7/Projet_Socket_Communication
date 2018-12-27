#      Ecrire dans terminal      #
#     make -f Make_serveur.mk    #

default: Serveur_vent execServeur 

Serveur_vent: Serveur_vent.c
	gcc -Wall -g Serveur_vent.c -o Serveur_vent

Client_vent: Client_vent.c
	gcc -Wall -g Client_vent.c -o Client_vent


execServeur: Serveur_vent
	./Serveur_vent
	
execClient: Client_vent
	./Client_vent
