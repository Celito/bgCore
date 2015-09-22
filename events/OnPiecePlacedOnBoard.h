//
// Created by Celito on 9/21/2015.
//

#ifndef BGCORE_ONBITPLACEDAT_H
#define BGCORE_ONBITPLACEDAT_H

#include <memory>
#include "CustomEvent.h"

using namespace std;

class GameBit;
class PlacePieceOnBoard;
class Action;

class OnPiecePlacedOnBoard : public CustomEvent {
public:
    OnPiecePlacedOnBoard(shared_ptr<GameBit> tracked_piece, shared_ptr<GameBit> target_board,
                        shared_ptr<PlacePieceOnBoard> action_def);

private:
    weak_ptr<GameBit> _tracked_piece;
    weak_ptr<GameBit> _target_board;

    bool _happened;

    void on_tracked_piece_placed_on_board(shared_ptr<Action> action);
};


#endif //BGCORE_ONBITPLACEDAT_H
