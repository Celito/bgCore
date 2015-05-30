//
// Created by Celito on 2015-05-29.
//

#include <iostream>
#include "Piece.h"

using namespace std;

Piece::Piece(GameManager *game): GameBit(game){

    cout << "creating a Piece" << endl;
}

void Piece::JsonLoad(rapidjson::Value &json) {
    GameBit::JsonLoad(json);
}
