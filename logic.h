#ifndef LOGIC_H
#define LOGIC_H

extern int Player;
extern int SixInRow;
extern int bluepiece;

void PlayerCol(int i);
int Roll();
void ChooseFirstPlayer();
void SetValues();
void intro();
int Move(int location, int roll);
void BaseToBoard();
int Piecelocation(int player, int piece);
void Capture(int piece, int roll);
void Reset(int location);
void AI(int roll);
void MakeABlock(int piece, int roll);
void HeadTail(int piece);
int randpiece();
void BreakBlock();
int CanMakeBlock(int roll);
int CanCapture(int roll);
void summary();
void makeBlockX ();
int piecepath (int location);
int enterHomeStraight (int roll);
#endif
