//
// Created by Celito on 2015-07-09.
//

#include "ChooseTileOnBoard.h"
#include "options/TileOption.h"
#include "../../gameBits/Piece.h"
#include "../../gameBits/BitReference.h"
#include "../../gameBits/boards/Tile.h"
#include "../../rules/Rule.h"
#include "../../rules/TestableRule.h"
#include "../../rules/MovementFilterRule.h"
#include "../../rules/RulesManager.h"

ChooseTileOnBoard::ChooseTileOnBoard(shared_ptr<BitReference> target) {
    _bit_refs[e_board] = target;
}

string ChooseTileOnBoard::get_description() const {
    return "Choose a board location";
}

void ChooseTileOnBoard::update_options(Action &action) {

    shared_ptr<Board> target_board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(action.get_req_bit(e_board));
    shared_ptr<Piece> piece = (shared_ptr<Piece>)dynamic_pointer_cast<Piece>(action.get_req_bit(e_piece));

    if(target_board == nullptr) throw new exception();
    if(piece == nullptr) throw new exception();
    
    if(_reason == e_for_placement) {
        vector<shared_ptr<Tile> > tiles = target_board->get_tiles();
        // find all available tiles on the board
        const vector< shared_ptr<Rule> > &placement_rules =
                piece->get_game().rules_manager()->get_rules(e_placement_rule, piece->get_bit_id());

        for (auto tile : tiles) {
            bool is_available = true;
            for (auto rule_ptr : placement_rules) {
                shared_ptr<TestableRule> placement_rule =
                        (shared_ptr<TestableRule>)dynamic_pointer_cast<TestableRule>(rule_ptr);
                if(placement_rule == nullptr) throw new exception();
                placement_rule->add_req_bit(e_tile, tile);
                if(!placement_rule->test()){
                    is_available = false;
                    break;
                }
            }
            if(is_available) {
                action.add_option(make_shared<TileOption>(tile));
            }
        }
    }
    else if(_reason == e_for_movement){
        shared_ptr<Tile> start_tile = (shared_ptr<Tile>)dynamic_pointer_cast<Tile>(action.get_req_bit(e_tile));

        if(start_tile == nullptr) throw new exception();

        // get all the movement rules and apply them to the options;
        const vector< shared_ptr<Rule> > &movement_rules =
                piece->get_game().rules_manager()->get_rules(e_movement_rule, piece->get_bit_id());

        if(movement_rules.size() == 0) throw new exception();

        vector<shared_ptr<Option>> options;
        // apply each of the movement rule at the options;
        for (shared_ptr<Rule> rule : movement_rules) {
            shared_ptr<MovementFilterRule> movement_rule =
                    (shared_ptr<MovementFilterRule>)dynamic_pointer_cast<MovementFilterRule>(rule);
            if(movement_rule == nullptr) throw new exception();
            movement_rule->filter_positions(options, start_tile);
        }
        for (auto option : options) {
            action.add_option(option);
        }
    }
}

bool ChooseTileOnBoard::is_available(shared_ptr<Player> player) {
    shared_ptr<Board> board = (shared_ptr<Board>)dynamic_pointer_cast<Board>(_bit_refs[e_board].get()->get_bit(player));

    return board != nullptr && !board->is_empty();
}

action_type_e ChooseTileOnBoard::get_type() {
    return e_choose_tile;
}
