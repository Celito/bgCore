//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_PIECESET_H
#define BGCORE_PIECESET_H

#include <c++/iostream>
#include "GameBit.h"


class PieceSet : public GameBit {

public:
    PieceSet(GameManager *game);

    virtual void JsonLoad(rapidjson::Value &json) override;
};


#endif //BGCORE_PIECESET_H
