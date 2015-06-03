//
// Created by Celito on 2015-05-29.
//

#ifndef BGCORE_BITSMANAGER_H
#define BGCORE_BITSMANAGER_H

#include <rapidjson/document.h>
#include <string>
#include <map>
#include <vector>

class GameManager;
class GameBit;

class BitsManager {

public:
    BitsManager(GameManager* manager);

    GameManager* _manager;

    //This is a nested map with the first key being the bit id and the second one being the bit refId
    std::map<std::string, std::map<std::string, GameBit *> > AllGameBits;

    template <typename T>
    void JsonLoadBitsList(rapidjson::Value &jsonArray, std::vector<T *> *bitsArray);

    GameBit * JsonLoadBit(rapidjson::Value &bitInfo);
};

template<typename T>
void BitsManager::JsonLoadBitsList(rapidjson::Value &jsonArray, std::vector<T *> *bitsArray) {
    if(!jsonArray.IsArray()){ throw "Json list of objects to load is not an array"; }
    for (uint16_t i = 0; i < jsonArray.Size(); ++i) {
        rapidjson::Value& bitInfo = jsonArray[i];
        uint16_t quantity = 1;
        //When there is multiple entries of the same bit the quantity is set here
        if(bitInfo.HasMember("quantity")) {
            quantity = bitInfo["quantity"].GetInt();
        }
        for (uint16_t j = 0; j < quantity; ++j) {
            GameBit *ret = JsonLoadBit(bitInfo);
            if(bitsArray != nullptr) {
                bitsArray->push_back((T *)ret);
            }
        }
    }
}




#endif //BGCORE_BITSMANAAGER_H
