# Projet_OS
Mise en place de communications entre des bateaux (clients) et un serveur par utilisation des moyens vus en cours d'OS.  

## Fonctionnalités actuelles: 
Connexion au serveur   
Communication et enregistrement du nom du bateau dans une liste de clients connectés au serveur   
Utilisation d'un channel de tchat commun à tous les clients permettant l'envoi de messages communs   
Modification des paramètres de vent affectant les bateaux
Déconnection

## Fonctionnement
Utiliser la commande `$make` pour compiler les fichiers MainServer.c et MainClient.c   
Dans un terminal, démarrer le serveur en utilisant la commande `$./MainServer`   
Dans d'autres terminaux, connecter des clients en utilisant la commande `$./MainClient [addresseServeur] [nickname]`    
Les clients sont alors connectés au channel de tchat et peuvent communiquer entre eux par simple entrée clavier dans leurs terminaux.    
La modification de la force et de la direction du vent se fait depuis le terminal du serveur par la commande `$Wind [Force][Direction]`.
 Exemple: `$Wind 3N`. Cette commande modifie des valeurs utilisables par chaque client, pour un calcul de déplacement par exemple.
  Ces valeurs ne sont cependant pas traitées actuellement.    
Pour quitter: taper `"$Quit"` dans le terminal d'un client, il sera déconnecté.   
Quand tous les clients sont déconnectés, taper `"$Quit"` dans le terminal du serveur entraîne sa déconnection.   
