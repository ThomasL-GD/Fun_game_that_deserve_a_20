#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Entity{

	char Name[64];
	int Atk;
	int AtkSpe;
	int Life;
	int LifeSpe;

};
typedef struct Entity entity;

struct Element{

	char Name[64];
	// Pour l'ID : 0=>eau / 1=>feu / 2=>air / 3=>terre // 4=>air / 5=>glace / 6=>nature / 7=>foudre / 8=>lave / 9=>sable
	int ID;
	int ModifAtk;
	int ModifAtkSpe;
	int ModifLife;
	int ModifLifeSpe;
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

void DeckDefinition (card deck[20]){

	for (int i = 0; i < 20; i++){

		strcat(deck[i].Entity.Name, deck[i].Element.Name);
		deck[i].Entity.Atk += deck[i].Element.ModifAtk;
		deck[i].Entity.AtkSpe += deck[i].Element.ModifAtkSpe;
		deck[i].Entity.Life += deck[i].Element.ModifLife;
		deck[i].Entity.LifeSpe += deck[i].Element.ModifLifeSpe;

	}

};

void Fight (card deckP[20], card deckA[20]){

	// Sert a connaitre les cartes deja piochees pour ne pas les repiocher a nouveau... On remplacera les -1 par l'index des cartes deja piochees
	int cardsDrewP[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int cardsDrewA[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	int actionsP = 3;
	int actionsA = 3;

	element empty = {"Z",10,0,0,0,0,""};
	entity Empty = {"z",0,0,0,0};

	card fieldA[3] ={Empty,empty, Empty,empty, Empty,empty};
	card fieldP[3] ={Empty,empty, Empty,empty, Empty,empty};

	card handP[20] = {Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty};
	card handA[20] = {Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty};
};

int main(){

	srand(time(NULL));

	//////////////////////////////////////////BASE DE DONNEES DES CARTES//////////////////////////////////////////////////////////
	element eau = {"'Eau",0,-1,1,1,0,"Soigne 1PV par tour aux autres creatures sous votre controle"};
	element feu = {"e Feu",1,2,0,-1,0,"Inflige deux tours de brulure (-1PV par tour) pour toute attaque physique effectuÃ©e"};
	element air = {"'Air",2,-1,0,1,1,"Subit 1 dÃ©gat magique de moins par attaque magique subie"};
	element terre = {"e Terre",3,0,-1,2,0,"Subit 1 dÃ©gat physique de moins par attaque physique subie"};

	element fumee = {"e Fumee",4,0,1,1,-1,"Inflige 1 degat a tous les adversaires par tour"};
	element glace = {"e Glace",5,0,1,-1,1,"Reduit l'attaque de 1 point pendant 2 tours a celui qui subit une attaque de glace"};
	element nature = {"e Nature",6,-1,0,1,1,"Se soigne de 1PV par tour et reduit les degats subits de 1 a chaque attaque"};
	element foudre = {"e Foudre",7,0,2,0,-1,"Fait un degat magique de plus et un degat supplementaire pour chaque attaque foudre deja lancee ce tour"};
	element lave = {"e Lave",8,1,0,1,-1,"Inflige un degat supplementaire de contre-attaque"};
	element sable = {"e Sable",9,0,-1,1,1,"Divise par deux les degats de contre-attaque recus"};


	entity Loup = {"Loup d", 3, 3, 4, 4};                                    //balance
	entity CrabeRoyal = {"Crabe Royal d", 3, 2, 7, 4};                    //HP
	entity DragonDeKomodo = {"Drakodo d", 6, 0, 4, 4};                    //attack + HP (phy + spe)
	entity AraigneeCracheuse = {"Araignee Cracheuse d", 2, 6, 2, 4};      //attack spe
	entity CrocodileAffame = {"Crocodile d", 5, 2, 5, 2};                 //attack + HP             /
	entity ChefAlpaga = {"Chef Alpaga d", 2, 4, 5, 5};                    //HP (phy + spe) + attack spe
	entity Grenouille = {"Crapaud d", 0, 3, 4, 7};                        //HP mag + attack spe
    entity TortueSonore = {"Tortue Sonore d", 2, 6, 6, 2};                //HP + attack spe
    entity BoucTemeraire = {"Bouc Temeraire d", 5, 5, 3, 3};              //attack (phy + spe)
    entity Aigle = {"Aigle d", 6, 2, 3, 4};                               //attack
    entity Elephant = {"Elephant d", 4, 0, 10, 0};                        //HP
    entity Jaguar = {"Jaguar d", 6, 2, 2, 6};                             //HP spe + attack
    entity SerpentCorosif = {"Serpent Corosif d", 0, 4, 0, 10};           //HP spe + attack spe
    entity PlanteMarecageuse = {"Plante Marecargeuese d", 0, 6, 4, 4};    //attack spe
    entity Scorpion = {"Scorpion d", 2, 4, 6, 2};                         //attack + attack spe
    entity Phasme = {"Phasme d", 2, 2, 6, 6};                             // HP (phy + spe)
    entity Buffle = {"Buffle d", 4, 2, 5, 2};                             //HP + attack
    entity ManteReligieuse = {"Mante Religieuse d", 6, 2, 3, 4};          //attack



	/////////////////////////////////////////////////DEFINITION DES DECKS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Ce tableau contient 20 cartes, c'est donc un deck, /! Les cartes sont triÃ©es donc quand on piochera il faudra prendre une carte aleatoire parmi le deck
	card deck1[20] = {Loup,feu, Loup,terre, DragonDeKomodo,feu, DragonDeKomodo,terre, AraigneeCracheuse,feu, AraigneeCracheuse, terre, AraigneeCracheuse,air, CrocodileAffame,feu, CrocodileAffame,air, CrocodileAffame,eau, ChefAlpaga,feu, ChefAlpaga,air, Grenouille,eau, Grenouille,feu, Grenouille,air, TortueSonore,feu, TortueSonore,terre, Aigle,feu, Aigle,air, Aigle,terre};
	// Cette fonction est necessaire pour appliquer les modifications des Ã©lements aux cartes
	DeckDefinition(deck1);


	// EXEMPLES DE L' UTILISATION DES DECKS

	//Pour recuperer une carte il faut "deck1[rang voulu]"
	//On peut ainsi afficher le nom de la 13eme carte du deck par exemple :
	printf ("%s\n",deck1[12].Entity.Name);





















	return 0;
}
