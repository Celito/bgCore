//
// Created by Celito on 7/20/2015.
//

#ifndef BGCORE_MOVEPIECEONBOARD_H
#define BGCORE_MOVEPIECEONBOARD_H

#include "../gameBits/BitReference.h"
#include "Action.h"
#include "../gameBits/boards/Board.h"
#include "ChoosePieceOnBoard.h"

class MovePieceOnBoard : public ChoosePieceOnBoard {
public:
    MovePieceOnBoard(shared_ptr<BitReference> target_board);

    virtual string get_description() const override;
};


#endif //BGCORE_MOVEPIECEONBOARD_H
