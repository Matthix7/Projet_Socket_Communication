/// Code Include, regroupe toutes les inclusions nécessaires       ///
/// au projet pour alléger l'écriture des autres fichiers.         ///

#ifndef INC_H
#define INC_H


//Inclusion des librairies standards
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <math.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>


//Inclusion des fonctions des autres fichiers
//#include "sea.h"
//#include "boat.h"
//#include "wind.h"
#include "struct.h"
#include "sock.h"
#include "connection_chat.h"


#include "sock.c"
#include "connection_chat_client.c"
#include "connection_chat_server.c"

#endif
