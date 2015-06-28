//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PUTPIECEONBOARD_H
#define BGCORE_PUTPIECEONBOARD_H


#include "Action.h"
#include "../gameBits/PieceSet.h"
#include "../gameBits/boards/Board.h"

class PutPieceOnBoard : public Action {
public:
    PutPieceOnBoard();

    virtual bool is_available() override;

private:
    shared_ptr<PieceSet> _piece_set;
    shared_ptr<Board> _board;
};


#endif //BGCORE_PUTPIECEONBOARD_H
