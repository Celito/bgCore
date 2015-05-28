//
// Created by Celito on 2015-05-27.
//

#ifndef BGCORE_CONFIG_H
#define BGCORE_CONFIG_H

#include <string>
#include <rapidjson/document.h>

using namespace std;

class Config {

public:
    Config();

    void JsonLoad(rapidjson::Value &jsonObj);
};


#endif //BGCORE_CONFIG_H
