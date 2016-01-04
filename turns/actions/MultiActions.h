//
// Created by Celito on 2015-06-30.
//

#ifndef BGCORE_MULTACTIONS_H
#define BGCORE_MULTACTIONS_H


#include "ActionDef.h"

using namespace std;

class MultiActions : public ActionDef {
public:

    MultiActions(BgCore &game) : ActionDef(game) { }

    void add_sub_action(shared_ptr<ActionDef> action);

    virtual void update_options(Action &action) override;

    virtual string get_description() const override;

    virtual bool is_available(shared_ptr<Player> player);

    virtual const shared_ptr<ActionDef> &get_next_action_def(const shared_ptr<Option> &selected_option) override;

    virtual action_type_e get_type() const override { return e_action_type_multi_action; }

private:

    vector<shared_ptr<ActionDef> > _sub_actions;
};


#endif //BGCORE_MULTACTIONS_H
