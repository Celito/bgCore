//
// Created by Celito on 2015-07-20.
//

#ifndef BGCORE_CHOOSEPIECEONBOARD_H
#define BGCORE_CHOOSEPIECEONBOARD_H


#include "ActionDef.h"

class ChoosePieceOnBoard : public ActionDef {
public:
    ChoosePieceOnBoard(shared_ptr<BitReference> target_board);

    virtual void update_options(Action &action) override;

    virtual string get_description() const override;
};


#endif //BGCORE_CHOOSEPIECEONBOARD_H
