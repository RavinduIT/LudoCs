#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main () {
	int piece;
	int CurrentRoll;
	srand(time(0));

	SetValues();  // set values to starting point
	intro();
	ChooseFirstPlayer();

	while(Player){
		CurrentRoll = Roll();			
		AI(CurrentRoll);

		Player++;	
		if(Player > 4){
			Player == 1;
		}
	}
	printf("Won the game !");
    
    return 0;
}
