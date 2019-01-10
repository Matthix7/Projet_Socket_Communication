# Projet_OS
Mise en place de communications entre des bateaux (clients) et un serveur par utilisation des moyens vus en cours d'OS.      \n

# Fonctionnalités actuelles: 
Connection au serveur\n
Communication et enregistrement du nom du bateau dans une liste de clients connectés au serveur\n
Création d'un channel de tchat commun à tous les clients\n

# Fonctionnement
Utiliser la commande $make pour compiler les fichiers MainServer.c et MainClient.c
Dans un terminal, démarrer le serveur en utilisant la commande $./MainServer
Dans d'autres terminaux, connecter des clients en utilisant la commande $./MainClient [addresseServeur] [nickname]
Les clients sont alors connectés au channel de tchat et peuvent communiquer entre eux.
Pour quitter: taper "Quit" dans le terminal d'un client, il sera déconnecté.
Quand tous les clients sont déconnectés, n'importe quelle entrée clavier entraîne la déconnection du serveur.
