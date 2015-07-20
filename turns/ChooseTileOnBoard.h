//
// Created by Celito on 2015-07-09.
//

#ifndef BGCORE_MOVEBITTO_H
#define BGCORE_MOVEBITTO_H

#include "Action.h"
#include "../gameBits/boards/Board.h"

class ChooseTileOnBoard : public Action {
public:
    ChooseTileOnBoard(shared_ptr<BitReference> target);

    virtual void update_options() override;

    virtual string get_description() const override;

    shared_ptr<Board> get_board() { return (shared_ptr<Board>)dynamic_pointer_cast<Board>(_required_bits[board]); }
};


#endif //BGCORE_MOVEBITTO_H
