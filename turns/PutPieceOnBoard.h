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
    PutPieceOnBoard(BitReference pieces_pool, BitReference target_board) :
            _pieces_pool_ref(pieces_pool), _target_board_ref(target_board) {}


    virtual void apply_to(shared_ptr<Player> player) override;

    virtual bool is_available() const override;


    virtual string get_description() const override;

private:
    BitReference _pieces_pool_ref;
    BitReference _target_board_ref;
    shared_ptr<PieceSet> _pieces_pool;
    shared_ptr<Board> _target_board;
};


#endif //BGCORE_PUTPIECEONBOARD_H
