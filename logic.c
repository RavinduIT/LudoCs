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
	Player = Maxplayer;
    printf(".\n");   
}

void Move (int location, int roll) {
	int movepossible;
	if(movepossible == 1){
		
	}else{

		return;
	}

}

void BaseToBoard () {
		switch (Player){
			case 1 :
					int PiecesBoard = 4 - BasePiece.Red;
					for(int i = 1; i <= 4; i++){
						if(Location(1,i) == -1){
							printf("Red player moves piece R%d to the starting point\n", i);
							printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.",PiecesBoard, BasePiece.Red);
							PieceLocation[i].Red = 26;
							BasePiece.Red--;
							HeadTail(i);
							break;						
						}
					}
			case 2 :
					int PiecesBoard = 4 - BasePiece.Green;
					for(int i = 1; i <= 4; i++){
						if(Location(1,i) == -1){
							printf("Green player moves piece G%d to the starting point\n", i);
							printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.",PiecesBoard, BasePiece.Green);
							PieceLocation[i].Green = 39;
							BasePiece.Green--;
							HeadTail(i);
							break;						
						}
					}
			case 3:
					int PiecesBoard = 4 - BasePiece.Yellow;
					for(int i = 1; i <= 4; i++){
						if(Location(1,i) == -1){
							printf("Yellow player moves piece Y%d to the starting point\n", i);
							printf("Yellow player now has %d/4 on pieces on the board and %d/4 pieces on the base.",PiecesBoard, BasePiece.Yellow);
							PieceLocation[i].Yellow = 0;
							BasePiece.Yellow--;
							HeadTail(i);
							break;						
						}
					}
			case 4 :
					int PiecesBoard = 4 - BasePiece.Blue;
					for(int i = 1; i <= 4; i++){
						if(Location(1,i) == -1){
							printf("Blue player moves piece B%d to the starting point\n", i);
							printf("Blue player now has %d/4 on pieces on the board and %d/4 pieces on the base.",PiecesBoard, BasePiece.Blue);
							PieceLocation[i].Blue = 13;
							BasePiece.Blue--;
							HeadTail(i);
							break;						
						}
					}
		}
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
			
void Capture (int piece, int roll) {


	int Basepiece;
	int location = Piecelocation(Player, piece);
	int newlocation = location + roll;
	
	switch (Player){
				case 1:
					printf("Red piece ");
					for(int p = 1; p <= 4; p++){
					if(PieceLocation[p].Red == location){
								printf("R%d, ", p);
								captured[p].Red++;
							}
						}
						printf("lands on square L%d, captures ", newlocation);
						break;

					case 2:
						printf("Green piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Green == newlocation){
								printf("G%d, ", p);
								captured[p].Green++;
							}
						}
						printf("lands on square L%d, captures ", newlocation);
						break;

					case 3:
						printf("Yellow piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Yellow == newlocation){
								printf("Y%d, ", p);
								captured[p].Yellow++;
							}
						}
						printf("lands on square L%d, captures ", location);
						break;

					case 4: 
						printf("piece ");
						for(int p = 1; p <= 4; p++){
						if(PieceLocation[p].Blue == newlocation){
								printf("B%d, ", p);
								captured[p].Blue++;
							}
						}
						printf("lands on square L%d, captures ", newlocation);
						break;
				}
	int capplayer; 
	for(capplayer = 1; capplayer <= 4; capplayer++){
		if(newlocation == Piecelocation(capplayer,1) || newlocation == Piecelocation(capplayer,2) || newlocation == Piecelocation(capplayer,3) || newlocation == Piecelocation(capplayer,4)){
			PlayerCol(capplayer);
			for(int cappiece = 1; cappiece <= 4; cappiece++){
				if( Piecelocation(capplayer, cappiece) == newlocation && capplayer != Player){
				switch (capplayer){
					case 1:
						printf("R%d", cappiece);
						break;
					case 2:
						printf("G%d, ", cappiece);
						break;
					case 3:
						printf("Y%d, ", cappiece);
						break;
					case 4:
						printf("B%d, ", cappiece);
						break;
					}
				}
			}
	}
				printf("Return it to the base.\n");			
				Reset(newlocation);
				Move(location, roll);
				PlayerCol(capplayer);
				switch (capplayer){
					case 1:
						BasePiece.Red = Basepiece;
						break;
					case 2:
						BasePiece.Green = Basepiece;
						break;
					case 3:
						BasePiece.Yellow = Basepiece;
						break;
					case 4:
						BasePiece.Blue = Basepiece;
						break;
					} 
			}
				printf("player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - Basepiece), Basepiece);	
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
			if(minval != 54){                                                      // Red capture if can
				Capture(choosepiece,roll);
				if(roll == 6){
					SixInRow++;
				}
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d", roll);
				AI(roll);
			}

			if( roll == 6 && SixInRow <= 2 && BasePiece.Red > 0 )  {                    // Red move a piece base to board
				BaseToBoard();
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d", roll);
				SixInRow++;
				AI(roll);
			}

			for(int y = 1; y <= 4; y++){
				for(int z = 1; z <= 4; z++){
					if(PieceLocation[z].Red != (PieceLocation[y].Red + roll) && y != z){     // Move Red piece but avoid making block 
						Move(y,roll);
						PossibleMove++;
						if(roll == 6){
							SixInRow++;
						}
					}
				}
			}
			if(PossibleMove == 0){
				MakeABlock(randpiece(),roll);                           // if we cant move any Red piece then make a block
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

void MakeABlock (int piece, int roll) {
	
	int currentlocation = Piecelocation(Player , piece);
	int oldblock = block[currentlocation];
	block[currentlocation] = 0;
	block[currentlocation + roll] += oldblock;
	Move(currentlocation, roll);
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
