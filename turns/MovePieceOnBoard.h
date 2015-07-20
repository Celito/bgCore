//
// Created by Celito on 7/20/2015.
//

#ifndef BGCORE_MOVEPIECEONBOARD_H
#define BGCORE_MOVEPIECEONBOARD_H

#include "../gameBits/BitReference.h"
#include "Action.h"
#include "../gameBits/boards/Board.h"

class MovePieceOnBoard : public Action {
public:
    MovePieceOnBoard(shared_ptr<BitReference> target_board);
};


#endif //BGCORE_MOVEPIECEONBOARD_H
