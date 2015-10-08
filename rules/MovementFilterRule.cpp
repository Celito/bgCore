//
// Created by Celito on 7/31/2015.
//

#include "MovementFilterRule.h"
#include "../turns/actions/options/TileOption.h"
#include "../gameBits/boards/TilePos.h"
#include "../gameBits/boards/Tile.h"
#include "../gameBits/Piece.h"
#include <queue>
#include <set>


void MovementFilterRule::filter_positions(vector<shared_ptr<Option> > &options, shared_ptr<Tile> initial_tile,
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
            if(neighbour == nullptr) continue;
            shared_ptr<TileOption> new_opt = make_shared<TileOption>(neighbour);
            new_opt->concat_path(opt->get_path());
            new_opt->add_path_node(neighbour);
            bool still_have_steps = !_restricted_steps || (opt->get_path().size() <= _max_steps);
            bool will_process = opt_can_be_processed(new_opt);
            bool it_was_not_tested = tested_pos.find(neighbour->get_pos()) == tested_pos.end();
            if(still_have_steps && will_process && it_was_not_tested) {
                possible_options.push(new_opt);
                tested_pos.insert(neighbour->get_pos());
                bool is_not_too_short = !_restricted_steps || new_opt->get_path().size() > _min_steps;
                if (is_not_too_short){
                    options.push_back(new_opt);
                }
            }
        }
        //keep going while there are available options to process;
        available_opts = possible_options.size() != 0;
    }
    initial_tile->receive(moving_piece);
}


void MovementFilterRule::set_max_steps(uint32_t value) {
    _restricted_steps = true;
    _max_steps = value;
}

void MovementFilterRule::set_min_steps(uint32_t value) {
    _restricted_steps = true;
    _min_steps = value;
}

bool MovementFilterRule::opt_can_be_processed(const shared_ptr<TileOption> &opt) const {
    bool result = true;
    for (auto sub_rule : _movement_sub_rules) {
        result &= sub_rule.get()->opt_can_be_processed(opt);
    }

    return result;
}

void MovementFilterRule::add_movement_sub_rule(const shared_ptr<MovementSubRule> &sub_rule) {
    _movement_sub_rules.push_back(sub_rule);
}
