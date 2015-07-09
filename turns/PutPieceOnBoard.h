//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PUTPIECEONBOARD_H
#define BGCORE_PUTPIECEONBOARD_H


#include "Action.h"

class Board;
class BitReference;
class ChoosePiece;

class PutPieceOnBoard : public Action {
public:
    PutPieceOnBoard(BitReference pieces_pool, BitReference target_board);

    virtual void init(shared_ptr<Player> player) override;

    virtual bool is_available() const override;

    virtual string get_description() const override;

    virtual bool self_resolve() override;

private:
    BitReference _target_board_ref;
    shared_ptr<ChoosePiece> _choose_piece_action;
    shared_ptr<Board> _target_board;
    shared_ptr<GameBit> _selected_bit;
};


#endif //BGCORE_PUTPIECEONBOARD_H
