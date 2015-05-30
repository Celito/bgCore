//
// Created by Celito on 2015-05-29.
//


#ifndef BGCORE_GAMEBIT_H
#define BGCORE_GAMEBIT_H

#include <rapidjson/document.h>

class GameManager;

class GameBit {
protected:
    GameManager* _game;
public:
    GameBit(GameManager *game);
    virtual void JsonLoad(rapidjson::Value& json){};
};


#endif //BGCORE_GAMEBIT_H
