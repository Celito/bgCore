//
// Created by Celito on 8/14/2015.
//

#include "JumpOverNeighbours.h"
#include <queue>
#include <set>
#include "../turns/actions/options/TileOption.h"
#include "../gameBits/boards/TilePos.h"
#include "../gameBits/boards/Tile.h"
#include "../gameBits/Piece.h"

void JumpOverNeighbours::filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile,
                      const shared_ptr<Piece> &moving_piece)
{
    bool available_opts = true;
    moving_piece->set_parent(nullptr);
    queue< shared_ptr<TileOption> > possible_options;
    set< TilePos > tested_pos;
    tested_pos.insert(initial_tile->get_pos());
    shared_ptr<TileOption> initial_opt = make_shared<TileOption>(initial_tile);
    initial_opt->add_path_node(initial_tile);
    possible_options.push(initial_opt);

    while(available_opts) {
        shared_ptr<TileOption> opt = possible_options.front();
        possible_options.pop();
        shared_ptr<Tile> tile = opt->get_tile();
        for (uint32_t i = 0; i < tile->get_num_of_directions(); ++i) {
            shared_ptr<Tile> neighbour = tile->get_neighbour(i);
            const vector<weak_ptr<Tile>> &path = opt->get_path();
            bool is_straight_line = true;
            if(path.size() > 1) {
                uint32_t curr_path_dir = path[0].lock().get()->get_direction_of(path[1].lock()->get_pos());
                is_straight_line = (curr_path_dir == i);
            }
            if(neighbour != nullptr) {
                tested_pos.insert(neighbour->get_pos());
                if(is_straight_line){
                    shared_ptr<TileOption> new_opt = make_shared<TileOption>(neighbour);
                    new_opt->concat_path(path);
                    new_opt->add_path_node(neighbour);
                    if(!neighbour->is_empty()){
                        possible_options.push(new_opt);
                    }
                    else if(new_opt->get_path().size() > 2){
                        options.push_back(new_opt);
                    }
                }
            }
        }
        //keep going while there are available options to process;
        available_opts = possible_options.size() != 0;
    }
    initial_tile->receive(moving_piece);
}
