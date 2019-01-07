#ifndef CLIENT_H
#define CLIENT_H

#include "sea.h"

typedef struct
{
   SOCKET sConnection;
   SOCKET sChat;
   SOCKET sWind;
   SOCKET sList;
   SOCKET sUpdate;
   int x;
   int y;
   char name[BUF_SIZE];
}Client;


typedef struct{
	int power;
	char orientation;

}WIND; 

typedef struct{
	int x; 
	int y;
	int *map;    
	WIND wind;
	char * fileBoat;
}SEA;

typedef  struct{
	int isConnected;
	int name;
	int sChat;
	int sWInd;
	int sList;
	int sUpdate;
}BOAT;
/*
typedef struct{
	int nbrclient;
	BATEAU bateau[10];
}Client;


*/

#endif /* guard */
