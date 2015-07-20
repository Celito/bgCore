//
// Created by Celito on 2015-06-27.
//

#ifndef BGCORE_PLAYERTUI_H
#define BGCORE_PLAYERTUI_H


#include "../player/PlayerController.h"

class PlayerTUI : public PlayerController {

    virtual void resolve_action(shared_ptr<Action> action) override;

    void print_board(const vector <shared_ptr<Option>> &options, const shared_ptr<Board> &board) const;
};


#endif //BGCORE_PLAYERTUI_H
