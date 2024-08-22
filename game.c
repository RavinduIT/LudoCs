#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main () {
	int Game = 20;
	int CurrentRoll;
	srand(time(0));

	SetValues();  // set values to starting point
	intro();
	ChooseFirstPlayer();

	while(Game){
		int SixInRow = 0;
		if(Player > 4){
			Player = 1;
		}
		CurrentRoll = Roll();
		PlayerCol(Player);
		printf(" player rolled %d.\n", CurrentRoll);			
		AI(CurrentRoll,SixInRow);

		Player++;
		Game--;	
		if(Home.Red == 4 || Home.Green == 4 || Home.Yellow == 4 || Home.Blue == 4){
			Game = 0;
		}
	}
	PlayerCol(Player);
	printf(" Won the game !");
    
    return 0;
}
