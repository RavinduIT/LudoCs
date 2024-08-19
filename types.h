#ifndef TYPES_H
#define TYPES_H

struct colour {
	int Red;
	int Green;
	int Yellow;
	int Blue;
};

extern struct colour BasePiece;
extern struct colour PieceLocation[4];
extern struct colour BasePiece;
extern struct colour path[4]; 
extern struct colour captured[4];
extern struct colour Home;
extern struct colour BlockPath[4];

extern int block[52];


#endif
