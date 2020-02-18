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
	// Pour l'ID : 0=>eau / 1=>feu / 2=>air / 3=>terre // 4=>air / 5=>glace / 6=>nature / 7=>foudre / 8=>lave / 9=>sable
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






void DeckDefinition (card deck[20]){
	
	for (int i = 0; i < 20; i++){
		
		strcat(deck[i].Entity.Name, deck[i].Element.Name);
		deck[i].Entity.AtkPhy += deck[i].Element.ModifAtkPhy;
		deck[i].Entity.AtkMag += deck[i].Element.ModifAtkMag;
		deck[i].Entity.LifePhy += deck[i].Element.ModifLifePhy;
		deck[i].Entity.LifeMag += deck[i].Element.ModifLifeMag;
	
	}
	
};

int main(){
	
	srand(time(NULL));
	
	
	element eau = {"'Eau",0,-1,1,1,0,"Soigne 1PV par tour aux autres creatures sous votre controle"};
	element feu = {"e Feu",1,2,0,-1,0,"Inflige deux tours de brulure (-1PV par tour) pour toute attaque physique effectuée"};
	element air = {"'Air",2,-1,0,1,1,"Subit 1 dégat magique de moins par attaque magique subie"};
	element terre = {"e Terre",3,0,-1,2,0,"Subit 1 dégat physique de moins par attaque physique subie"};
	
	element fumee = {"e Fumee",4,0,1,1,-1,"Inflige 1 degat a tous les adversaires par tour"};
	element glace = {"e Glace",5,0,1,-1,1,"Reduit l'attaque de 1 point pendant 2 tours a celui qui subit une attaque de glace"};
	element nature = {"e Nature",6,-1,0,1,1,"Est soigné de 1PV par tour et reduit les degats subits de 1 a chaque attaque"};
	element foudre = {"e Foudre",7,0,2,0,-1,"Fait un degat magique de plus et un degat supplementaire pour chaque attaque foudre deja lancee ce tour"};
	element lave = {"e Lave",8,1,0,1,-1,"Inflige un degat supplementaire de contre-attaque"};
	element sable = {"e Sable",9,0,-1,1,1,"Divise par deux les degats de contre-attaque recus"};

	entity Loup = {"Loup d", 4,4,3,3};                                    //balance
	entity CrabeRoyal = {"Crabe Royal d", 7, 4, 3, 0};                    //HP
	entity DragonDeKomodo = {"Drakodo d", 4, 4, 6, 0};                    //attack + HP (phy + spe)
	entity AraigneeCracheuse = {"Araignee Cracheuse d", 2, 4, 2, 6};      //attack spe
	entity CrocodileAffame = {"Crocodile d", 5, 2, 5, 2};                   //attack + HP
	entity ChefAlpaga = {"Chef Alpaga d", 5, 5, 2, 4};                    //HP (phy + spe) + attack spe
	entity Grenouille = {"Crapaud d", 4, 7, 0, 3};                        //HP mag + attack spe
    entity TortueSonore = {"Tortue Sonore d", 6, 2, 2, 6};                 //HP + attack spe
    entity BoucTemeraire = {"Bouc Temeraire d", 3, 3, 5, 5};              //attack (phy + spe)
    entity Aigle = {"Aigle d", 3, 4, 6, 2};                               //attack

	// Ce tableau contient 20 cartes, c'est donc un deck, /! Les cartes sont triées donc quand on piochera il faudra prendre une carte aléatoire parmi le deck
	card deck[20] = {Loup,feu, Loup,terre, DragonDeKomodo,feu, DragonDeKomodo,terre, AraigneeCracheuse,feu, AraigneeCracheuse, terre, AraigneeCracheuse,air, CrocodileAffame,feu, CrocodileAffame,air, CrocodileAffame,eau, ChefAlpaga,feu, ChefAlpaga,air, Grenouille,eau, Grenouille,feu, Grenouille,air, TortueSonore,feu, TortueSonore,terre, Aigle,feu, Aigle,air, Aigle,terre};
	// Cette fonction est necessaire pour appliquer les modifications des élements aux cartes
	DeckDefinition(deck);


	// EXEMPLES DE L' UTILISATION DES DECKS

	//Pour récupérer une carte il faut "deck1[rang voulu]"
	//On peut ainsi afficher le nom de la 13ème carte du deck par exemple :
	printf ("%s\n",deck[12].Entity.Name);


	return 0;
}
