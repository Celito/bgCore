//
// Created by Celito on 2015-06-27.
//

#include <c++/iostream>
#include <algorithm>
#include "PlayerTUI.h"
#include "../player/PlayerInterface.h"
#include "../turns/Action.h"
#include "../turns/options/Option.h"

void PlayerTUI::resolve_action(shared_ptr<Action> action) {
    system("cls");
    vector<shared_ptr<Option>> const &options = action->get_options();
    shared_ptr<PlayerInterface> interface = get_interface().lock();
    uint32_t id = interface->get_id();
    cout << "Player " << id << " controller received " << (action->is_available() ? "a valid" :  "an invalid") <<
            " action with " << options.size() << " options" <<  endl;
    cout << action->get_description() << ":" << endl;
    for (int i = 0; i < options.size(); ++i) {
        cout << i << ") " << options[i]->get_description() << endl;
    }
    uint32_t option_id;
    while(!(cin >> option_id) || option_id >= options.size()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    action->choose(options[option_id]);
}
