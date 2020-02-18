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
	// Pour l'ID : 0=>eau / 1=>feu / 2=>air etc... (� completer)
	int ID;
	int ModifAtkPhy;
	int ModifAtkMag;
	int ModifLifePhy;
	int ModifLifeMag;
	char Description[255];

};
typedef struct Element element;

struct Card{

	// Une carte est d�finie par une entit� qui r�pond � un �l�ment
	entity Entity;
	// Il faudra ensuite changer les stats de l'entit� en fonction des modificateurs de l'�l�ment.
	element Element;

};
typedef struct Card card;

int main(){

	entity Loup = {"Loup d", 4,4,3,3};                                    //balance
	entity CrabeRoyal = {"Crabe Royal d", 7, 4, 3, 2};                    //HP
	entity DragonDeKomodo = {"Drakodo d", 4, 4, 6, 0};                    //attack + HP (phy + spe)
	entity AraigneeCracheuse = {"Araignee Cracheuse d", 2, 4, 2, 6};      //attack spe
	entity CrocodileAffame = {"Crocodile d", 5, 2, 5, 2};                 //attack + HP
	entity ChefAlpaga = {"Chef Alpaga d", 5, 5, 2, 4};                    //HP (phy + spe) + attack spe
	entity Grenouille = {"Crapaud d", 4, 7, 0, 3};                        //HP mag + attack spe
    entity TortueSonore = {"Tortue Sonore d", 6, 2, 2, 6};                //HP + attack spe
    entity BoucTemeraire = {"Bouc Temeraire d", 3, 3, 5, 5};              //attack (phy + spe)
    entity Aigle = {"Aigle d", 3, 4, 6, 2};                               //attack
    entity Elephant = {"Elefant d", 10, 0, 4, 0};                         //HP
    entity Jaguare = {"Jaguare d", 2, 6, 6, 2};                           //HP spe + attack
    entity SerpentCorosif = {"Serpent Corosif d", 0, 10, 0, 4};           //HP spe + attack spe
    entity PlanteMarecageuse = {"Plante Marecargeuese d", 4, 4, 0, 6};              //attack spe
    entity Scorpion = {"Scorpion d", 6, 2, 2, 4};
    entity Phasme = {"Phasme d", 6, 6, 2, 2};
    entity Buffle = {"Buffle d", 5, 2, 4, 2};
    entity ManteReligieuse = {"Mante Religieuse d", 3, 4, 6, 2};


	element terre = {"Terre",3,0,-1,2,0,"Subit 1 d�gat physique de moins par attaque physique subie"};

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
