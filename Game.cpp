//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <vector>
#include <stdint-gcc.h>
#include "json/json.h"
#include "Game.h"
#include "Player.h"
#include "ConfigManager.h"
#include "BitsManager.h"
#include "gameBits/boards/HexBoard.h"
#include "gameBits/PieceSet.h"
#include "TurnsManager.h"

using namespace std;
using namespace rapidjson;

Game::Game() {
    cout << "Creating the Game" << endl;

    //For now this is the list of players
    Bits = new BitsManager(this);
    Config = new ConfigManager();

    //MANUAL LOADING
    Config->PlayersNum = 2;
    const string PLAYER_PIECES = "PlayerPieces";
    const string QUEEN = "Queen";
    Bits->AllGameBits["Table"]["Table_0"] = new HexBoard(this, "Table_0");
    for (uint16_t i = 0; i < Config->PlayersNum; i++) {

        shared_ptr<Player> player = make_shared<Player>(i+1);
        _players.push_back(player);
        string pieceSetRefId = PLAYER_PIECES + "_" + to_string(i);
        PieceSet* playerSet = new PieceSet(this, pieceSetRefId);
        Bits->AllGameBits[PLAYER_PIECES][pieceSetRefId] = playerSet;
        player->Posetions[pieceSetRefId] = playerSet;
        const string queenRefId = QUEEN + "_" + to_string(i);
        Piece *queen = new Piece(this, queenRefId);
        playerSet->Pieces.push_back(queen);
    }

    new TurnsManager(this);

//    Document document;

    //Open the rules file
//    ifstream file("rules/hive.rules");
//    file.seekg(0, std::ios::end);
//    size_t size = (size_t) file.tellg();
//    std::string buffer(size, ' ');
//    file.seekg(0);
//    file.read(&buffer[0], size);

//    Json::Value root;
//    Json::Reader reader;
//    bool parsingSuccessful = reader.parse(buffer,root);
//    if ( !parsingSuccessful )
//    {
//        // report to the user the failure and their locations in the document.
//        std::cout  << "Failed to parse configuration\n"
//        << reader.getFormattedErrorMessages();
//        return;
//    }

//    document.Parse(buffer.c_str());
//    if (document.HasParseError()) {
//        cout << "\nError: " <<  GetParseError_En(document.GetParseError()) << endl;
//    }
//    system("pause");
//    if(!document.IsObject()){throw "ERROR";}
//
//    Value& configValues = document["game_config"];
//    Config->JsonLoad(configValues);

    //Instantiate players
//
//    Value& bitsValues = document["game_bits"];
//    Bits->JsonLoadBitsList<GameBit>(bitsValues, nullptr);

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
