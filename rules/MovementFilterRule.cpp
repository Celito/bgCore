//
// Created by Celito on 7/31/2015.
//

#include "MovementFilterRule.h"
#include <queue>
#include <set>

void MovementFilterRule::filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile) {
    bool available_opts = true;
    queue< shared_ptr<TileOption> > possible_options;
    set< TilePos > tested_pos;
    tested_pos.insert(initial_tile->get_pos());
    shared_ptr<TileOption> initial_opt = make_shared<TileOption>(initial_tile);
    initial_opt->add_path(initial_tile);
    possible_options.push(initial_opt);

    while(available_opts) {
        shared_ptr<TileOption> opt = possible_options.front();
        possible_options.pop();
        shared_ptr<Tile> tile = opt->get_tile();
        for (uint32_t i = 0; i < tile->get_num_of_directions(); ++i) {
            shared_ptr<Tile> neighbour = tile->get_neighbour(i);
            //auto iter = tested_pos.find(tile->get_pos());
            if(neighbour != nullptr && neighbour->is_empty() &&
                    tested_pos.find(neighbour->get_pos()) == tested_pos.end()) {
                shared_ptr<TileOption> new_opt = make_shared<TileOption>(neighbour);
                new_opt->add_path(opt->get_path());
                new_opt->add_path(neighbour);
                possible_options.push(new_opt);
                tested_pos.insert(neighbour->get_pos());
                //TODO: test if the path is bigger than a min a smaller than a max
                options.push_back(new_opt);
            }
        }
        //keep going while there are available options to process;
        available_opts = possible_options.size() != 0;
    }
}
