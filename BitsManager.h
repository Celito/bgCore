//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_BITSMANAGER_H
#define BGCORE_BITSMANAGER_H

#include <rapidjson/document.h>
#include <string>
#include <map>

class GameManager;
class GameBit;

enum BitBasicType {
    eHexBoard,
    ePieceSet
};

class BitsManager {

public:
    BitsManager(GameManager* manager);

    GameManager* _manager;

    void JsonLoad(rapidjson::Value &bitsList);

    std::map<std::string, GameBit *> AllGameBits;

    std::map<std::string, BitBasicType> BitBasicTypesIds;
};


#endif //BGCORE_BITSMANAAGER_H
