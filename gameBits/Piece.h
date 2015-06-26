//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECE_H
#define BGCORE_PIECE_H

#include "GameBit.h"

class Piece : public GameBit {
public:
    Piece(Game &game, std::string refId);
};


#endif //BGCORE_PIECE_H
