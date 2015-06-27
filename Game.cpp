//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <vector>
#include <stdint-gcc.h>
#include "Game.h"
#include "Player.h"
#include "BitsManager.h"
#include "gameBits/PieceSet.h"
#include "TurnsManager.h"

using namespace std;

Game::Game() {
    cout << "Creating the Game" << endl;

    _bits = make_shared<BitsManager>(*this);

    //TEMP starting to manual load the game configuration
    num_of_players = 2;
    const string PLAYER_PIECES = "PlayerPieces";

    //TEMP vector with the quantity of each piece on the set and its bit id
    vector<pair<uint32_t , string> > pieces_info =
    {
        {1, "Queen"},
        {2, "Beetle"},
        {2, "Spider"},
        {3, "GrassHooper"},
        {3, "Ant"},
    };

    for (uint32_t i = 0; i < num_of_players; i++) {

        shared_ptr<Player> player = make_shared<Player>(i+1);
        _players.push_back(player);

        shared_ptr<PieceSet> player_set = _bits->create_bit<PieceSet>(PLAYER_PIECES);

        for(auto iter = pieces_info.begin(); iter != pieces_info.end(); iter++ )
        {
            for(uint32_t j = 0; j < iter->first; j++)
            {
                shared_ptr<Piece> new_piece = _bits->create_bit<Piece>(iter->second);
                player_set->add_piece(new_piece);
            }
        }
    }

    new TurnsManager(this);

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

void Game::Start() {

}
