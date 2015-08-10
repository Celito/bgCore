//
// Created by Celito on 7/20/2015.
//

#ifndef BGCORE_MOVEPIECEONBOARD_H
#define BGCORE_MOVEPIECEONBOARD_H

#include "../../gameBits/BitReference.h"
#include "ActionDef.h"
#include "../../gameBits/boards/Board.h"
#include "ChoosePieceOnBoard.h"
#include "ChooseTileOnBoard.h"

class MovePieceOnBoard : public ChoosePieceOnBoard {
public:
    MovePieceOnBoard(shared_ptr<BitReference> target_board);

    virtual void update_options(Action &action) override;

    virtual string get_description() const override;

    virtual void choose(Action &action) override;

    virtual bool is_available(shared_ptr<Player> player) override;

private:
    shared_ptr<ChooseTileOnBoard> _choose_tile_on_board;
};


#endif //BGCORE_MOVEPIECEONBOARD_H
