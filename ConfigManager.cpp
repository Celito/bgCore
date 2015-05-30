//
// Created by Celito on 2015-05-27.
//

#include <c++/iostream>
#include "ConfigManager.h"

using namespace std;

ConfigManager::ConfigManager() {

}

void ConfigManager::JsonLoad(rapidjson::Value &jsonObj) {
    if(!jsonObj.HasMember("players"))
    {
        throw "Missing core config value 'players' in the rules file";
    }

    uint16_t playersNum = jsonObj["players"].GetUint();

    PlayersNum = playersNum;
    cout << "Number of players found = " << playersNum << endl;
}
