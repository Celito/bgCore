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
#include "ConfigManager.h"
#include "BitsManager.h"

using namespace std;
using namespace rapidjson;

GameManager::GameManager() {
    cout << "Creating the GameManager" << endl;

    //For now this is the list of players
    Players = new vector<Player*>();
    Bits = new BitsManager(this);
    Config = new ConfigManager();

    Document document;

    //Open the rules file
    ifstream file("rules/hive.rules");
    file.seekg(0, std::ios::end);
    size_t size = (size_t) file.tellg();
    std::string buffer(size, ' ');
    file.seekg(0);
    file.read(&buffer[0], size);

    document.Parse(buffer.c_str());
    if(!document.IsObject()){throw "ERROR";}

    Value& configValues = document["game_config"];
    Config->JsonLoad(configValues);

    //Instantiate players
    for (uint16_t i = 0; i < Config->PlayersNum; i++) {
        Players->push_back(new Player(i+1));
    }

    Value& bitsValues = document["game_bits"];
    Bits->JsonLoadBitsList<GameBit>(bitsValues, nullptr);

    //TODO: create a sample of rules (hive)

    //TODO: load the game bits

    //TODO: create the turn structure

    //TODO: load the rules

    //TODO: create the GameBits

    //TODO: create the Board

    //TODO: create the pieces

    //TODO: create the group of pieces

    //TODO: create the player inventory

    system("pause");
}
