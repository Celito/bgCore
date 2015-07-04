//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PUTPIECEONBOARD_H
#define BGCORE_PUTPIECEONBOARD_H


#include "Action.h"

class Board;
class BitReference;

class PutPieceOnBoard : public Action {
public:
    PutPieceOnBoard(BitReference pieces_pool, BitReference target_board) :
            _pieces_pool_ref(pieces_pool), _target_board_ref(target_board) {}


    virtual void init(shared_ptr<Player> player) override;

    virtual bool is_available() const override;

    virtual string get_description() const override;


    virtual void choose(shared_ptr<Option> option) override;

private:
    BitReference _pieces_pool_ref;
    BitReference _target_board_ref;
    shared_ptr<PieceSet> _pieces_pool;
    shared_ptr<Board> _target_board;
};


#endif //BGCORE_PUTPIECEONBOARD_H
