//
// Created by Celito on 9/21/2015.
//

#ifndef BGCORE_ONBITPLACEDAT_H
#define BGCORE_ONBITPLACEDAT_H

#include <memory>
#include "CustomEvent.h"

using namespace std;

class GameBit;

class OnBitPlacedAt : public CustomEvent {
public:
    OnBitPlacedAt(shared_ptr<GameBit> tracked_bit, shared_ptr<GameBit> target_parent);

private:
    weak_ptr<GameBit> _tracked_bit;
    weak_ptr<GameBit> _target_parent;

    void on_tracked_bit_change_parent(GameBit const& bit);
};


#endif //BGCORE_ONBITPLACEDAT_H
