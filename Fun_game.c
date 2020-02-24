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
	int Burned;
	int Freezed;

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
		if(deck[i].Entity.Atk < 0){deck[i].Entity.Atk = 0;}
		deck[i].Entity.AtkSpe += deck[i].Element.ModifAtkSpe;
		if(deck[i].Entity.AtkSpe < 0){deck[i].Entity.AtkSpe = 0;}
		deck[i].Entity.Life += deck[i].Element.ModifLife;
		if(deck[i].Entity.Life < 0){deck[i].Entity.Life = 0;}
		deck[i].Entity.LifeSpe += deck[i].Element.ModifLifeSpe;
		if(deck[i].Entity.LifeSpe < 0){deck[i].Entity.LifeSpe = 0;}

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
	if(field[index].Entity.Atk < 0){field[index].Entity.Atk = 0;}
	field[index].Entity.AtkSpe += fusionElement.ModifAtkSpe + fusionCard.Entity.AtkSpe;
	if(field[index].Entity.AtkSpe < 0){field[index].Entity.AtkSpe = 0;}
	field[index].Entity.Life += fusionElement.ModifLife + fusionCard.Entity.Life;
	if(field[index].Entity.Life < 0){field[index].Entity.Life = 0;}
	field[index].Entity.LifeSpe += fusionElement.ModifLifeSpe + fusionCard.Entity.LifeSpe;
	if(field[index].Entity.LifeSpe < 0){field[index].Entity.LifeSpe = 0;}
	field[index].Element = fusionElement;

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

