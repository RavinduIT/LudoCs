#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "logic.h"

int Player;

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

int Move (int location, int roll) {
	int move = roll / block[location];
	int havetojump = move;


	for(int otherblock = (location + 1); otherblock >= (location + move); otherblock++){
		if(block[otherblock] > block[location]){
			if(move >= abs(otherblock - location)){
				PlayerCol(Player);
				move = abs(otherblock - location) - 1;
			}

			if(block[location] > 1){                              // block move if there's a block infront of it
				PlayerCol(Player);
				printf(" pieces ");
				for(int locpiece = 1; locpiece <= 4; locpiece++){
				switch (Player){						
					case 1:
						if(PieceLocation[locpiece].Red == location) {
							if(BlockPath[locpiece].Red == 0){
								PieceLocation[locpiece].Red += move;
								block[location]--;
								block[location + move]++;
								printf("R%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Red -= move;
								block[location]--;
								block[location - move]++;
								printf("R%d, ", locpiece);
								}	
							}
							break;
					case 2:
						if(PieceLocation[locpiece].Green == location) {
							if(BlockPath[locpiece].Green == 0){
								PieceLocation[locpiece].Green += move;
								block[location]--;
								block[location + move]++;
								printf("G%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Green -= move;
								block[location]--;
								block[location - move]++;
								printf("G%d, ", locpiece);
								}	
							}
							break;
					case 3:
						if(PieceLocation[locpiece].Yellow == location) {
							if(BlockPath[locpiece].Yellow == 0){
								PieceLocation[locpiece].Yellow += move;
								block[location]--;
								block[location + move]++;
								printf("Y%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Yellow -= move;
								block[location]--;
								block[location - move]++;
								printf("Y%d, ", locpiece);
								}	
							}
							break;
					case 4:
						if(PieceLocation[locpiece].Blue == location) {
							if(BlockPath[locpiece].Blue == 0){
								PieceLocation[locpiece].Blue += move;
								block[location]--;
								block[location + move]++;
								printf("B%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Blue -= move;
								block[location]--;
								block[location - move]++;
								printf("B%d, ", locpiece);
								}	
							}
							break;
						}
					}
					printf("is blocked from moving from L%d to L%d by ", location, havetojump);
					int blockedbyplayer;
					int blockedbypiece;
					for(int blockplayer; blockplayer <= 4; blockplayer++){
					for(int blockedpiece = 1; blockedpiece <= 4;blockedpiece++ ){
						if(Piecelocation(blockedbyplayer,blockedbypiece) == otherblock){
									blockedbyplayer = blockplayer;
									blockedbypiece = blockedpiece;
							}
						}
					}
				PlayerCol(blockedbyplayer);
				printf("%d\n", blockedbypiece);
				return 10;
			}

			if(block[location] == 1){ 
				PlayerCol(Player);
				printf(" piece ");
				for(int movepiece; movepiece <= 4; movepiece++){
					switch (Player){
						case 1:
							if(PieceLocation[movepiece].Red == location) {
								if(path[movepiece].Red == 0){
									PieceLocation[movepiece].Red += move;
									block[location] = 0;
									block[location + move]++;
									printf("R%d ", movepiece);
									}else{
									PieceLocation[movepiece].Red -= move;
									block[location] = 0;
									block[location - move]++;
									printf("R%d ", movepiece);
									}	
								}
								break;
						case 2:
							if(PieceLocation[movepiece].Green == location) {
								if(path[movepiece].Green == 0){
									PieceLocation[movepiece].Green += move;
									block[location] = 0;
									block[location + move]++;
									printf("G%d ", movepiece);
									}else{
									PieceLocation[movepiece].Green -= move;
									block[location] = 0;
									block[location - move]++;
									printf("G%d ", movepiece);
									}	
								}
								break;
						case 3:
							if(PieceLocation[movepiece].Yellow == location) {
								if(path[movepiece].Yellow == 0){
									PieceLocation[movepiece].Yellow += move;
									block[location] = 0;
									block[location + move]++;
									printf("Y%d ", movepiece);
									}else{
									PieceLocation[movepiece].Yellow -= move;
									block[location] = 0;
									block[location - move]++;
									printf("Y%d ", movepiece);
									}	
								}
								break;
						case 4:
							if(PieceLocation[movepiece].Blue == location) {
								if(path[movepiece].Blue == 0){
									PieceLocation[movepiece].Blue += move;
									block[location] = 0;
									block[location + move]++;
									printf("B%d ", movepiece);
									}else{
									PieceLocation[movepiece].Blue -= move;
									block[location] = 0;
									block[location - move]++;
									printf("B%d ", movepiece);
									}	
							}
							break;
						}
					}
				printf("is blocked from moving from L%d to L%d by ", location, havetojump);
				int blockedbyplayer;
				int blockedbypiece;
				for(int blockplayer; blockplayer <= 4; blockplayer++){
					for(int blockedpiece = 1; blockedpiece <= 4;blockedpiece++ ){
						if(Piecelocation(blockedbyplayer,blockedbypiece) == otherblock){
									blockedbyplayer = blockplayer;
									blockedbypiece = blockedpiece;
							}
						}
					}
				PlayerCol(blockedbyplayer);
				printf("%d\n", blockedbypiece);

			}

			if(abs(otherblock - location) == 0){
				PlayerCol(Player);
				printf(" does not have other pieces in the board to move instead of the blocked piece.Ignoring the throw and moving on to the next player.\n");
			}
			if( otherblock > location){
			printf("does not have other pieces in the board to move instead of the blocked piece.Moved the piece to square L%d which is the cell before the block.\n", (otherblock - 1));
			}		
			else if( otherblock < location){
				printf("does not have other pieces in the board to move instead of the blocked piece.Moved the piece to square L%d which is the cell before the block.\n", (otherblock + 1));
			}
		}
		else if (block[otherblock] <= block[location]){
			int newpiecelocation;
			PlayerCol(Player);
			printf(" moves piece ");
			if(block[location] == 1){                                                      // piece move without any block in front of it
			for(int locationpiece = 1;locationpiece <= 4; locationpiece++){
				switch(Player) {
					case 1:
						if(PieceLocation[locationpiece].Red == location) {
							if(path[locationpiece].Red == 0){
								PieceLocation[locationpiece].Red += move;
								block[location] = 0;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("R%d ", locationpiece);
								}else{
								PieceLocation[locationpiece].Red -= move;
								block[location] = 0;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("R%d ", locationpiece);
							}	
						}
						break;
					case 2:
						if(PieceLocation[locationpiece].Green == location) {
							if(path[locationpiece].Green == 0){
								PieceLocation[locationpiece].Green += move;
								block[location] = 0;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("G%d ", locationpiece);
								}else{
								PieceLocation[locationpiece].Green -= move;
								block[location] = 0;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("G%d ", locationpiece);
							}	
						}
						break;
					case 3:
						if(PieceLocation[locationpiece].Yellow == location) {
							if(path[locationpiece].Yellow == 0){
								PieceLocation[locationpiece].Yellow += move;
								block[location] = 0;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("Y%d ", locationpiece);
								}else{
								PieceLocation[locationpiece].Yellow -= move;
								block[location] = 0;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("Y%d ", locationpiece);
							}	
						}
						break;
					case 4:
						if(PieceLocation[locationpiece].Blue == location) {
							if(path[locationpiece].Blue == 0){
								PieceLocation[locationpiece].Blue += move;
								block[location] = 0;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("B%d ", locationpiece);
								}else{
								PieceLocation[locationpiece].Blue -= move;
								block[location] = 0;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("B%d ", locationpiece);
							}	
						}
						break;
					}
				}
				printf("from location L%d to L%d by %d units in ", location, newpiecelocation, move);
				if(location > newpiecelocation){
					printf("counter-clockwise direction.\n");
				}
				else if(location < newpiecelocation){
					printf("clockwise direction.\n");
				}
			}
			else if(block[location] > 1){                                                  // block move if there's no any block infront of it
				for(int locpiece = 1; locpiece <= 4; locpiece++){
					switch (Player){						
						case 1:
						if(PieceLocation[locpiece].Red == location) {
							if(path[locpiece].Red == 0){
								PieceLocation[locpiece].Red += move;
								block[location]--;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("R%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Red -= move;
								block[location]--;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("R%d, ", locpiece);
								}	
							}
							break;
						case 2:
						if(PieceLocation[locpiece].Green == location) {
							if(path[locpiece].Green == 0){
								PieceLocation[locpiece].Green += move;
								block[location]--;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("G%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Green -= move;
								block[location]--;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("G%d, ", locpiece);
								}	
							}
							break;
						case 3:
						if(PieceLocation[locpiece].Yellow == location) {
							if(path[locpiece].Yellow == 0){
								PieceLocation[locpiece].Yellow += move;
								block[location]--;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("Y%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Yellow -= move;
								block[location]--;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("Y%d, ", locpiece);
								}	
							}
							break;
						case 4:
						if(PieceLocation[locpiece].Blue == location) {
							if(path[locpiece].Blue == 0){
								PieceLocation[locpiece].Blue += move;
								block[location]--;
								block[location + move]++;
								newpiecelocation = location + move;
								printf("B%d, ", locpiece);
								}else{
								PieceLocation[locpiece].Blue -= move;
								block[location]--;
								block[location - move]++;
								newpiecelocation = location - move;
								printf("B%d, ", locpiece);
								}	
							}
						break;
					}
				}
				printf(" from location L%d to L%d by %d units in ",location , newpiecelocation, move);
				if(newpiecelocation > location){
					printf("clockwise direction\n");
				}else if(newpiecelocation < location){
					printf("counter-clockwise direction\n");
				}
			}
		}
	}
}

void BaseToBoard () {
		switch (Player){
			case 1 :
					for(int i = 1; i <= 4; i++){
						if(Piecelocation(1,i) == -1){
							BasePiece.Red--;
							printf("Red player moves piece R%d to the starting point.\n", i);
							printf("Red player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n",(4 - BasePiece.Red), BasePiece.Red);
							PieceLocation[i].Red = 26;
							HeadTail(i);
							break;
						}
					}
					break;						
			case 2 :
					for(int i = 1; i <= 4; i++){
						if(Piecelocation(1,i) == -1){
							BasePiece.Green--;
							printf("Green player moves piece G%d to the starting point.\n", i);
							printf("Green player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Green), BasePiece.Green);
							PieceLocation[i].Green = 39;
							HeadTail(i);
							break;
						}
					}
					break;						
			case 3:
					for(int i = 1; i <= 4; i++){
						if(Piecelocation(1,i) == -1){
							BasePiece.Yellow--;
							printf("Yellow player moves piece Y%d to the starting point.\n", i);
							printf("Yellow player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n", (4 - BasePiece.Yellow), BasePiece.Yellow);
							PieceLocation[i].Yellow = 0;
							HeadTail(i);
							break;
						}
					}
					break;						
			case 4 :
					for(int i = 1; i <= 4; i++){
						if(Piecelocation(1,i) == -1){
							BasePiece.Blue--;
							printf("Blue player moves piece B%d to the starting point.\n", i);
							printf("Blue player now has %d/4 on pieces on the board and %d/4 pieces on the base.\n",(4 - BasePiece.Blue), BasePiece.Blue);
							PieceLocation[i].Blue = 13;
							HeadTail(i);
							break;
						}
					}
					break;						

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

void AI (int roll, int SixInRow){

	if(SixInRow > 2){
		PlayerCol(Player);
		printf(" six rolled for the third consecutive time, the roll is ignored.\n");
		BreakBlock();
		return;
	}
		int PossibleMove = 0;
		int cancapture[4] = {55,55,55,55};
		int minval = 54;
		int choosepiece;
	switch (Player){
	
		case 1:
			
			for(int c = 1; c <= 4; c++){
				int location = (PieceLocation[c].Red + roll);
				for(int d = 1; d <= 4; d++){
					if((location == PieceLocation[d].Green || location == PieceLocation[d].Yellow || location == PieceLocation[d].Blue) && (block[location - roll] >= block[location])){
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
					minval = cancapture[x];
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
				AI(roll,SixInRow);
			}

			if( roll == 6 && SixInRow <= 2 && BasePiece.Red > 0 )  {                    // Red move a piece base to board
				BaseToBoard();
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d", roll);
				SixInRow++;
				AI(roll,SixInRow);
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
			int block_piece = CanMakeBlock(roll);
			if(roll == 6 && block_piece > 1){
				MakeABlock(block_piece,roll);
				SixInRow++;
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d", roll);
				AI(roll,SixInRow);
			}else if(roll == 6 && BasePiece.Green > 1){
				BaseToBoard();
				SixInRow++;
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d", roll);
				AI(roll,SixInRow);
			}else{
				int randompiece, randompiecelocation, piecehavetomove, isitblocked;
				for(int loop = 1; loop <= 4; loop++){
				randompiece = randpiece();
				randompiecelocation = PieceLocation[randompiece].Green;
				if(block[randompiecelocation] == 1 ){
					piecehavetomove;
				}
				isitblocked = Move(PieceLocation[piecehavetomove].Green,roll);
				if(isitblocked == 10){
					BreakBlock();
				}
				if(roll == 6){
					SixInRow++;
					roll = Roll();
					PlayerCol(Player);
					printf(" player rolled %d", roll);
					AI(roll,SixInRow);
					}
				}
			}
			break;
		case 3:
			if(roll == 6 && BasePiece.Yellow > 0 ){
				BaseToBoard();
				SixInRow++;
				roll = Roll();
				PlayerCol(Player);
				printf(" player rolled %d", roll);
				AI(roll,SixInRow);
			}
			break;

		case 4:


			break;
		
		
		

	}
	
}

void MakeABlock (int piece, int roll) {
	
	int currentlocation = Piecelocation(Player , piece);
	int oldblock = block[currentlocation];
	int newpiecepath;
	int oldpiecepath;
	int blockpath;

	block[currentlocation] = 0;
	block[currentlocation + roll] += oldblock;
	for(int newpiece = 1; newpiece <= 4; newpiece++){
		switch (Player){
			case 1:
				if(PieceLocation[newpiece].Red == (currentlocation + roll)){
					newpiecepath = path[newpiece].Red;
				} 
				oldpiecepath = path[piece].Red;
				break;
			case 2:
				if(PieceLocation[newpiece].Green == (currentlocation + roll)){
					newpiecepath = path[newpiece].Green;
				}                                                                            //  to get new location piece path
				oldpiecepath = path[piece].Green;
				break;
			case 3:
				if(PieceLocation[newpiece].Yellow == (currentlocation + roll)){
					newpiecepath = path[newpiece].Yellow;
				} 
				oldpiecepath = path[piece].Yellow;
				break;
			case 4:
				if(PieceLocation[newpiece].Blue == (currentlocation + roll)){
					newpiecepath = path[newpiece].Blue;
				} 
				oldpiecepath = path[piece].Blue;
				break;
		}
	}

	if( newpiecepath != oldpiecepath){
		int hometooldpiece, hometonewpiece;
		if(oldpiecepath == 0){
			hometooldpiece = 50 - currentlocation + roll;                                 // to get path of the block 
			hometonewpiece = currentlocation + roll + 2;
			if(hometooldpiece > hometonewpiece){
				blockpath = oldpiecepath;
			}else{
				blockpath = newpiecepath;
			}	
		}
	}else {
		switch (Player) {
			case 1:
				blockpath = path[piece].Red;
				break;
			case 2:
				blockpath = path[piece].Green;
				break;
			case 3:
				blockpath = path[piece].Yellow;
				break;
			case 4:
				blockpath = path[piece].Blue;
				break;
		}
	}


	switch(Player){
		case 1:
			BlockPath[piece].Red = blockpath;
			break;
		case 2:
			BlockPath[piece].Green = blockpath;
			break;
		case 3:                                                            // store the data of block path
			BlockPath[piece].Yellow = blockpath;
			break;
		case 4:
			BlockPath[piece].Blue = blockpath;
			break;
			}

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

void BreakBlock (){

	for(int blockpiece1 = 1; blockpiece1 <= 4; blockpiece1++){
		for(int blockpiece2 = 1; blockpiece2 <= 4; blockpiece2++){
			switch (Player){
				case 1:
					if(PieceLocation[blockpiece1].Red == PieceLocation[blockpiece2].Red && blockpiece1 != blockpiece2){
						int breakblocklocation = PieceLocation[blockpiece1].Red;
						block[breakblocklocation] = 1;
					}
					break;
				case 2:
					if(PieceLocation[blockpiece1].Green == PieceLocation[blockpiece2].Green && blockpiece1 != blockpiece2){
						int breakblocklocation = PieceLocation[blockpiece1].Green;
						block[breakblocklocation] = 1;
					}
					break;
				case 3:
					if(PieceLocation[blockpiece1].Yellow == PieceLocation[blockpiece2].Yellow && blockpiece1 != blockpiece2){
						int breakblocklocation = PieceLocation[blockpiece1].Yellow;
						block[breakblocklocation] = 1;
					}
					break;
				case 4:
					if(PieceLocation[blockpiece1].Blue == PieceLocation[blockpiece2].Blue && blockpiece1 != blockpiece2){
						int breakblocklocation = PieceLocation[blockpiece1].Blue;
						block[breakblocklocation] = 1;
					}
					break;
			}
		}
	}
	PlayerCol(Player);
	printf(" Break the block.");
}	

int CanMakeBlock (int roll){
	int block_piece = 0;
	for(int canmakepiece = 1; canmakepiece <= 4; canmakepiece++){
		for(int otherpiece = 1; otherpiece <= 4; otherpiece ++){
			switch (Player) {
				case 1:
					if((PieceLocation[canmakepiece].Red + roll) == PieceLocation[otherpiece].Red && canmakepiece != otherpiece){
						block_piece = canmakepiece;
					}
			}
		}
	}
	return block_piece;
}