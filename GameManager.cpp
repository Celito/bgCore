//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <vector>
#include "GameManager.h"
#include "Player.h"

using namespace std;

GameManager::GameManager() {
    cout << "Creating the GameManager" << endl;

    vector<Player*>* players = new vector<Player*>();

    //TODO: this should be part of the game rules;
    uint16_t numOfPlayers = 2;

    //Instantiate players
    for (uint16_t i = 0; i < numOfPlayers; i++) {
        players->push_back(new Player(i+1));
    }

}
