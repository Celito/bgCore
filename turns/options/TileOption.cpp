//
// Created by Celito on 2015-07-14.
//

#include "TileOption.h"
#include "../../gameBits/boards/Tile.h"

string TileOption::get_description() {
    if(_path.size() == 0){
        return "[ " + to_string(get_tile()->x()) + ", " + to_string(get_tile()->y()) + " ]";
    }
    else {
        string ret;
        bool first = true;
        for (auto w_tile : _path) {
            shared_ptr<Tile> tile = w_tile.lock();
            if(first) {
                first = false;
            } else {
                ret += " -> ";
            }
            ret += tile->get_pos().to_string();
        }
        return ret;
    }
}

void TileOption::concat_path(vector<weak_ptr<Tile> > const &other_path) {
    for (auto item : other_path) {
        add_path_node(item);
    }
}
