//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <vector>
#include <c++/fstream>
#include <stdint-gcc.h>
#include "rapidjson/document.h"
#include "GameManager.h"
#include "Player.h"
#include "Config.h"

using namespace std;
using namespace rapidjson;

GameManager::GameManager() {
    cout << "Creating the GameManager" << endl;

    vector<Player*>* players = new vector<Player*>();

    Config* config = new Config();

    Document document;

    ifstream file("rules/hive.rules");
    file.seekg(0, std::ios::end);
    size_t size = (size_t) file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size);

    document.Parse(buffer.c_str());
    assert(document.IsObject());
    assert(document.HasMember("game_config"));

    Value& configValues = document["game_config"];
    config->JsonLoad(configValues);


//    bool configJson = d.HasMember("game_config");

    //TODO: this should be part of the game rules;
//    uint16_t numOfPlayers = 2;
//
//    //Instantiate players
//    for (uint16_t i = 0; i < numOfPlayers; i++) {
//        players->push_back(new Player(i+1));
//    }



    //TODO: create a sample of rules (hive)

    //TODO: create the turn structure

    //TODO: load the rules

    //TODO: create the GameBits

    //TODO: create the Board

    //TODO: create the pieces

    //TODO: create the group of pieces

    //TODO: create the player inventory

    system("pause");
}
