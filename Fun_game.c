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
	// Une carte est d�finie par une entit� qui r�pond � un �l�ment
	entity Entity;
	// Il faudra ensuite changer les stats de l'entit� en fonction des modificateurs de l'�l�ment.
	element Element;

};
typedef struct Card card;



void clearScreen(){
	for(int i = 0; i <70; i++){
		printf("\n");
	}
};



void DeckDefinition (card deck[20]){

	for (int i = 0; i < 20; i++){

		strcat(deck[i].Entity.Name, deck[i].Element.Name);
		deck[i].Entity.Atk += deck[i].Element.ModifAtk;
		deck[i].Entity.AtkSpe += deck[i].Element.ModifAtkSpe;
		deck[i].Entity.Life += deck[i].Element.ModifLife;
		deck[i].Entity.LifeSpe += deck[i].Element.ModifLifeSpe;

	}

};









void Draw (card deck[20], card hand[20], int cardsDrew[20]){

	int nRandom = 0;
	int verif = 0;
	int index = 0;

	while(verif == 0){

		nRandom = rand()%20;
		verif = 1;

		for (int i = 0; i<20; i++){

			if(cardsDrew[i] == nRandom){verif = 0;}

		}

	}

	for (int i = 0; i<20; i++){

		if (hand[i].Element.ID == 10){

			index = i;
			i = 22;

		}

	}

	hand[index] = deck[nRandom];

};


void ShowHand(card hand[20]){

	//printf("\n");
	int nCounter = 0;

	for(int i = 0; i<20; i++){

		if (hand[i].Element.ID != 10){

			printf(" - %s  %d/%d/%d/%d\n",hand[i].Entity.Name,hand[i].Entity.Atk,hand[i].Entity.AtkSpe,hand[i].Entity.Life,hand[i].Entity.LifeSpe);

		}
		else{nCounter += 1;}

	}

	if (nCounter >= 20){printf(" - (main vide)\n");}

	printf("\n");

};

void ShowField(card field1[20]){

	printf("\n");

	for(int i = 0; i<3; i++){

		if (field1[i].Element.ID == 10){

			printf(" %d- (vide)\n",i+1);

		}
		else{

			printf(" %d- %s  %d/%d/%d/%d\n",i+1,field1[i].Entity.Name,field1[i].Entity.Atk,field1[i].Entity.AtkSpe,field1[i].Entity.Life,field1[i].Entity.LifeSpe);

		}

	}

};

void CardDetail(card cardShown){

	printf("\n -> \"%s\" \n   Attaque : %d\n   Attaque spe : %d\n   Vie restante : %d\n   Vie spe restante : %d\n   Pouvoir d'element : %s\n\n",cardShown.Entity.Name, cardShown.Entity.Atk, cardShown.Entity.AtkSpe, cardShown.Entity.Life, cardShown.Entity.LifeSpe, cardShown.Element.Description);

};



void Fight (card deckP[20], card deckA[20]){

	// Sert a connaitre les cartes deja piochees pour ne pas les repiocher a nouveau... On remplacera les -1 par l'index des cartes deja piochees
	int cardsDrewP[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int cardsDrewA[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	int actionsP = 3;
	int actionsA = 3;

	element empty = {"Z",10,0,0,0,0,""};
	entity Empty = {"z",0,0,0,0};
	card EMPTY = {Empty,empty};

	// Les terrains des deux joueurs
	card fieldA[3] ={Empty,empty, Empty,empty, Empty,empty};
	card fieldP[3] ={Empty,empty, Empty,empty, Empty,empty};

	// Les mains des deux joueurs
	card handP[20] = {Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty};
	card handA[20] = {Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty};


	Draw(deckA,handA,cardsDrewA);
	Draw(deckA,handA,cardsDrewA);
	Draw(deckA,handA,cardsDrewA);


	Draw(deckP,handP,cardsDrewP);
	Draw(deckP,handP,cardsDrewP);

	int bGame = 0;
	char sChoice[64];
	int nChoice = 0;

	while (bGame == 0){

		clearScreen();

		////////////PLAYER TURN//////////////////////////

		printf("\n\n	---VOTRE TOUR---\n");
		///////SET UP PHASE////////
		Draw(deckP,handP,cardsDrewP);
		strcpy(sChoice,"0");
		actionsP = 3;
		nChoice = 0;

		while (strcmp(sChoice,"Attaquer") !=0){

			printf("\n  Votre main est composee de :\n");
			ShowHand(handP);
			printf("Vous avez %d point(s) d'action restants\n",actionsP);
			printf(" -Tapez un nom de carte pour la poser\n");
			printf(" -Tapez \"Attaquer\" pour passer en phase d'attaque\n");
			printf(" -Tapez \"Check\" pour regarder le terrain\n");

			if(scanf(" %63[^\n]",sChoice)==1){};
			printf("\n");


			if(actionsP >= 1){

				for(int i = 0; i<20; i++){

					if( strcmp(handP[i].Entity.Name,sChoice) == 0){

						nChoice = -1;

						while(nChoice != 0 && nChoice != 1 && nChoice != 2){

							printf("   Ou voulez-vous poser cette carte ? (posez la sur une carte deja posee pour faire une fusion !)\n");

							ShowField(fieldP);

							scanf("%d",&nChoice);
							// On doit r�duire nChoice de 1 car dans ShowField() on ment au joueur sur les num�ros de cases
							nChoice -= 1;

							printf("\n");

						}

						if(fieldP[nChoice].Element.ID == 10){

							fieldP[nChoice] = handP[i];
							handP[i] = EMPTY;

							actionsP -=1;

						}
						else if (fieldP[nChoice].Element.ID <=9 && fieldP[nChoice].Element.ID >= 0){

							//FUUUUUUU-SIOOOOON
							printf("\n Fusion a coder\n");

						}

					}

				}

			}


			//Board check
			if(strcmp(sChoice, "Check") == 0){

				printf("\n   Terrain adverse :\n");
				ShowField(fieldA);

				printf("\n   Votre terrain :\n");
				ShowField(fieldP);

				printf("\n Tapez un nom de carte pour la voir en detail, tapez n'importe quoi d'autre pour revenir au menu\n");

				if(scanf(" %63[^\n]",sChoice)==1){};

				for(int i = 0; i<3; i++){

					if( strcmp(fieldP[i].Entity.Name,sChoice) == 0){

						printf("\n\n");
						CardDetail(fieldP[i]);

					}

					if( strcmp(fieldA[i].Entity.Name,sChoice) == 0){

						printf("\n\n");
						CardDetail(fieldA[i]);

					}

				}

				// Pour �viter que le joueur tape "Attaquer" et que �a lance la phase d'attaque
				strcpy(sChoice,"");

			}

		}


		//////ATTACK PHASE////////
		printf("\nAttaque-----------\n");



		/////////////IA TURN//////////////////////////////

	}

};

void ArtificialIntelligence(){

    // ennemy turn
    //draw
    Draw(deckA,handA,cardsDrewA);
    int actionsA = 3;
    // si le board n'est pas rempli, l'ennemis pose une carte sur le terrain
    for (int i = 0, i<=3, i++){
        if(fieldA[i].Element.ID == 10 && actionsA > 0){
            fieldA[i] = handA[0];
            handP[i] = EMPTY;
            actionsA -=1;
            //tri des cartes en mains
            sortingHand(&handA);
            }
    }
    for (int i = 1, i<=actionsA ,i++){
        //attacker
    }

}

void sortingHand(card* hand){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            if (hand[i].Element.ID > hand[j].Element.ID){

                card nTempo = hand[i].Element.ID;
                hand[i].Element.ID = hand[j].Element.ID;
                hand[j].Element.ID = nTempo;
            }
        }
    }
}


