//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECESET_H
#define BGCORE_PIECESET_H

#include <c++/iostream>
#include <vector>
#include "GameBit.h"
#include "Piece.h"


class PieceSet : public GameBit {

public:
    PieceSet(GameManager *game, std::string refId);

    virtual void JsonLoad(rapidjson::Value &json) override;

    std::vector<Piece *> Pieces;
};


#endif //BGCORE_PIECESET_H
