//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECE_H
#define BGCORE_PIECE_H

#include <vector>
#include "GameBit.h"

class Player;
class MovementFilterRule;
class TestableRule;

class Piece : public GameBit {
public:
    Piece(BgCore &game, std::string refId);

private:
};


#endif //BGCORE_PIECE_H
