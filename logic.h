#ifndef LOGIC_H
#define LOGIC_H

extern int Player;
extern int SixInRow = 0;

void PlayerCol (int i);
int Roll ();
void ChooseFirstPlayer ();
void SetValues();
void intro();
void Move (int location, int roll);
void BaseToBoard ();
int Piecelocation (int player, int piece);
void Capture (int piece, int roll);
void Reset (int location);
int AI (int roll);
void MakeABlock (int piece, int roll);
void HeadTail (int piece);
int randpiece ();
void BreakBlock ();

#endif
