//
// Created by Celito on 2015-05-29.
//

#include "PieceSet.h"
#include "../GameManager.h"
#include "../BitsManager.h"

using namespace std;

PieceSet::PieceSet(GameManager *game, std::string refId) : GameBit(game, refId) {
    cout << "Creating a piece set" << endl;
}

void PieceSet::JsonLoad(rapidjson::Value &json) {
    GameBit::JsonLoad(json);
    if(!json.HasMember("pieces")) { throw "pieces set is missing its pieces on json"; }
    rapidjson::Value &jsonPiecesList = json["pieces"];
    _game->Bits->JsonLoadBitsList<Piece>(jsonPiecesList, &Pieces);

}
