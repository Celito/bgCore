//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PUTPIECEONBOARD_H
#define BGCORE_PUTPIECEONBOARD_H


#include "Action.h"

class Board;
class BitReference;
class ChoosePieceOnSet;
class ChooseTileOnBoard;

class PutPieceOnBoard : public Action {
public:
    PutPieceOnBoard(shared_ptr<BitReference> pieces_pool, shared_ptr<BitReference> target_board);

    virtual void init(shared_ptr<Player> player) override;

    virtual bool is_available() const override;

    virtual string get_description() const override;

    virtual bool self_resolve() override;

    virtual void update_options() override;

private:
    shared_ptr<ChoosePieceOnSet> _choose_piece_action;
    shared_ptr<GameBit> _selected_bit;
    shared_ptr<ChooseTileOnBoard> _choose_tile_on_board;
};


#endif //BGCORE_PUTPIECEONBOARD_H
