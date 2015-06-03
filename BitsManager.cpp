//
// Created by Celito on 2015-05-29.
//

#include <map>
#include "BitsManager.h"
#include "gameBits/PieceSet.h"
#include "gameBits/boards/HexBoard.h"

using namespace rapidjson;
using namespace std;

BitsManager::BitsManager(GameManager *manager) {
    _manager = manager;

}

GameBit * BitsManager::JsonLoadBit(Value &bitInfo) {
    if(!bitInfo.HasMember("id")){ throw "Missing the 'id' on a game piece"; }
    if(!bitInfo.HasMember("type")){ throw "Missing the 'type' on a game piece"; }
    string bitId = bitInfo["id"].GetString();
    string refId = bitId + "_" + to_string(AllGameBits.count(bitId));
    string bitType = bitInfo["type"].GetString();
    if(bitType == "pieces_set")
    {
        AllGameBits[bitId][refId] = new PieceSet(_manager, refId);
    }
    else if(bitType == "hex_board")
    {
        AllGameBits[bitId][refId] = new HexBoard(_manager, refId);
    }
    else if(bitType == "piece")
    {
        AllGameBits[bitId][refId] = new Piece(_manager, refId);
    }
    if(AllGameBits.count(bitId) == 0){ throw "Unknow 'type' of game bit '" + bitType + "'"; }
    AllGameBits[bitId][refId]->JsonLoad(bitInfo);
    return AllGameBits[bitId][refId];
}
