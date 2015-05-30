//
// Created by Celito on 2015-05-29.
//

#include <map>
#include "BitsManager.h"
#include "gameBits/PieceSet.h"
#include "gameBits/HexBoard.h"

using namespace rapidjson;
using namespace std;

BitsManager::BitsManager(GameManager *manager) {
    _manager = manager;

    BitBasicTypesIds["piece_set"] = ePieceSet;
    BitBasicTypesIds["hex_board"] = eHexBoard;

}

void BitsManager::JsonLoad(rapidjson::Value &bitsList) {
    for (int i = 0; i < bitsList.Size(); ++i) {
        Value& bitInfo = bitsList[i];
        assert(bitInfo.HasMember("id"));
        assert(bitInfo.HasMember("type"));
        string bitId = bitInfo["id"].GetString();
        assert(AllGameBits.count( bitId ) == 0);
        string bitType = bitInfo["type"].GetString();
        GameBit* newBit = nullptr;
        if(bitType == "pieces_set")
        {
            AllGameBits[bitId] = new PieceSet(_manager);
        }
        else if(bitType == "hex_board")
        {
            AllGameBits[bitId] = new HexBoard(_manager);
        }
//        switch(BitBasicTypesIds[bitType])
//        {
//            case ePieceSet:
//                break;
//            case eHexBoard:
//                break;
//        }
        AllGameBits[bitId]->JsonLoad(bitInfo);
    }
}
