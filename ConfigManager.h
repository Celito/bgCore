//
// Created by Celito on 2015-05-27.
//

#ifndef BGCORE_CONFIG_H
#define BGCORE_CONFIG_H

#include <string>
#include <rapidjson/document.h>

using namespace std;

class ConfigManager {

public:
    ConfigManager();

    void JsonLoad(rapidjson::Value &jsonObj);

    uint16_t PlayersNum;
};


#endif //BGCORE_CONFIG_H
