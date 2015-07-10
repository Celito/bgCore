//
// Created by Celito on 2015-07-09.
//

#ifndef BGCORE_MOVEBITTO_H
#define BGCORE_MOVEBITTO_H

#include "Action.h"
#include "../gameBits/boards/Board.h"

class MoveBitTo : public Action {
public:
    MoveBitTo(BitReference target) : _target_ref(target) {}

    virtual void init(shared_ptr<Player> player) override;

    virtual bool is_available() const override;

    virtual string get_description() const override;

private:
    BitReference _target_ref;
    // TODO: Make the move bit to be more generic so it can target any bit holders
    shared_ptr<Board> _target;
};


#endif //BGCORE_MOVEBITTO_H
