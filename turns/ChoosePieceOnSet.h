//
// Created by Celito on 7/8/2015.
//

#ifndef BGCORE_CHOOSEPIECE_H
#define BGCORE_CHOOSEPIECE_H


#include "Action.h"

class BitReference;

class ChoosePieceOnSet : public Action {
public:
    ChoosePieceOnSet(shared_ptr<BitReference> pieces_pool);

    virtual string get_description() const override;

    virtual void update_options() override;

};


#endif //BGCORE_CHOOSEPIECE_H
