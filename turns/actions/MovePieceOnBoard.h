//
// Created by Celito on 7/20/2015.
//

#ifndef BGCORE_MOVEPIECEONBOARD_H
#define BGCORE_MOVEPIECEONBOARD_H

#include "../../gameBits/BitReference.h"
#include "ActionDef.h"
#include "ChoosePieceOnBoard.h"

class ChooseTileOnBoard;

class MovePieceOnBoard : public ChoosePieceOnBoard {
public:
    MovePieceOnBoard(BgCore &game, shared_ptr<BitReference> target_board);

    virtual void update_options(Action &action) override;

    virtual string get_description() const override;

    virtual void choose(shared_ptr<Action> action) override;

    virtual bool is_available(shared_ptr<Player> player) override;


    virtual void init_by_option(shared_ptr<Action> action, shared_ptr<Option> selected_option) override;

private:
    shared_ptr<ChooseTileOnBoard> _choose_tile_on_board;
};


#endif //BGCORE_MOVEPIECEONBOARD_H
