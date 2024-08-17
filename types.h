#ifndef TYPES_H
#define TYPES_H

struct colour {
	int Red;
	int Green;
	int Yellow;
	int Blue;
};

extern struct colour BasePiece;
extern struct colour Piece[4];
extern struct colour path;

#endif
