#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

int Player;

void PlayerCol (int i) {
    switch (i){
        case 1 : 
		printf("Red");
		break;
        case 2 : 
		printf("Green");
		break;
        case 3 :
		printf("Yellow");
		break;
        case 4 : 
		printf("Blue");
		break;
    }
}

int Roll () {
	return ((rand() % 6) + 1);
}

void ChooseFirstPlayer () {
    int Maxplayer, Maxroll = 0; 
    for( int i = 1; i <= 4; i++){
        int roll = Roll ();
        PlayerCol(i);
	printf(" rolls %d\n", roll);
        if(Maxroll < roll){
		Maxplayer = i;
		Maxroll = roll;
        }
    }  
    Player = Maxplayer;
    PlayerCol(Maxplayer);
    printf(" player has the highest roll and will begin the game.\n");
    printf("The order of a single round is");
    for( int i = 1; i <= 4; i++){
	    printf(", ");
	    if (Maxplayer > 4){
            	Maxplayer = 1;
       	}
	    PlayerCol/(Maxplayer);
	    Maxplayer++;
    }
    printf(".\n");   
}

void Move (int , int roll) {
	

	if(int x == 1){
		switch (Player){
			case 1:	Piece[y].Red += roll;
				break;
			case 2: Piece[y].Green += roll;
				break;
			case 3: Piece[y].Yellow += roll;
				break;
			case 4: Piece[y].Blue += roll;
				break;
		}
	}else if( Path == 0){
                switch (Player){
                        case 1: Piece[y].Red -= roll;
                                break;
                        case 2: Piece[y].Green -= roll;
                                break;
                        case 3: Piece[y].Yellow -= roll;
                                break;
                        case 4: Piece[y].Blue -= roll;
                                break;
                }
}

int BaseToBoard (int piece) {
	int roll;
		switch (Player){
			case 1 :
		 		if (BasePiece.Red == 4){
					PlayerCol(Player);
					printf(" player moves piece R1 to the starting point\n");
					PlayerCol(Player);
					printf(" player now has 1/4 on pieces on the board and 3/4 pieces on the base.");
					PieceLocation[1].Red = 0;
					BasePiece.Red--;
				}else if(){
						

					//rathu kanawa 	
				}else if(BasePiece.Red == 0){
					Move(Player,piece,6);
				}
				break;
			case 2 :
				if(BasePiece.Green > 0){
					int j = 5 - BasePiece.Green;
					PlayerCol(Player);
					printf(" player moves piece G%d to the starting point\n", j);
					PlayerCol(Player);
					printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", j, BasePiece.Green);
					PieceLocation[j].Green = 13;  
					BasePiece.Green--;
				}else{
					Move(Player,piece,6);
				}
				break;
			case 3:
				if(BasePiece.Yellow > 0){
					int j = 5 - BasePiece.Yellow;
					PlayerCol(Player);
					printf(" player moves piece Y%d to the starting point\n", j);
					PlayerCol(Player);
                               		printf(" player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", j, BasePiece.Yellow);
                              		PieceLocation[j].Yellow = 26; 
					BasePiece.Yellow--;
				}else{
					Move(Player,piece,6);
				}
				break;
			case 4 :
				if(BasePiece.Blue asfkjasdgkkgkkjfbg){

				}	

			// blue scene eka
				else{
					Move(player,piece,6);
				}
				break;
		}
		roll = Roll();
		return roll;
}
int Piecelocation (int player, int piece){
	int location;
	switch (player){
		case 1:
			location = PieceLocation[piece].Red;
			break;
		case 2:
			location = PieceLocation[piece].Green;
			break;
		case 3:
			location = PieceLocation[piece].Yellow;
			break;
		case 4:
			location = PieceLocation[piece].Blue;
			break;
			}
	return location;
}
			

void CaptureIfCan (int player, int piece, int roll) {
	int location = PieceLocation(player, piece);
	int orgplayer = player;
	for( int i = 1; i <= 3; i++){
		player++;
		if(player > 4){
			player == 1;
			}
		for(int j = 1; j <=4; j++){
			int otherlocation = PieceLocation(player, j);
			if(location == other location && block[otherlocation] <= block[location - roll]){
				PlayerCol(orgplayer);
				printf("piece %d lands on square L%d, captures ", piece, location);
				PlayerCol(player);
				printf("piece %d, and return it to the base.", j);
				Reset(player,j);
				break;		
			}
		}
	}
}

void Reset (int player, int piece) {
	
}

int SelectPiece (int player){
	int piece;
	

	return piece;
}

void MakeBlockIfCan () {


}
