//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PLAYERTUI_H
#define BGCORE_PLAYERTUI_H


#include "../player/PlayerController.h"
#include "GameTUI.h"

class Option;
class Board;

class PlayerTUI : public PlayerController {
public:
    PlayerTUI(GameTUI & gameTUI): _gameTUI(gameTUI) {}

    virtual void resolve_action(shared_ptr<Action> action) override;

    void print_board(const vector <shared_ptr<Option>> &options, const shared_ptr<Board> &board) const;

private:
    GameTUI &_gameTUI;

    void print_opts(const shared_ptr<Action> &action, const vector<shared_ptr<Option>> &options) const;
};


#endif //BGCORE_PLAYERTUI_H
