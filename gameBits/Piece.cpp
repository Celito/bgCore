//
// Created by Celito on 2015-05-29.
//

#include <iostream>
#include "Piece.h"

using namespace std;

Piece::Piece(Game *game, std::string refId) : GameBit(game, refId){
    cout << "creating a piece" << endl;
}

void Piece::JsonLoad(rapidjson::Value &json) {
    GameBit::JsonLoad(json);
}
