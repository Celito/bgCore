//
// Created by Celito on 2015-05-29.
//

#include "PieceSet.h"

using namespace std;

PieceSet::PieceSet(GameManager *game) : GameBit(game) {
    cout << "Creating a piece set" << endl;
}

void PieceSet::JsonLoad(rapidjson::Value &json) {
    GameBit::JsonLoad(json);

}
