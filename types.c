#include <stdio.h>
#include "types.h"

struct colour PieceLocation[4];
struct colour BasePiece;
struct colour path[4];
struct colour captured[4];
struct colour Home[4];
struct colour BlockPath[4];
struct colour HomeStraigh[4];
struct colour GotHome;

int block[52] = {0};
