//
// Created by Celito on 7/8/2015.
//

#ifndef BGCORE_CHOOSEPIECE_H
#define BGCORE_CHOOSEPIECE_H


#include "Action.h"

class BitReference;

class ChoosePiece : public Action {
public:
    ChoosePiece(BitReference pieces_pool);

    virtual void init(shared_ptr<Player> player) override;

    virtual string get_description() const override;

    virtual bool is_available() const override;

    virtual void choose(shared_ptr<Option> option) override;

private:
    BitReference _pieces_pool_ref;
    shared_ptr<PieceSet> _pieces_pool;
};


#endif //BGCORE_CHOOSEPIECE_H
