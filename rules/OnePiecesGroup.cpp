//
// Created by Celito on 2015-08-16.
//

#include "OnePiecesGroup.h"
#include "../gameBits/boards/Tile.h"
#include <deque>

bool OnePiecesGroup::test() {
    if(_required_bits.count(e_tile) == 0) throw new exception();
    if(_required_bits[e_tile].expired()) throw new exception();

    shared_ptr<Tile> tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(_required_bits[e_tile].lock());

    deque<shared_ptr<Tile>> occupied_neighbours;

    for (uint32_t i = 0; i < tile->get_num_of_directions(); ++i){
        shared_ptr<Tile> neighbour = tile->get_neighbour(i);
        if(neighbour != nullptr && !neighbour->is_empty()) occupied_neighbours.push_back(neighbour);
    }
    if(occupied_neighbours.size() == 0) return false;
    if(occupied_neighbours.size() == 1) return true;
    deque<shared_ptr<Tile>> to_analyze;
    deque<shared_ptr<Tile>> analyzed;
    to_analyze.push_back(occupied_neighbours.front());
    analyzed.push_back(tile);
    occupied_neighbours.pop_front();
    while (to_analyze.size() > 0 && occupied_neighbours.size() > 0){
        shared_ptr<Tile> curr = to_analyze.front();
        to_analyze.pop_front();
        auto first_neighbour = find(occupied_neighbours.begin(), occupied_neighbours.end(), curr);
        if(first_neighbour != occupied_neighbours.end()) {
            occupied_neighbours.erase(first_neighbour);
        }
        for (uint32_t i = 0; i < curr->get_num_of_directions(); ++i) {
            shared_ptr<Tile> curr_neighbour = curr->get_neighbour(i);
            if(curr_neighbour != nullptr && !curr_neighbour->is_empty() &&
                    find(analyzed.begin(), analyzed.end(), curr_neighbour) == analyzed.end()){
                to_analyze.push_back(curr_neighbour);
            }
        }
        analyzed.push_back(curr);
    }

    _required_bits.clear();

    return occupied_neighbours.size() == 0;
}
