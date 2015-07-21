//
// Created by Celito on 2015-07-20.
//

#ifndef BGCORE_CHOOSEPIECEONBOARD_H
#define BGCORE_CHOOSEPIECEONBOARD_H


#include "Action.h"

class ChoosePieceOnBoard : public Action  {
public:
    ChoosePieceOnBoard(shared_ptr<BitReference> target_board);

    virtual void update_options() override;

    virtual string get_description() const override;
};


#endif //BGCORE_CHOOSEPIECEONBOARD_H
