//
// Created by Celito on 8/14/2015.
//

#include "AlwaysTouching.h"
#include "../../gameBits/boards/Tile.h"
#include "../../turns/actions/options/TileOption.h"


bool AlwaysTouching::opt_can_be_processed(const shared_ptr<TileOption> &analyzed_option) {
    shared_ptr<Tile> next = analyzed_option.get()->get_tile();
    if(!next->is_empty()) return true;
    const vector<weak_ptr<Tile>> &path = analyzed_option->get_path();
    if(path.size() < 2) return false;
    shared_ptr<Tile> previous_tile = path[path.size() - 2].lock();
    uint32_t num_directions = previous_tile->get_num_of_directions();
    uint32_t direction = previous_tile->get_direction_of(next->get_pos());
    const shared_ptr<Tile> &other1 = previous_tile->get_neighbour(direction == (num_directions - 1) ? 0 : direction + 1);
    const shared_ptr<Tile> &other2 = previous_tile->get_neighbour(direction == 0 ? (num_directions - 1) : direction - 1);
    return (other1 != nullptr && !other1->is_empty()) || (other2 != nullptr && !other2->is_empty());
}