int main(){

	srand(time(NULL));

	clearScreen();

	//////////////////////////////////////////BASE DE DONNEES DES CARTES//////////////////////////////////////////////////////////
	element eau = {"'Eau",0,-1,1,1,0,"Soigne 1PV par tour aux autres creatures sous votre controle"};
	element feu = {"e Feu",1,2,0,-1,0,"Inflige deux tours de brulure (-1PV par tour) pour toute attaque physique effectuee"};
	element air = {"'Air",2,-1,0,1,1,"Subit 1 dégat magique de moins par attaque magique subie"};
	element terre = {"e Terre",3,0,-1,2,0,"Subit 1 dégat physique de moins par attaque physique subie"};

	element fumee = {"e Fumee",4,0,1,1,-1,"Inflige 1 degat a tous les adversaires par tour"};
	element glace = {"e Glace",5,0,1,-1,1,"Reduit l'attaque de 1 point pendant 2 tours a celui qui subit une attaque de glace"};
	element nature = {"e Nature",6,-1,0,1,1,"Se soigne de 1PV par tour et reduit les degats subits de 1 a chaque attaque"};
	element foudre = {"e Foudre",7,0,2,0,-1,"Fait un degat magique de plus et un degat supplementaire pour chaque attaque foudre deja lancee ce tour"};
	element lave = {"e Lave",8,1,0,1,-1,"Inflige un degat supplementaire de contre-attaque"};
	element sable = {"e Sable",9,0,-1,1,1,"Divise par deux les degats de contre-attaque recus"};


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
    entity Elephant = {"Elephant d", 10, 0, 4, 0};                        //HP
    entity Jaguar = {"Jaguar d", 2, 6, 6, 2};                             //HP spe + attack
    entity SerpentCorosif = {"Serpent Corosif d", 0, 10, 0, 4};           //HP spe + attack spe
    entity PlanteMarecageuse = {"Plante Marecargeuese d", 4, 4, 0, 6};    //attack spe
    entity Scorpion = {"Scorpion d", 6, 2, 2, 4};                         //attack + attack spe
    entity Phasme = {"Phasme d", 6, 6, 2, 2};                             // HP (phy + spe)
    entity Buffle = {"Buffle d", 5, 2, 4, 2};                             //HP + attack
    entity ManteReligieuse = {"Mante Religieuse d", 3, 4, 6, 2};          //attack



	/////////////////////////////////////////////////DEFINITION DES DECKS///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Ce tableau contient 20 cartes, c'est donc un deck, /! Les cartes sont triées donc quand on piochera il faudra prendre une carte aleatoire parmi le deck
	card deck1[20] = {Loup,feu, Loup,terre, DragonDeKomodo,feu, DragonDeKomodo,terre, AraigneeCracheuse,feu, AraigneeCracheuse, terre, AraigneeCracheuse,air, CrocodileAffame,feu, CrocodileAffame,air, CrocodileAffame,eau, ChefAlpaga,feu, ChefAlpaga,air, Grenouille,eau, Grenouille,feu, Grenouille,air, TortueSonore,feu, TortueSonore,terre, Aigle,feu, Aigle,air, Aigle,terre};
	// Cette fonction est necessaire pour appliquer les modifications des élements aux cartes
	DeckDefinition(deck1);


	// EXEMPLES DE L' UTILISATION DES DECKS

	//Pour recuperer une carte il faut "deck1[rang voulu]"
	//On peut ainsi afficher le nom de la 13eme carte du deck par exemple :
	//printf ("%s\n",deck1[12].Entity.Name);















	Fight (deck1,deck1);





	return 0;
}
