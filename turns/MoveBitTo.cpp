//
// Created by Celito on 2015-07-09.
//

#include "MoveBitTo.h"
#include "options/TileOption.h"

bool MoveBitTo::is_available() const {
    return false;
}

void MoveBitTo::init(shared_ptr<Player> player) {
    Action::init(player);
    assert(_target = dynamic_pointer_cast<Board>(_target_ref.get_bit()));
    vector<shared_ptr<Tile> > tiles =  _target.get()->get_available_titles();
    for_each(tiles.begin(), tiles.end(), [this](shared_ptr<Tile> tile){
        _options.push_back(make_shared<TileOption>(tile));
    });
}

string MoveBitTo::get_description() const {
    return "Choose a board location";
}
