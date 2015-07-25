//
// Created by Celito on 2015-07-14.
//

#include "TileOption.h"

string TileOption::get_description() {
    return "[ " + to_string(get_tile()->x()) + ", " + to_string(get_tile()->y()) + " ]";
}
