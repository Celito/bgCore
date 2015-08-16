//
// Created by Celito on 2015-07-14.
//

#include "TileOption.h"
#include "../../../gameBits/boards/Tile.h"

string TileOption::get_description() {
    return "[ " + to_string(get_tile()->x()) + ", " + to_string(get_tile()->y()) + " ]";
}

void TileOption::concat_path(vector<weak_ptr<Tile> > const &other_path) {
    for (auto item : other_path) {
        add_path_node(item);
    }
}
