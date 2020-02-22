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
	int bFusion;

};
typedef struct Element element;

struct Card{
	// Une carte est définie par une entité qui répond à un élément
	entity Entity;
	// Il faudra ensuite changer les stats de l'entité en fonction des modificateurs de l'élément.
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

	for (int i = 0; i<20; i++){

		if (cardsDrew[i] == -1){

			index = i;
			i = 22;

		}

	}

	cardsDrew[index] = nRandom;

};

void Fusion(card field[3], card fusionCard,int index,element elementsList[10]){

	element fusionElement;


	printf("\n!!! La Fusion entre %s et %s",field[index].Entity.Name, fusionCard.Entity.Name);


	strcpy(field[index].Entity.Name, "Creature Fusion d");

	for(int i = 0; i<4; i++){

		if(field[index].Element.ID == i){

			for(int j = 0; j<4; j++){

				if(fusionCard.Element.ID == j){

					if(i == j){
						fusionElement = elementsList[i];
					}
					else if(i+j == 1){
						fusionElement = elementsList[4];
					}
					else if(i+j == 2){
						fusionElement = elementsList[5];
					}
					else if(i+j == 3 && (i == 0 || j == 0)){
						fusionElement = elementsList[6];
					}
					else if(i+j == 3 && (i == 1 || j == 1)){
						fusionElement = elementsList[7];
					}
					else if(i+j == 4){
						fusionElement = elementsList[8];
					}
					else if(i+j == 5){
						fusionElement = elementsList[9];
					}

				}

			}

		}

	}

	strcat(field[index].Entity.Name, fusionElement.Name);
	field[index].Entity.Atk += fusionElement.ModifAtk + fusionCard.Entity.Atk;
	field[index].Entity.AtkSpe += fusionElement.ModifAtkSpe + fusionCard.Entity.AtkSpe;
	field[index].Entity.Life += fusionElement.ModifLife + fusionCard.Entity.Life;
	field[index].Entity.LifeSpe += fusionElement.ModifLifeSpe + fusionCard.Entity.LifeSpe;
	field[index].Element.bFusion = 1;
	strcpy(field[index].Element.Description, fusionElement.Description);

	printf(" resulte de : %s !!!\n",field[index].Entity.Name);

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


int DirectAttack(int * ID, int * life, int * dmg, int * thunderCounter){

	int thunderBonus = 0;

	if(*thunderCounter >= 1 || *ID == 7){

		thunderBonus += 1;

		thunderBonus += 2* *thunderCounter;

		printf("	!Bonus foudre : %d degats !\n",thunderBonus);

		*dmg += thunderBonus;

	}

	*life -= *dmg;

	return *dmg;
};



void SmokeDamage(card field[3]){

	int nRandom = 0;

	for(int i = 0; i<3; i++){

		if(field[i].Element.ID != 10){

			nRandom = rand()%2;

			if(nRandom == 0 && field[i].Entity.Life > 0){

				field[i].Entity.Life -= 1;

			}
			else if(nRandom == 1 && field[i].Entity.LifeSpe > 0){

				field[i].Entity.LifeSpe -= 1;

			}
			else if(field[i].Entity.Life > 0){

				field[i].Entity.Life -= 1;

			}
			else if(field[i].Entity.LifeSpe > 0){

				field[i].Entity.LifeSpe -= 1;

			}

		}

	}

};

void WaterHeal(card field[3], int index){

	for(int i = 0; i < 3; i++){

		//Pour eviter que la creature s'auto-soigne
		if(index == i){i++;}

		if(field[i].Element.ID != 10 && i < 4){

			if(field[i].Entity.Life > field[i].Entity.LifeSpe && field[i].Entity.LifeSpe > 0){

				field[i].Entity.LifeSpe++;

			}
			else if(field[i].Entity.Life < field[i].Entity.LifeSpe && field[i].Entity.Life > 0){

				field[i].Entity.Life++;

			}
			else if(field[i].Entity.Life > 0){

				field[i].Entity.Life++;

			}
			else if(field[i].Entity.LifeSpe > 0){

				field[i].Entity.LifeSpe++;

			}

		}

	}

};

void NatureHeal(card field[3], int index){

	if(field[index].Entity.Life > field[index].Entity.LifeSpe && field[index].Entity.LifeSpe > 0){

		field[index].Entity.LifeSpe++;

	}
	else if(field[index].Entity.Life < field[index].Entity.LifeSpe && field[index].Entity.Life > 0){

		field[index].Entity.Life++;

	}
	else if(field[index].Entity.Life > 0){

		field[index].Entity.Life++;

	}
	else if(field[index].Entity.LifeSpe > 0){

		field[index].Entity.LifeSpe++;

	}

};





void Fight (card deckP[20], card deckA[20], element elementsList[10]){

	// Sert a connaitre les cartes deja piochees pour ne pas les repiocher a nouveau... On remplacera les -1 par l'index des cartes deja piochees
	int cardsDrewP[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	int cardsDrewA[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

	int actionsP = 3;
	int actionsA = 3;

	int lifeA = 30;
	int lifeP = 30;


	element empty = {"Z",10,0,0,0,0,""};
	entity Empty = {"z",0,0,0,0};
	card EMPTY = {Empty,empty};

	// Les terrains des deux joueurs
	card fieldA[3] ={Empty,empty, Empty,empty, Empty,empty};
	card fieldP[3] ={Empty,empty, Empty,empty, Empty,empty};

	// Les mains des deux joueurs
	card handP[20] = {Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty};
	card handA[20] = {Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty, Empty,empty,Empty,empty, Empty,empty};


	int dmg = 0;
	int i = 0;

	// Chaque index passe a 1 si la creature qui correspond a l'index a deja attaqué
	int alreadyAttacked[3] = {0,0,0};
	int burnedA[3] = {0,0,0};
	int burnedP[3] = {0,0,0};


	int thunderCounter = 0;



	Draw(deckA,handA,cardsDrewA);
	Draw(deckA,handA,cardsDrewA);
	Draw(deckA,handA,cardsDrewA);


	Draw(deckP,handP,cardsDrewP);
	Draw(deckP,handP,cardsDrewP);

	char sChoice[64];
	int nChoice = 0;
	int memo = 0;

	while (lifeA >= 0 && lifeP >= 0){

		clearScreen();

		////////////PLAYER TURN//////////////////////////

		printf("\n\n	---VOTRE TOUR---\n");
		///////SET UP PHASE////////
		Draw(deckP,handP,cardsDrewP);
		strcpy(sChoice,"0");
		actionsP = 3;
		nChoice = 0;
		thunderCounter = 0;
		for(int i = 0; i<3;i++){alreadyAttacked[i] = 0;}


		while (strcmp(sChoice,"Attaquer") !=0){

			printf("\n  Votre main est composee de :\n");
			ShowHand(handP);
			printf("Vous avez %d point(s) d'action restants\n",actionsP);
			printf(" -Tapez un nom de carte pour la poser\n");
			printf(" -Tapez \"Attaquer\" pour passer en phase d'attaque\n");
			printf(" -Tapez \"Check\" pour regarder le terrain\n");

			if(scanf(" %63[^\n]",sChoice)==1){};
			printf("\n");

			for(int i = 0; i<20; i++){

				if( strcmp(handP[i].Entity.Name,sChoice) == 0 && actionsP >= 1){

					nChoice = -1;

					while(nChoice != 0 && nChoice != 1 && nChoice != 2){

						printf("   Ou voulez-vous poser cette carte ? (posez la sur une carte deja posee pour faire une fusion !)\n");

						ShowField(fieldP);

						scanf("%d",&nChoice);
						// On doit réduire nChoice de 1 car dans ShowField() on ment au joueur sur les numéros de cases
						nChoice -= 1;

						printf("\n");

					}

					if(fieldP[nChoice].Element.ID == 10){

						fieldP[nChoice] = handP[i];
						handP[i] = EMPTY;

						actionsP -=1;

					}
					else if (fieldP[nChoice].Element.ID <=3 && fieldP[nChoice].Element.ID >= 0 && actionsP >= 2 && fieldP[nChoice].Element.bFusion == 0){

						//FUUUUUUU-SIOOOOON
						Fusion(fieldP,handP[i],nChoice,elementsList);
						handP[i] = EMPTY;

						actionsP -=2;

					}
					else if (actionsP < 2){

						printf("Vous n'avez pas les 2 points d'actions necessaires pour effectuer une fusion...\n");

					}
					else if (fieldP[nChoice].Element.bFusion == 1){

						printf("Vous ne pouvez pas effectuer de fusion sur une creature deja fusionnee...\n");

					}

				}
				else if(strcmp(handP[i].Entity.Name,sChoice) == 0 && actionsP == 0){

					printf("!Vous n'avez plus de points d'actions, attendez le prochain tour pour poser des creatures!\n");

				}

			}





			if(actionsP >= 1){

				for(int i = 0; i<20; i++){

					if( strcmp(handP[i].Entity.Name,sChoice) == 0){

						nChoice = -1;

						while(nChoice != 0 && nChoice != 1 && nChoice != 2){

							printf("   Ou voulez-vous poser cette carte ? (posez la sur une carte deja posee pour faire une fusion !)\n");

							ShowField(fieldP);

							scanf("%d",&nChoice);
							// On doit réduire nChoice de 1 car dans ShowField() on ment au joueur sur les numéros de cases
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

				// Pour éviter que le joueur tape "Attaquer" et que ça lance la phase d'attaque
				strcpy(sChoice,"");

			}

		}


		//////ATTACK PHASE////////
		clearScreen();
		printf("\n--------------Phase d'Attaque-----------\n");

		while(actionsP>0 && nChoice != 444){

			nChoice = 5;

			while(nChoice != 0 && nChoice != 1 && nChoice != 2 && nChoice != -1){

				printf("\n	Voici votre terrain, chaque creature peut attaquer une fois pour 1 point d'action (points d'actions restatnts : %d ): \n",actionsP);

				ShowField(fieldP);

				printf("\n	Tapez un numero de terrain pour attaquer avec la creature associee, tapez 0 pour terminer votre tour\n");

				scanf("%d",&nChoice);
				nChoice -= 1;
				memo = nChoice;

			}


			if(nChoice == -1){

				nChoice = 444;

			}
			else if(fieldP[nChoice].Element.ID == 10){

				printf("  Il n'y a aucune creature a l'endroit cible...\n");

			}
			else if (alreadyAttacked[nChoice] == 1){

				printf("  Cette creature a deja attaque pour ce tour...\n");

			}
			else if (fieldP[nChoice].Element.ID <= 9 && fieldP[nChoice].Element.ID >= 0){

				nChoice = 0;

				alreadyAttacked[nChoice] = 1;

				while(nChoice != 1 && nChoice != 2){

					printf("\n 1) Attaque normale : %d point(s) d'attaque\n 2) Attaque speciale : %d point(s) d'attaque speciale\n",fieldP[memo].Entity.Atk, fieldP[memo].Entity.AtkSpe);

					scanf("%d",&nChoice);

				}

				if((nChoice == 1 && fieldP[memo].Entity.Atk > 0) || (nChoice == 2 && fieldP[memo].Entity.AtkSpe > 0)){

					for(int i = 0; i<3; i++){

						if(fieldA[i].Element.ID != 10){

							i = 22;

						}

					}

					if(i == 22){

						printf("&&Attaque ciblee a coder\n");

					}
					else{

						if(nChoice == 1){

							int none = 0;

							dmg = DirectAttack(&fieldP[memo].Element.ID, &lifeA, &fieldP[memo].Entity.Atk, &none);

							printf("	!Attaque directe!\n");

						}
						else if (nChoice == 2){

							dmg = DirectAttack(&fieldP[memo].Element.ID, &lifeA, &fieldP[memo].Entity.AtkSpe, &thunderCounter);

							printf("	!Attaque speciale directe!\n");

						}

					}

					printf("	!Vous infligez %d degats!\n",dmg);

					actionsP -= 1;

				}
				else{

					printf("Vous n'avez pas de points d'attaque dans la categorie demandee, vous ne pouvez pas attaquer...\n");
				}
			}
		}


		// tour de l'intelligence artificielle----------------------------------------------------
		ArtificialIntelligence(deckA, handA, cardsDrewA, fieldP, fieldA, elementsList);
        // ---------------------------------------------------------------------------------------


		if(actionsP < 1){printf("vous n'avez plus de points d'actions, fin du tour obligatoire\n");}

		//////EFFECTS PHASE/////////
		printf("\n");

		for(int i = 0; i<3; i++){

			//Soin passif eau
			if (fieldP[i].Element.ID == 0){

				printf("   + %s soigne toutes vos autres creatures +\n",fieldP[i].Entity.Name);

				WaterHeal(fieldP,i);

			}

			//Brulure feu
			for(int j = 0; j<3; j++){

				if(burnedP[j] > 0){

					burnedP[j] -= 1;

					if(fieldP[j].Entity.Life > 0){

						printf("   !Votre %s souffre de sa brulure!", fieldP[j].Entity.Name);

						fieldP[j].Entity.Life -= 1;

					}

				}

			}

			//Degat passif smoke
			if (fieldP[i].Element.ID == 4){

				printf("   ! %s inflige des degats a toutes les creatures adverses !\n",fieldP[i].Entity.Name);

				SmokeDamage(fieldA);

			}

			//soin passif nature
			if (fieldP[i].Element.ID == 6){

				printf("   + %s se soigne +\n",fieldP[i].Entity.Name);

				NatureHeal(fieldP,i);

			}

		}




		/////////////IA TURN//////////////////////////////
		thunderCounter = 0;
		for(int i = 0; i<3;i++){alreadyAttacked[i] = 0;}



	}

};

// deck de l'intelligence, ses cartes, ceux qu'il a tires, les cartes du terrain de l'adversaire, les cartes du terrain de l'intelligence, empty function, +elementlist(pour rentrer dans la fonction fusion)
void ArtificialIntelligence(card deck[20], card hand[20], int cardsDrew[20], card fieldPlayer[3], card fieldAtrificialPlayer[3], element elementsList[10]){

    element empty = {"Z",10,0,0,0,0,""};
	entity Empty = {"z",0,0,0,0};
	card EMPTY = {Empty,empty};

    // ennemy turn
    //draw
    Draw(deck,hand,cardsDrew);
    int actions = 3;
    // si le board n'est pas rempli, l'ennemis pose une carte sur le terrain
    for (int i = 0; i<=3; i++){
        if (fieldAtrificialPlayer[i].Element.ID == 10 && actions > 0){
            fieldAtrificialPlayer[i] = hand[0];
            hand[0] = EMPTY;
            actions -=1;
            ShowField(fieldAtrificialPlayer);
            //tri des cartes en mains
            sortingHand(hand);
        //permet la fusion à  un point i
        }else if (fieldAtrificialPlayer[i].Element.ID <= 3 && actions >= 2){
            Fusion(fieldAtrificialPlayer,hand[i],i,elementsList);
            hand[i] = EMPTY;
            actions -=2;
        }
    };

}

void sortingHand(card hand[20]){
    element empty = {"Z",10,0,0,0,0,""};
	entity Empty = {"z",0,0,0,0};
	card EMPTY = {Empty,empty};



    int i = 20;
    int boolean = 0;
    while(boolean != 1){
        if(hand[i].Element.ID != 10){
            hand[0] = hand[i];
            hand[i] = EMPTY;
            boolean = 1;
        }
        i += 1;
    }
    ShowHand(hand);
}


int main(){

	srand(time(NULL));

	clearScreen();

	//////////////////////////////////////////BASE DE DONNEES DES CARTES//////////////////////////////////////////////////////////

	element eau = {"'Eau",0,-1,1,1,0,"Soigne 1PV par tour aux autres creatures sous votre controle",0};
	element feu = {"e Feu",1,2,0,-1,0,"Inflige deux tours de brulure (-1PV par tour) pour toute attaque physique effectuee",0};
	element air = {"'Air",2,-1,0,1,1,"Subit 1 degat magique de moins par attaque magique subie",0};
	element terre = {"e Terre",3,0,-1,2,0,"Subit 1 degat physique de moins par attaque physique subie",0};

	element fumee = {"e Fumee",4,0,1,1,-1,"Inflige 1 degat a tous les adversaires par tour",1};
	element glace = {"e Glace",5,0,1,-1,1,"Reduit l'attaque de 1 point pendant 2 tours a celui qui subit une attaque de glace",1};
	element nature = {"e Nature",6,-1,0,1,1,"Se soigne de 1PV par tour et reduit les degats subits de 1 a chaque attaque",1};
	element foudre = {"e Foudre",7,0,2,0,-1,"Fait un degat magique de plus et 2 degat supplementaire pour chaque attaque foudre deja lancee ce tour",1};
	element lave = {"e Lave",8,1,0,1,-1,"Inflige un degat supplementaire de contre-attaque",1};
	element sable = {"e Sable",9,0,-1,1,1,"Divise par deux les degats de contre-attaque recus",1};

	element elementsList[10] = {eau,feu,air,terre, fumee,glace,nature,foudre,lave,sable};

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

	// Ce tableau contient 20 cartes, c'est donc un deck, /! Les cartes sont triÃ©es donc quand on piochera il faudra prendre une carte aleatoire parmi le deck
	card deck1[20] = {Loup,feu, Loup,terre, DragonDeKomodo,feu, DragonDeKomodo,terre, AraigneeCracheuse,feu, AraigneeCracheuse, terre, AraigneeCracheuse,air, CrocodileAffame,feu, CrocodileAffame,air, CrocodileAffame,eau, ChefAlpaga,feu, ChefAlpaga,air, Grenouille,eau, Grenouille,feu, Grenouille,air, TortueSonore,feu, TortueSonore,terre, Aigle,feu, Aigle,air, Aigle,terre};
	// Cette fonction est necessaire pour appliquer les modifications des Ã©lements aux cartes
	DeckDefinition(deck1);


	// EXEMPLES DE L' UTILISATION DES DECKS

	//Pour recuperer une carte il faut "deck1[rang voulu]"
	//On peut ainsi afficher le nom de la 13eme carte du deck par exemple :
	//printf ("%s\n",deck1[12].Entity.Name);















	Fight (deck1,deck1,elementsList);





	return 0;
}
