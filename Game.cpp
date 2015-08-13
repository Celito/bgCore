//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <algorithm>
#include <stdint-gcc.h>
#include "Game.h"
#include "GameController.h"
#include "player/Player.h"
#include "BitsManager.h"
#include "gameBits/PieceSet.h"
#include "turns/TurnsManager.h"
#include "turns/TurnDef.h"
#include "turns/State.h"
#include "turns/actions/ActionDef.h"
#include "gameBits/boards/HexBoard.h"
#include "turns/actions/PutPieceOnBoard.h"
#include "turns/actions/MultiActions.h"
#include "turns/actions/MovePieceOnBoard.h"
#include "rules/PlayerAttrComparison.h"
#include "rules/MovementFilterRule.h"
#include "rules/RulesManager.h"
#include "rules/IsEmpty.h"

using namespace std;

Game::Game() {
    cout << "Creating the Game" << endl;

    // Initialize the supporting managers;
    _bits_manager = make_shared<BitsManager>(*this);
    _turns = make_shared<TurnsManager>(*this);
    _attr_manager = make_shared<AttrManager>();
    _rules_manager = make_shared<RulesManager>();

    // TEMP starting to manual load the game configuration
    _num_of_players = 2;
    string PLAYER_PIECES = "PiecesSet";
    string COLOR_ATTR = "Color";
    string HEX_BOARD_NAME = "Table";

    // TEMP vector with the quantity of each piece on the set and its bit id
    vector<pair<uint32_t , string> > pieces_info =
    {
        {1, "Queen"},
        {2, "Beetle"},
        {2, "Spider"},
        {3, "GrassHooper"},
        {3, "Ant"},
    };

    // TEMP creating the game pieces and making its setup

    //TODO: create the group of pieces

    //TODO: separate the bits loading from the game setup

    for (uint32_t i = 0; i < _num_of_players; i++) {

        shared_ptr<Player> player = make_shared<Player>(*this, i+1);
        register_new_bit(player);
        player->set_attr(COLOR_ATTR, i);
        _players.push_back(player);

        shared_ptr<PieceSet> player_set = make_shared<PieceSet>(*this, PLAYER_PIECES);
        register_new_bit(player_set);

        for(auto iter = pieces_info.begin(); iter != pieces_info.end(); iter++ )
        {
            for(uint32_t j = 0; j < iter->first; j++)
            {
                shared_ptr<Piece> new_piece = make_shared<Piece>(*this, iter->second);
                register_new_bit(new_piece);
                new_piece->set_attr(COLOR_ATTR, i);
                //curr_state()->transfer(player_set, new_piece);
                player_set->receive(new_piece);
            }
        }
        //curr_state()->transfer(_players[i], player_set);
        _players[i]->receive(player_set);
    }

    // TEMP create the board, call it 'Table' and add it to the table objects;
    shared_ptr<HexBoard> board = make_shared<HexBoard>(*this, HEX_BOARD_NAME);
    register_new_bit(board);

    // TEMP create the normal turn with the possible actions in it;

    //TODO: create the turn structure
    shared_ptr<TurnDef> normal_turn = make_shared<TurnDef>();

    auto put_piece_on_board =
            make_shared<PutPieceOnBoard>(
                    make_shared<BitReference>(PLAYER_PIECES, *this, true),
                    make_shared<BitReference>(HEX_BOARD_NAME, *this)
            );
    auto move_piece_on_board =
            make_shared<MovePieceOnBoard>(make_shared<BitReference>(HEX_BOARD_NAME, *this));

    auto first_action = make_shared<MultiActions>();

    first_action->add_sub_action(put_piece_on_board);

    first_action->add_sub_action(move_piece_on_board);

    normal_turn->add_action_def(first_action);

    _turns->register_turn_def(normal_turn);

    _is_over = false;

    // TEMP adding the rules to the rules dictionary

    //TODO: load the rules
    //TODO: add the e_movement_enable_rule that does not allow the player to split the hive
    //TODO: create events to allow the game to add and remove rules after a certain amount of rounds
    //TODO: add the e_placement_rule that does not allow the player to put pieces where they touch the other color from the second round on

    shared_ptr<PlayerAttrComparison> is_player_color = make_shared<PlayerAttrComparison>(*this);
    is_player_color->set_tested_attr(COLOR_ATTR);
    is_player_color->set_bit_type(e_piece);

    shared_ptr<IsEmpty> is_tile_empty = make_shared<IsEmpty>(*this);

    shared_ptr<MovementFilterRule> queen_movement = make_shared<MovementFilterRule>();
    queen_movement->set_max_steps(1);
    _rules_manager.get()->add_rule(e_movement_rule, "Queen", queen_movement);
    _rules_manager.get()->add_rule(e_movement_enable_rule, "Queen", is_player_color);
    _rules_manager.get()->add_rule(e_placement_rule, "Queen", is_tile_empty);

    shared_ptr<MovementFilterRule> spider_movement = make_shared<MovementFilterRule>();
    spider_movement->set_max_steps(3);
    spider_movement->set_min_steps(3);
    _rules_manager.get()->add_rule(e_movement_rule, "Spider", spider_movement);
    _rules_manager.get()->add_rule(e_movement_enable_rule, "Spider", is_player_color);
    _rules_manager.get()->add_rule(e_placement_rule, "Spider", is_tile_empty);

    shared_ptr<MovementFilterRule> ant_movement = make_shared<MovementFilterRule>();
    _rules_manager.get()->add_rule(e_movement_rule, "Ant", ant_movement);
    _rules_manager.get()->add_rule(e_movement_enable_rule, "Ant", is_player_color);
    _rules_manager.get()->add_rule(e_placement_rule, "Ant", is_tile_empty);

    //TODO: create the proper movement rules for the Beetle
    _rules_manager.get()->add_rule(e_movement_rule, "Beetle", ant_movement);
    _rules_manager.get()->add_rule(e_movement_enable_rule, "Beetle", is_player_color);
    _rules_manager.get()->add_rule(e_placement_rule, "Beetle", is_tile_empty);

    //TODO: create the proper movement rules for the GrassHooper
    _rules_manager.get()->add_rule(e_movement_rule, "GrassHooper", ant_movement);
    _rules_manager.get()->add_rule(e_movement_enable_rule, "GrassHooper", is_player_color);
    _rules_manager.get()->add_rule(e_placement_rule, "GrassHooper", is_tile_empty);
}

void Game::start(GameController &game_controller) {
    for(uint32_t i = 0; i < _players.size(); i++) {
        _players[i]->set_controller(game_controller.get_player_controller(i));
    }

    while(!_is_over) {
        _turns->next_turn();
    }
}

shared_ptr<Player> Game::get_player(uint32_t id) {
    return _players[id];
}

shared_ptr<GameBit> Game::get_table_bit(string bit_id) const {
    return _bits_manager->get_first_bit(bit_id);
}

void Game::register_new_bit(shared_ptr<GameBit> bit) {
    _bits_manager->register_bit(bit);
}

const shared_ptr<State> &Game::curr_state() {
    return _turns->get_curr_state();
}
