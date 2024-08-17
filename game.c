#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

void intro () {
    printf("The red player has four (04) pieces named R1, R2, R3, and R4.\n");
    printf("The green player has four (04) pieces named G1, G2, G3, and G4.\n");
    printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
    printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
}
int main () {
	int piece;
	int CurrentRoll;
	srand(time(0));
	intro();
	ChooseFirstPlayer();

for(int k =1;k<=11; k++){
	CurrentRoll = Roll();	
	piece = SelectPiece();		
	
	if(CurrentRoll == 6){
		CurrentRoll = BaseToBoard(piece);
		if(CurrentRoll = 6){
			CurrentRoll = BaseToBoard(piece);
			if(CurrentRoll == 6){
				CurrentRoll == 0;
			}
		}
	}

	Move(Player,piece,CurrentRoll);
	MakeBlockIfCan();
	CaptureIfCan(Player,piece,CurrentRoll);



	Player++;	
	if(Player > 4){
		Player == 1;
	}
	}
	printf("Won the game !!");
    
    return 0;
}
