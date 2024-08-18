#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

int Player;
int SixInRow = 0;

void SetValues (){

	for(int a = 1; a <= 4; a++){
		PieceLocation[a].Red = -1;
		PieceLocation[a].Green = -1;
		PieceLocation[a].Yellow = -1;
		PieceLocation[a].Blue = -1;
	}
}

void intro () {
    printf("The red player has four (04) pieces named R1, R2, R3, and R4.\n");
    printf("The green player has four (04) pieces named G1, G2, G3, and G4.\n");
    printf("The yellow player has four (04) pieces named Y1, Y2, Y3, and Y4\n");
    printf("The blue player has four (04) pieces named B1, B2, B3, and B4\n");
}

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
	    PlayerCol(Maxplayer);
	    Maxplayer++;
    }
    printf(".\n");   
}

void Move (int roll) {
	

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

		}	// block ekak unath move kranna
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
					HeadTail(1,1);
				}else if(  > 0 ){
						

					//rathu kanawa 	
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
					HeadTail(2,j);
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
				}
				break;
			case 4 :
				if(BasePiece.Blue asfkjasdgkkgkkjfbg){

				}	

			// blue scene eka
				
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
	int roll2 = roll;
	int Basepiece;
	int location = PieceLocation(player, piece);
	int orgplayer = player;
	for( int i = 1; i <= 3; i++){
		player++;
		if(player > 4){
			player == 1;
			}
		for(int j = 1; j <=4; j++){
			int newlocation = PieceLocation(player, j);
			if((location + roll) == newlocation && block[newlocation] <= block[location]){
				PlayerCol(orgplayer);
				switch (orgplayer){
					case 1:
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Red == location){
								printf("R%d, ", p);
							}
						printf("lands on square L%d, captures ", location);
						}
						break;
					case 2:
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Green == newlocation){
								printf("G%d, ", p);
							}
						printf("lands on square L%d, captures ", location);
						}
						break;
					case 3:
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Yellow == newlocation){
								printf("Y%d, ", p);
							}
						printf("lands on square L%d, captures ", location);
						}
						break;
					case 4: 
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Blue == newlocation){
								printf("B%d, ", p);
							}
						printf("lands on square L%d, captures ", location);
						}
						break;
		
				}
				PlayerCol(player);
				switch (player){
					case 1:
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Red == newlocation){
								printf("R%d, ", p);
							}
						}
						break;
					case 2:
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Green == newlocation){
								printf("G%d, ", p);
							}
						}
						break;
					case 3:
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Yellow == newlocation){
								printf("Y%d, ", p);
							}
						}
						break;
					case 4:
						printf("piece");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Blue == newlocation){
								printf("B%d, ", p);
							}
						}
						break;
				}
				printf("Return it to the base.\n", newlocation);			
				Reset(newlocation);
				Move(orgplayer,piece,roll);
				PlayerCol(player);
				switch (player){
					case 1:
						BasePiece.Red = Basepiece;
						break;
					case 2:
						BasePiece.Green = Basepiece;
						break;
					case 3:
						Basepiece.Yellow = Basepiece;
						break;
					case 4:
						Basepiece.Blue = Basepiece;
						break;
					} 
				}
				printf("player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - Basepiece), Basepiece);
				roll2 = Roll();
				return roll2;		
			}
		}
	}
}

void Reset (int location) {
	
	for(int r = 0; r <= 4; r++){
		switch (r){
			case 1:
				for(int s = 1; s <= 4; s++){
					if(PieceLocation[s].Red == location){
						PieceLocation[s].Red = -1;
						captured[s].Red = 0;
						BasePiece.Red++;
					}
					break;
				}
			case 2:
				for(int s = 1; s <= 4; s++){
					if(PieceLocation[s].Green == location){
						PieceLocation[s].Green = -1;
						captured[s].Green = 0;
						BasePiece.Green++;
					}
					break;
				}
			case 3:
				for(int s = 1; s <= 4; s++){
					if(PieceLocation[s].Yellow == location){
						PieceLocation[s].Yellow = -1;
						captured[s].Yellow = 0;
						BasePiece.Yellow++;
					}
					break;
				}
			case 4:
				for(int s = 1; s <= 4; s++){
					if(PieceLocation[s].Blue == location){
						PieceLocation[s].Blue = -1;
						captured[s].Blue = 0;
						BasePiece.Blue++;
					}
					break;
				}
		}
	}


}

int AI (int roll){

	if(SixInRow > 2){
		return;
	}

	switch (Player){
		case 1:
			int PossibleMove = 0;
			int cancapture[4] = {55,55,55,55};
			int minval = 54;
			int choosepiece;
			
			for(int c = 1; c <= 4; c++){
				int location = (PieceLocation[c].Red + roll);
				for(int d = 1; d <= 4; d++){
					if(location == PieceLocation[d].Green || location == PieceLocation[d].Yellow || location == PieceLocation[d].Blue && (block[location - roll] >= block[location])){
						if(path[c].Red == 0){
							cancapture[c - 1] = (50 - location); 
						}else if(path[c].Red == 1){
							cancapture[c - 1] = location + 2; 
						}		
					}
				}
			}

			for(int x = 0; x <= 3; x++){
				if(cancapture[x] < minval){
					minval == cancapture[x];
					choosepiece = (x + 1);
				}
			}
			if(minval != 54){
				Capture(choosepiece);
				if(roll == 6){
					SixInRow++;
				}
				roll = Roll();
				AI(roll);
			}

			if( roll == 6 && SixInRow <= 2 && BasePiece.Red > 0 )  {
				BaseToBoard();
				roll = Roll();
				SixInRow++;
				AI(roll);
			}

			for(int y = 1; y <= 4; y++){
				for(int z = 1; z <= 4; z++){
					if(PieceLocation[z] != (PieceLocation[y] + roll) && y != z){
						Move(y);
						PossibleMove++;
						if(roll == 6){
							SixInRow++;
						}
					}
				}
			}
			if(PossibleMove == 0){
				MakeABlock(randpiece());
			}
			SixInRow = 0;
			break;

		case 2:


			break;
		
		case 3:


			break;

		case 4:


			break;
		
		
		

	}
	
}

void MakeABlock (int piece) {
	


}

void HeadTail (int piece){

	int headtail = (( rand() % 2 ));  //  0 = clockwise  1 = counterwise
	switch (Player){
		case 1:
			path[piece].Red = headtail;
			break;
		case 2:
			path[piece].Green = headtail;
			break;
		case 3:
			path[piece].Yellow = headtail;
			break;
		case 4:
			path[piece].Blue = headtail;
			break;
	}
}

int randpiece (){
	return (rand() % 4 ) + 1;
}
