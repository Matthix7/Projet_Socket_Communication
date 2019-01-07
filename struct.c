#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <signal.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 10
#define MAXTEXT 100


typedef struct{
	int power;
	char orientation;

}WIND; 

typedef struct{
	int x;  /* size of map, standard x y positioning 0,0 in top left corner */ 
	int y;
	int *map;    
	WIND wind;
	char * fileBoat;
}SEA;

typedef  struct{
	int isConnected;
	int ID;
	int sChat;
	int sWind;
	int sList;
	int sUpdate;
}BOAT;

typedef struct{
	int nbrclient;
	BOAT client[5];
}CLIENT;


void clean_stdin(void) 
{ 
    int c; 
  
    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF); 
}


void changeWind(SEA *sea){
	char wind;
	printf("New orientation of the wind (N,O,S,E) ? \n");
	
	scanf("%c",&wind);
	clean_stdin();
	switch(wind)
	{
		case 'N': sea->wind.orientation = 'N'; break;
		case 'n': sea->wind.orientation = 'N'; break;
		case 'O': sea->wind.orientation = 'O'; break;
		case 'o': sea->wind.orientation = 'O'; break;
		case 'E': sea->wind.orientation = 'E'; break;
		case 'e': sea->wind.orientation = 'E'; break;
		case 'S': sea->wind.orientation = 'S'; break;
		case 's': sea->wind.orientation = 'S'; break;
		default: printf("Wrong format, please enter N, O, S or E \n");
	}
	
	int power;
	printf("New power of wind ? min = 0, max = 20");
	scanf("%d",&power);
	clean_stdin();
	sea->wind.power = power;
	
}


void changeSea(SEA *sea, int x, int y, int val){
	int point; 
	point = y*sea->y + x;
	sea->map[point] = val;
}


char getCase(SEA *sea, int x, int y) {
	int point;
	point = y*sea->y + x;
	return sea->map[point];
}

void displaySea(SEA *sea){
	for (int y = 0; y< sea->y; y++){
		for (int x=0; x<sea->x; x++){
			switch (getCase(sea,x,y))
			{
				case 0:
					printf(" . ");
					break;
				case 1:
					printf(" B ");
					break;
				case 2:
					printf(" R ");
					break;
			}
		}
		printf("\n");
	}
	printf("Direction of the wind: %c, Intensity: %d", sea->wind.orientation, sea->wind.power);
}



void buildSea(SEA *sea){
	FILE * fileMap = fopen("mapConfig.txt","r");
	char line [128]; /* or other suitable maximum line size */
	char *a;
	while ( fgets ( line, sizeof(line), fileMap ) != NULL ) /* read a line */
	{
		if ((line[0] != '#')&&(line[0] != '-')){
			a = strtok(line,", \n");
			sea->x = atoi(a);
			a = strtok(NULL,", \n");
			sea->y = atoi(a);
			printf("Size of map: (%d, %d) \n",sea->x,sea->y);
			break;
		}
		
	}
	sea->map = malloc( sea->x*sea->y*sizeof(int));	
	for (int i =0; i< (sea->x*sea->y);i++){
		sea->map[i] = 0;
	}
	
	while ( fgets ( line, sizeof(line), fileMap ) != NULL ) /* read a line */
	{
		if ((line[0] != '#')&&(line[0] != '-')){
			a = strtok(line,", \n");
			int x = atoi(a);
			a = strtok(NULL,", \n");
			int y = atoi(a);
			changeSea(sea,x,y,2);
		}
		
	}
	
	fclose (fileMap);
}



	
	
void menu(SEA *sea){
	char choice;
	do
	{
		printf("\n\n Display map: M\n");
		printf("Change wind: W\n");
		printf("Quit : Q\n");
		printf("                             your choice?");
		rewind(stdin);
		scanf("%c",&choice);
		clean_stdin();
		switch(choice)
		{
			case 'M': displaySea(sea); break;
			case 'm': displaySea(sea); break;
			case 'W': changeWind(sea); break;
			case 'w': changeWind(sea); break;
		}
	}while (choice != 'q' && choice !='Q');
	
	
}


void main(int argc, char *argv[])
{
	
	SEA sea = {NULL};

	buildSea(&sea);
	displaySea(&sea);
	menu(&sea);
	
}
