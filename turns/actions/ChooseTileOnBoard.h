//
// Created by Celito on 2015-07-09.
//

#ifndef BGCORE_MOVEBITTO_H
#define BGCORE_MOVEBITTO_H

#include "ActionDef.h"
#include "../../gameBits/boards/Board.h"

class ChooseTileOnBoard : public ActionDef
{
public:
    ChooseTileOnBoard(BgCore &game, shared_ptr<BitReference> target);

    virtual void update_options(Action &action) override;

    virtual string get_description() const override;

    virtual bool is_available(shared_ptr<Player> player);

    void set_reason(const available_tiles_t &_reason) { ChooseTileOnBoard::_reason = _reason; }

    virtual void init_by_option(shared_ptr<Action> action, shared_ptr<Option> selected_option) override;

    virtual action_type_e get_type() const override { return e_action_type_choose_tile_on_board; }

private:
    available_tiles_t _reason = e_for_placement;
};


#endif //BGCORE_MOVEBITTO_H
