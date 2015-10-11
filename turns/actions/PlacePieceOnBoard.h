//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PUTPIECEONBOARD_H
#define BGCORE_PUTPIECEONBOARD_H


#include "ActionDef.h"
#include "ChoosePieceOnSet.h"

class Board;
class BitReference;
class ChooseTileOnBoard;

class PlacePieceOnBoard : public ChoosePieceOnSet {
public:
    PlacePieceOnBoard(BgCore &game, shared_ptr<BitReference> pieces_pool, shared_ptr<BitReference> target_board);

    virtual string get_description() const override;

    virtual void process_choice(shared_ptr<Action> action) override;

private:
    shared_ptr<ChooseTileOnBoard> _choose_tile_on_board;
};


#endif //BGCORE_PUTPIECEONBOARD_H
