//
// Created by Celito on 2015-06-30.
//

#ifndef BGCORE_MULTACTIONS_H
#define BGCORE_MULTACTIONS_H


#include "ActionDef.h"

using namespace std;

class MultiActions : public ActionDef {
public:

    void add_sub_action(shared_ptr<ActionDef> action);

    virtual void update_options() override;

    virtual bool is_available() const override;

    virtual void init(shared_ptr<Player> player) override;

    virtual string get_description() const override;

    virtual void choose(shared_ptr<Option> option) override;

    virtual bool self_resolve() override;

private:

    vector<shared_ptr<ActionDef> > _sub_actions;
};


#endif //BGCORE_MULTACTIONS_H
