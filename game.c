#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main () {
	int Game;
	int piece;
	int CurrentRoll;
	srand(time(0));

	SetValues();  // set values to starting point
	intro();
	ChooseFirstPlayer();

	while(Game){
		CurrentRoll = Roll();			
		AI(CurrentRoll);

		Player++;	
		if(Player > 4){
			Player == 1;
		}
		if(Home.Red == 4 || Home.Green == 4 || Home.Yellow == 4 || Home.Blue == 4){
			Game = 0;
		}
	}
	PlayerCol(Player);
	printf(" Won the game !");
    
    return 0;
}
