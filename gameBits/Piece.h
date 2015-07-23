//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECE_H
#define BGCORE_PIECE_H

#include "GameBit.h"
#include "../player/Player.h"
#include "../rules/Rule.h"
#include "../rules/PlayerAttrComparison.h"

class Piece : public GameBit {
public:
    Piece(Game &game, std::string refId);

    bool available_for_movement(shared_ptr<Player> player) const;

    void add_movement_availability_rule(shared_ptr<PlayerAttrComparison> rule){
        _availability_for_movement.push_back(rule);
    }

private:
    vector< shared_ptr<PlayerAttrComparison> > _availability_for_movement;
};


#endif //BGCORE_PIECE_H
