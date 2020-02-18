#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Entity{
	
	char Name[64];
	int AtkPhy;
	int AtkMag;
	int LifePhy;
	int LifeMag;
	
};
typedef struct Entity entity;

struct Element{
	
	char Name[64];
	// Pour l'ID : 0=>eau / 1=>feu / 2=>air etc... (à completer)
	int ID;
	int ModifAtkPhy;
	int ModifAtkMag;
	int ModifLifePhy;
	int ModifLifeMag;
	char Description[255];
	
};
typedef struct Element element;

struct Card{
	
	// Une carte est définie par une entité qui répond à un élément
	entity Entity;
	// Il faudra ensuite changer les stats de l'entité en fonction des modificateurs de l'élément.
	element Element;
	
};
typedef struct Card card;

int main(){
	
	entity loup = {"Loup de ", 4,1,3,2};
	
	element terre = {"Terre",3,0,-1,2,0,"Subit 1 dégat physique de moins par attaque physique subie"};
	
	printf("%s",loup.Name);
	printf("%s \n",terre.Name);
	
	card firstCard = {loup,terre};
	
	printf("\n%s",firstCard.Entity.Name);
	printf("%s\n",firstCard.Element.Name);
	
	strcat(firstCard.Entity.Name, firstCard.Element.Name);
	firstCard.Entity.AtkPhy += firstCard.Element.ModifAtkPhy;
	firstCard.Entity.AtkMag += firstCard.Element.ModifAtkMag;
	firstCard.Entity.LifePhy += firstCard.Element.ModifLifePhy;
	firstCard.Entity.LifeMag += firstCard.Element.ModifLifeMag;
	
	printf("\n%s  ",firstCard.Entity.Name);
	printf("%d/",firstCard.Entity.AtkPhy);
	printf("%d/",firstCard.Entity.AtkMag);
	printf("%d/",firstCard.Entity.LifePhy);
	printf("%d",firstCard.Entity.LifeMag);
	
	
	
	return 0;
}