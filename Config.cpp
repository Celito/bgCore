//
// Created by Celito on 2015-05-27.
//

#include <c++/iostream>
#include "Config.h"

using namespace std;

Config::Config() {

}

void Config::JsonLoad(rapidjson::Value &jsonObj) {
    int playersNum = jsonObj["players"].GetInt();

    cout << "Number of players found = " << playersNum << endl;
}
