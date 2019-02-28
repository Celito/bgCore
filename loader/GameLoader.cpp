//
// Created by CelitFel on 2019-02-28.
//

#include <fstream>
#include <iostream>
#include "GameLoader.h"
#include "ReservedWords/NumOfPlayers.h"

GameLoader::GameLoader(BgCore &game) {
    _wordsDictionary.push_back(make_shared<NumOfPlayers>());
    // TODO: create a dictionary of reserved words for the BGRules files;
        //TODO: create the TURNS word
}

void GameLoader::LoadRules(const string &filename) {
    string line;
    ifstream gameRulesFile(filename);
    if (gameRulesFile.is_open()) {
        while ( getline (gameRulesFile, line) ) {
            size_t foundPos = line.find_first_of(':');
            if(foundPos!=std::string::npos) {
                string reservedWord = line.substr(0, foundPos);
                cout << reservedWord << '\n';
                break;
                // TODO: find the reserved word in the dictionary;
            } else {
                // TODO: check if is just an empty line or a line missing the ':' marker;
            }

            // TODO: line by line, load each based on the reserved words dictionary ignoring empty lines
        }
        gameRulesFile.close();
    }

    else cout << "Unable to open file";
}
