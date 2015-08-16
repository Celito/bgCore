//
// Created by Celito on 7/8/2015.
//

#ifndef BGCORE_CHOOSEPIECE_H
#define BGCORE_CHOOSEPIECE_H


#include "ActionDef.h"

class BitReference;

class ChoosePieceOnSet : public ActionDef {
public:
    ChoosePieceOnSet(Game &game, shared_ptr<BitReference> pieces_pool);

    virtual bool is_available(shared_ptr<Player> player);

    virtual string get_description() const override;

    virtual void update_options(Action &action) override;

};


#endif //BGCORE_CHOOSEPIECE_H
