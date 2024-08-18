#include <stdio.h>
#include "types.h"

struct colour PieceLocation[4];
struct colour BasePiece = {4,4,4,4};
struct colour path[4]; 
struct colour captured[4];
struct colour Home;

int block[52];

