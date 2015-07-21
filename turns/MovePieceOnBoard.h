//
// Created by Celito on 7/20/2015.
//

#ifndef BGCORE_MOVEPIECEONBOARD_H
#define BGCORE_MOVEPIECEONBOARD_H

#include "../gameBits/BitReference.h"
#include "Action.h"
#include "../gameBits/boards/Board.h"
#include "ChoosePieceOnBoard.h"
#include "../rules/EnableMovementRule.h"

class MovePieceOnBoard : public ChoosePieceOnBoard {
public:
    MovePieceOnBoard(shared_ptr<BitReference> target_board);

    virtual void update_options() override;

    virtual string get_description() const override;

    void add_enable_movement_rule(shared_ptr<EnableMovementRule> rule);

private:
    vector< shared_ptr<Rule> > _enable_movement_rules;
};


#endif //BGCORE_MOVEPIECEONBOARD_H
