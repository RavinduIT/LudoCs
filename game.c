#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"
#include "types.h"

int main()
{
	int Game = 1, round = 1;
	srand(time(0));
	SetValues();										 // set values to starting point
	intro();
	ChooseFirstPlayer();								// choose first player
	printf("\n");
	int startPlayer = Player;
	while (Game) {
		if(startPlayer == Player) {
			printf("\n\t----Round %d---- \n", round);    // printf the round
			round++;
		}
		SixInRow = 0;									
		if (Player > 4) Player = 1;
		int CurrentRoll = Roll();                       // roll the dice
		PlayerCol(Player);
		printf(" player rolled %d.\n", CurrentRoll);
		AI(CurrentRoll);   								// player AI work according to the rolled dice

		Player++;
		if (startPlayer == Player) {
			printf("\n");
			summary();                                  // get a summary end of the round
	}
		if (GotHome.Red == 4 || GotHome.Green == 4 || GotHome.Yellow == 4 || GotHome.Blue == 4)   // check if theres any player who has reached home. if yes end loop
		{
			Game = 0;
		}
	}
		PlayerCol(Player - 1);
		printf(" Won the game !\n");
	return 0;
}