void VerifDeath(card field[3],int index, card EMPTY){

	if(field[index].Entity.LifeSpe <= 0 && field[index].Entity.Life <= 0){

		printf("\n     !!!%s est mort!!!\n",field[index].Entity.Name);

		field[index] = EMPTY;

	}

	if(field[index].Entity.LifeSpe < 0){
		field[index].Entity.LifeSpe = 0;
	}

	if(field[index].Entity.Life < 0){
		field[index].Entity.Life = 0;
	}

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


// Attaque ciblée param : terrain attaquant, terrain defenseur, index de la creature attaquante, index de la creature receveuse, un memo pour determiner si l'attaque est normale ou speciale
int AimedAttack(card fieldA[3], card fieldD[3], int indexA, int indexD, int normSpe, card EMPTY){

	int dmg = 0;
	int dmgContre = 0;

	//ATTAQUE
	if(normSpe == 1){
		dmg = fieldA[indexA].Entity.Atk;
	}else if(normSpe == 2){
		dmg = fieldA[indexA].Entity.AtkSpe;
	}


	if(normSpe == 1){
		fieldD[indexD].Entity.Life -= dmg;
	}else if(normSpe == 2){
		fieldD[indexD].Entity.LifeSpe -= dmg;
	}


	//COUNTER - ATTACK

	if(normSpe == 1){
		dmgContre = fieldD[indexD].Entity.Atk / 2;
	}else if(normSpe == 2){
		dmgContre = fieldD[indexD].Entity.AtkSpe / 2;
	}

	if(normSpe == 1){
		fieldA[indexA].Entity.Life -= dmgContre;
	}else if(normSpe == 2){
		fieldA[indexA].Entity.LifeSpe -= dmgContre;
	}


	VerifDeath(fieldD,indexD,EMPTY);
	VerifDeath(fieldA,indexA,EMPTY);

	return dmg;
};


void sortingHand(card hand[20]){
    element empty = {"Z",10,0,0,0,0,""};
	entity Empty = {"z",0,0,0,0,0,0};
	card EMPTY = {Empty,empty};

	if(hand[0].Element.ID == 10){
		int i = 19;
		int boolean = 0;
		while(boolean != 1){
			if(hand[i].Element.ID != 10){
				hand[0] = hand[i];
				hand[i] = EMPTY;
				boolean = 1;
			}
			i -= 1;
			if(i == -1){boolean = 1;}
		}
	}
	ShowHand(hand);
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

// 1=> combattant a qui c'ets le tour (francais douteux)  ///// 2 => opposant
void EffectPhase(card field1[3], card field2[3], int burned1[3], int burned2[3]){

	for(int i = 0; i<3; i++){

			//Soin passif eau
			if (field1[i].Element.ID == 0){

				printf("   + %s soigne toutes vos autres creatures +\n",field1[i].Entity.Name);

				WaterHeal(field1,i);

			}

			//Brulure feu
			if(burned1[i] > 0){

				burned1[i] -= 1;

				if(field1[i].Entity.Life > 0){

					printf("   !Votre %s souffre de sa brulure!", field1[i].Entity.Name);

					field1[i].Entity.Life -= 1;

				}

			}

			//Degat passif smoke
			if (field1[i].Element.ID == 4){

				printf("   ! %s inflige des degats a toutes les creatures adverses !\n",field1[i].Entity.Name);

				SmokeDamage(field2);

			}

			//soin passif nature
			if (field1[i].Element.ID == 6){

				printf("   + %s se soigne +\n",field1[i].Entity.Name);

				NatureHeal(field1,i);

			}

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
	entity Empty = {"z",0,0,0,0,0,0};
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
	// Je sais que c'est dark d'avoir des fonctions memo mais c'est le seul nom qui m'est venu a l'esprit...
	int memo = 0;
	int memoNormSpe = 0;
	int aim = 0;

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

				printf("\n  Il n'y a aucune creature a l'endroit cible...\n");

			}
			else if (alreadyAttacked[nChoice] == 1){

				printf("\n  Cette creature a deja attaque pour ce tour...\n");

			}
			else if (fieldP[nChoice].Element.ID <= 9 && fieldP[nChoice].Element.ID >= 0){

				alreadyAttacked[nChoice] = 1;

				nChoice = 0;

				while(nChoice != 1 && nChoice != 2){

					printf("\n 1) Attaque normale : %d point(s) d'attaque\n 2) Attaque speciale : %d point(s) d'attaque speciale\n",fieldP[memo].Entity.Atk, fieldP[memo].Entity.AtkSpe);

					scanf("%d",&nChoice);

					memoNormSpe = nChoice;

				}

				if((nChoice == 1 && fieldP[memo].Entity.Atk > 0) || (nChoice == 2 && fieldP[memo].Entity.AtkSpe > 0)){

					aim = 0;

					for(int i = 0; i<3; i++){

						if(fieldA[i].Element.ID != 10){

							aim = 1;

						}

					}

					//Attaque ciblée
					if(aim == 1){

						nChoice = 5;

						while(nChoice != 0 && nChoice != 1 && nChoice != 2 && nChoice != -1){

							printf("\n Qui sera la cible de votre attaque ? (tapez le numero correspondant ou 0 pour annuler)\n");

							ShowField(fieldA);

							scanf("%d",&nChoice);
							nChoice -= 1;

						}

						if(fieldA[nChoice].Element.ID != 10 && nChoice != -1){

							dmg = AimedAttack(fieldP,fieldA,memo,nChoice,memoNormSpe,EMPTY);

						}
						else if (fieldA[nChoice].Element.ID == 10 && nChoice != -1){

							printf("	Il n'y a aucune creature a l'endroit cible...");

						}

					}
					else{

						if(memoNormSpe == 1){

							int none = 0;

							dmg = DirectAttack(&fieldP[memo].Element.ID, &lifeA, &fieldP[memo].Entity.Atk, &none);

							printf("	!Attaque directe!\n");

						}else if (memoNormSpe == 2){

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

		if(actionsP < 1){printf("vous n'avez plus de points d'actions, fin du tour obligatoire\n");}


        //permet de debug
        //card fieldPtemps[3];
		//for (int i = 0; i <3; i ++){
        //    fieldPtemps[i] = fieldP[i];
		//}

		// tour de l'intelligence artificielle----------------------------------------------------
		//ArtificialIntelligence(deckA, handA, cardsDrewA, fieldP, fieldA, elementsList, fieldPtemps);
        // ---------------------------------------------------------------------------------------

        //for (int i = 0; i <3; i ++){
        //    fieldP[i] = fieldPtemps[i];
		//}


		//////EFFECTS PHASE/////////
		printf("\n");

		EffectPhase(fieldP, fieldA, burnedP, burnedA);



		/////////////IA TURN//////////////////////////////
		thunderCounter = 0;
		for(int i = 0; i<3;i++){alreadyAttacked[i] = 0;}


		// ennemy turn

		Draw(deckA,handA,cardsDrewA);
		actionsA = 3;



		int NombreDeMonstre = 0; // compte le nombre de monstres sur le terrais de l'IA pour savoir si la fusion est possible
        int NombreDeMonsteFusion = 0;
		for (int i = 0; i<3; i++){
            if (fieldA[i].Element.ID != 10){
                NombreDeMonstre += 1;

                if(fieldA[i].Element.ID > 3){
                    NombreDeMonsteFusion;
                }
            }
		}

		while (actionsA >= 0){

           int decision = rand()%3;
           printf("ICI LA DEISION/////\n%d\n", decision);
           printf("L ACTION EST DE %d\n", actionsA);

            // Décision -> Attaque
			if (decision == 0 && NombreDeMonstre != 3){

                for (int j = 0; j<3; j++){

                    if (fieldA[j].Element.ID == 10 && actionsA > 0 && handA[0].Element.ID != 10){
                        fieldA[j] = handA[0];
                        handA[0] = EMPTY;
                        actionsA -=1;
                        ShowField(fieldA);
                        //tri des cartes en mains
                        sortingHand(handA);
                    }
                }
			// Décision -> Fusion
			}else if (decision == 1 && NombreDeMonsteFusion > 0 && actionsA >= 2){

			    int fusionOk = 0;
			    int random = rand()%3;
                while (fusionOk != 1){

                    if (fieldA[random].Element.ID <= 3){
                        Fusion(fieldA,handA[0],random,elementsList);
                        handA[0] = EMPTY;
                        actionsA -=2;
                        sortingHand(handA);
                        fusionOk = 1;
                    }
                }
            }else if(decision == 2){
                for(int i = 0; i < 3; i++){
                    if (fieldA[i].Element.ID < 10){
                        for (int j = 0; j < 3; j++){
                            int attaque = 0;

                            if (fieldP[j].Entity.AtkSpe >= fieldP[j].Entity.Atk)
                                attaque = fieldA[i].Entity.AtkSpe;
                            else
                                attaque = fieldA[i].Entity.Atk;


                            if (fieldP[j].Element.ID < 10){
                                int attaquenull = 0;
                                int lifenull = 0;

                                if (fieldP[j].Entity.AtkSpe == 0)
                                    attaquenull = 1;
                                else if (fieldP[j].Entity.Atk == 0)
                                    attaquenull = 2;

                                if (fieldP[j].Entity.Life <= fieldP[j].Entity.LifeSpe || attaquenull == 2){
                                    int dmg = AimedAttack(fieldA, fieldP, i, j, 2, EMPTY);
                                    printf("%s a attaque ton %s, s'est pris %d degats speciaux\n", fieldA[i].Entity.Name, fieldP[j].Entity.Name, dmg);
                                    actionsA -= 1;

                                }else if (fieldP[j].Entity.Life > fieldP[j].Entity.LifeSpe || attaquenull == 1){
                                    AimedAttack(fieldA, fieldP, i, j, 1, EMPTY);
                                    printf("%s a attaque ton %s, s'est pris %d degats\n", fieldA[i].Entity.Name, fieldP[j].Entity.Name, dmg);
                                    actionsA -=1;
                                }


                            }else if (j == 2 && fieldA[i].Element.ID < 10){
                                int dmg = DirectAttack(&fieldA[i].Element.ID, &lifeA, &attaque, &thunderCounter);
                                printf("%s vous a fait %d degats, vous n'avez plus que %d vies\n", fieldA[i].Entity.Name, attaque, lifeA);
                                actionsA -=1;
                            }
                        }
                    }
                    printf("%d", actionsA);
                }
            }
        }
    }
};


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
	element sable = {"e Sable",9,0,-1,1,1,"reduit la contre attaque recue a 1 point de degat max",1};

	element elementsList[10] = {eau,feu,air,terre, fumee,glace,nature,foudre,lave,sable};


	entity Loup = {"Loup d", 4,4,3,3,0,0};                                    //balance
	entity CrabeRoyal = {"Crabe Royal d", 7, 4, 3, 2,0,0};                    //HP
	entity DragonDeKomodo = {"Drakodo d", 4, 4, 6, 0,0,0};                    //attack + HP (phy + spe)
	entity AraigneeCracheuse = {"Araignee Cracheuse d", 2, 4, 2, 6,0,0};      //attack spe
	entity CrocodileAffame = {"Crocodile d", 5, 2, 5, 2,0,0};                 //attack + HP
	entity ChefAlpaga = {"Chef Alpaga d", 5, 5, 2, 4,0,0};                    //HP (phy + spe) + attack spe
	entity Grenouille = {"Crapaud d", 4, 7, 0, 3,0,0};                        //HP mag + attack spe
    entity TortueSonore = {"Tortue Sonore d", 6, 2, 2, 6,0,0};                //HP + attack spe
    entity BoucTemeraire = {"Bouc Temeraire d", 3, 3, 5, 5,0,0};              //attack (phy + spe)
    entity Aigle = {"Aigle d", 3, 4, 6, 2,0,0};                               //attack
    entity Elephant = {"Elephant d", 10, 0, 4, 0,0,0};                        //HP
    entity Jaguar = {"Jaguar d", 2, 6, 6, 2,0,0};                             //HP spe + attack
    entity SerpentCorosif = {"Serpent Corosif d", 0, 10, 0, 4,0,0};           //HP spe + attack spe
    entity PlanteMarecageuse = {"Plante Marecargeuese d", 4, 4, 0, 6,0,0};    //attack spe
    entity Scorpion = {"Scorpion d", 6, 2, 2, 4,0,0};                         //attack + attack spe
    entity Phasme = {"Phasme d", 6, 6, 2, 2,0,0};                             // HP (phy + spe)
    entity Buffle = {"Buffle d", 5, 2, 4, 2,0,0};                             //HP + attack
    entity ManteReligieuse = {"Mante Religieuse d", 3, 4, 6, 2,0,0};          //attack



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
