//
// Created by Celito on 2015-08-16.
//

#include "CanStack.h"
#include "../../turns/actions/options/TileOption.h"
#include "../../gameBits/boards/Tile.h"

bool CanStack::opt_can_be_processed(const shared_ptr<TileOption> &analyzed_option) {
    if(_can_stack){
        return true;
    }
    else {
        return !analyzed_option->get_tile()->is_empty();
    }
}
