//
// Created by Celito on 5/27/2015.
//

#include <iostream>
#include <algorithm>
#include <stdint.h>
#include "BgCore.h"
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
#include "rules/TouchAnotherPieceRule.h"
#include "rules/IsRound.h"
#include "rules/JumpOverNeighbours.h"
#include "rules/movement/AlwaysTouching.h"
#include "rules/OnePiecesGroup.h"
#include "rules/movement/CanStack.h"
#include "gameBits/attributes/AttrManager.h"
#include "events/OnBitPlacedAt.h"

using namespace std;

BgCore::BgCore() {
    cout << "Creating the Game" << endl;

    // Initialize the supporting managers;
    _bits_manager = make_shared<BitsManager>(*this);
    _turns_manager = make_shared<TurnsManager>(*this);
    _attr_manager = make_shared<AttrManager>();
    _rules_manager = make_shared<RulesManager>();
    _event_manager = make_shared<EventManager>(*this);

    _is_over = false;

    // TEMP starting to manual load the game configuration
    _num_of_players = 2;
    string PLAYER_PIECES = "PiecesSet";
    string COLOR_ATTR = "Color";
    string HEX_BOARD_NAME = "Table";

    // TEMP vector with the quantity of each piece on the set and its bit id
    string GRASSHOPPER_NAME = "Grasshopper";
    string QUEEN_NAME = "Queen";
    string BEETLE_NAME = "Beetle";
    string SPIDER_NAME = "Spider";
    string ANT_NAME = "Ant";

    vector<pair<uint32_t, string> > pieces_info = {
            {1, QUEEN_NAME},
            {2, BEETLE_NAME},
            {2, SPIDER_NAME},
            {3, GRASSHOPPER_NAME},
            {3, ANT_NAME},
    };

    // TEMP creating the game pieces and making its setup

    //TODO: separate the bits loading from the game setup

    shared_ptr<Piece> white_queen_piece;

    for (uint32_t i = 0; i < _num_of_players; i++) {

        shared_ptr<Player> player = make_shared<Player>(*this, i + 1);
        register_new_bit(player);
        player->set_attr(COLOR_ATTR, i);
        _players.push_back(player);

        shared_ptr<PieceSet> player_set = make_shared<PieceSet>(*this, PLAYER_PIECES);
        register_new_bit(player_set);

        for (auto iter = pieces_info.begin(); iter != pieces_info.end(); iter++) {
            for (uint32_t j = 0; j < iter->first; j++) {
                shared_ptr<Piece> new_piece = make_shared<Piece>(*this, iter->second);
                register_new_bit(new_piece);
                new_piece->set_attr(COLOR_ATTR, i);
                player_set->receive(new_piece);
                if(i == 0 && iter->second == QUEEN_NAME)
                {
                    white_queen_piece = new_piece;
                }
            }
        }
        _players[i]->receive(player_set);
    }

    // TEMP create the board, call it 'Table' and add it to the table objects;
    shared_ptr<HexBoard> board = make_shared<HexBoard>(*this, HEX_BOARD_NAME);
    register_new_bit(board);
    board->initialize_tiles(true);

    // TEMP create the normal turn with the possible actions in it;
    shared_ptr<TurnDef> normal_turn = make_shared<TurnDef>();

    auto put_piece_on_board =
            make_shared<PutPieceOnBoard>(
                    *this,
                    make_shared<BitReference>(PLAYER_PIECES, *this, true),
                    make_shared<BitReference>(HEX_BOARD_NAME, *this)
            );
    auto move_piece_on_board =
            make_shared<MovePieceOnBoard>(*this, make_shared<BitReference>(HEX_BOARD_NAME, *this));

    auto first_action = make_shared<MultiActions>(*this);

    first_action->add_sub_action(put_piece_on_board);

    first_action->add_sub_action(move_piece_on_board);

    normal_turn->add_action_def(first_action);

    _turns_manager->register_turn_def(normal_turn);

    // TEMP adding the rules to the rules dictionary

    //TODO: create bit_name and retype the bit_id from string to uint32_t

    //TODO: create the custom events
    //TODO: add and event when the queen is added in game

    //TODO: make possible to add rules to a set of bits (like "all Pieces")
    //TODO: add the rule that you cannot move any piece until the queen is in game
    //TODO: add the rule that the queen must be placed on game if it is the 4th round
    //TODO: add the victory condition

    // WHEN THE WHITE QUEEN IS PLACED ON THE TABLE:
    shared_ptr<OnBitPlacedAt> white_piece_on_table_event = make_shared<OnBitPlacedAt>(white_queen_piece, board);

    // PLAYERS CAN ONLY MOVE THEIR COLOR PIECES
    shared_ptr<PlayerAttrComparison> is_player_color = make_shared<PlayerAttrComparison>(*this);
    is_player_color->set_tested_attr(COLOR_ATTR);
    is_player_color->set_bit_type(e_piece);
    is_player_color->set_usage(e_movement_enable_rule);
    is_player_color->add_applicable_bit(_bits_manager->get_bit_id_by_name(QUEEN_NAME));
    is_player_color->add_applicable_bit(_bits_manager->get_bit_id_by_name(SPIDER_NAME));
    is_player_color->add_applicable_bit(_bits_manager->get_bit_id_by_name(ANT_NAME));
    is_player_color->add_applicable_bit(_bits_manager->get_bit_id_by_name(BEETLE_NAME));
    is_player_color->add_applicable_bit(_bits_manager->get_bit_id_by_name(GRASSHOPPER_NAME));
    _rules_manager.get()->add_static_rule(is_player_color);

    // PLAYERS CANNOT MOVE PIECES IF THEY ARE GOING TO SPLIT THE GROUP OF PIECES
    shared_ptr<OnePiecesGroup> is_one_hive = make_shared<OnePiecesGroup>(*this);
    is_one_hive->set_usage(e_movement_enable_rule);
    is_one_hive->add_applicable_bit(_bits_manager->get_bit_id_by_name(QUEEN_NAME));
    is_one_hive->add_applicable_bit(_bits_manager->get_bit_id_by_name(SPIDER_NAME));
    is_one_hive->add_applicable_bit(_bits_manager->get_bit_id_by_name(ANT_NAME));
    is_one_hive->add_applicable_bit(_bits_manager->get_bit_id_by_name(BEETLE_NAME));
    is_one_hive->add_applicable_bit(_bits_manager->get_bit_id_by_name(GRASSHOPPER_NAME));
    _rules_manager->add_static_rule(is_one_hive);

    // PLAYERS CAN ONLY PUT PIECES IN EMPTY TILES
    shared_ptr<IsEmpty> is_tile_empty = make_shared<IsEmpty>(*this);
    is_tile_empty->set_usage(e_placement_rule);
    is_tile_empty->add_applicable_bit(_bits_manager->get_bit_id_by_name(QUEEN_NAME));
    is_tile_empty->add_applicable_bit(_bits_manager->get_bit_id_by_name(SPIDER_NAME));
    is_tile_empty->add_applicable_bit(_bits_manager->get_bit_id_by_name(ANT_NAME));
    is_tile_empty->add_applicable_bit(_bits_manager->get_bit_id_by_name(BEETLE_NAME));
    is_tile_empty->add_applicable_bit(_bits_manager->get_bit_id_by_name(GRASSHOPPER_NAME));
    _rules_manager.get()->add_static_rule(is_tile_empty);

    // TimedCondition
    shared_ptr<IsRound> is_second_round = make_shared<IsRound>(*this);
    is_second_round->is_bigger_then(1);
    shared_ptr<TimedCondition> is_second_round_cond = make_shared<TimedCondition>(*this);
    is_second_round_cond->add_condition(is_second_round);

    // AFTER THE FIRST ROUND, PLAYERS CAN ONLY PUT PIECES TOUCHING SOME PIECE
    shared_ptr<TouchAnotherPieceRule> touch_any_piece = make_shared<TouchAnotherPieceRule>(*this);
    touch_any_piece->set_usage(e_placement_rule);
    touch_any_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(QUEEN_NAME));
    touch_any_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(SPIDER_NAME));
    touch_any_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(ANT_NAME));
    touch_any_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(BEETLE_NAME));
    touch_any_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(GRASSHOPPER_NAME));
    _rules_manager->add_conditioned_rule(touch_any_piece, is_second_round_cond);

    // AFTER THE FIRST ROUND, PLAYERS CAN ONLY PUT PIECES WHERE THEY WON'T TOUCH ANOTHER COLOR PIECES
    shared_ptr<TouchAnotherPieceRule> not_touch_another_color_piece = make_shared<TouchAnotherPieceRule>(*this);
    not_touch_another_color_piece->set_usage(e_placement_rule);
    not_touch_another_color_piece->set_reverse(true);
    not_touch_another_color_piece->add_compared_player_attr("Color", false);
    not_touch_another_color_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(QUEEN_NAME));
    not_touch_another_color_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(SPIDER_NAME));
    not_touch_another_color_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(ANT_NAME));
    not_touch_another_color_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(BEETLE_NAME));
    not_touch_another_color_piece->add_applicable_bit(_bits_manager->get_bit_id_by_name(GRASSHOPPER_NAME));
    _rules_manager->add_conditioned_rule(not_touch_another_color_piece, is_second_round_cond);

    shared_ptr<AlwaysTouching> always_touching = make_shared<AlwaysTouching>();
    shared_ptr<CanStack> cannot_stack = make_shared<CanStack>(false);

    // THE QUEEN CAN ONLY MOVE ONE TILE, IT MUST BE EMPTY AND IT MUST BE ALWAYS TOUCHING AT LEAST ON PIECE
    shared_ptr<MovementFilterRule> queen_movement = make_shared<MovementFilterRule>();
    queen_movement->set_max_steps(1);
    queen_movement->set_usage(e_movement_rule);
    queen_movement->add_applicable_bit(_bits_manager->get_bit_id_by_name(QUEEN_NAME));
    queen_movement->add_movement_sub_rule(always_touching);
    queen_movement->add_movement_sub_rule(cannot_stack);
    _rules_manager.get()->add_static_rule(queen_movement);

    // THE SPIDER CAN ONLY MOVE 3 TILES, NOT LESS THEN 3 TILES, THE TILE MUST BE EMPTY AND IT MUST BE ALWAYS TOUCHING
    // AT LEAST ONE PIECE
    shared_ptr<MovementFilterRule> spider_movement = make_shared<MovementFilterRule>();
    spider_movement->set_max_steps(3);
    spider_movement->set_min_steps(3);
    spider_movement->set_usage(e_movement_rule);
    spider_movement->add_applicable_bit(_bits_manager->get_bit_id_by_name(SPIDER_NAME));
    spider_movement->add_movement_sub_rule(always_touching);
    spider_movement->add_movement_sub_rule(cannot_stack);
    _rules_manager.get()->add_static_rule(spider_movement);

    // |THE ANT| |CAN MOVE| |AS MUCH AS IT WANTS|, |THE TILE MUST BE EMPTY| AND |IT MUST BE ALWAYS TOUCHING AT LEAST ONE
    // PIECE|
    shared_ptr<MovementFilterRule> ant_movement = make_shared<MovementFilterRule>();
    ant_movement->set_usage(e_movement_rule);
    ant_movement->add_applicable_bit(_bits_manager->get_bit_id_by_name(ANT_NAME));
    ant_movement->add_movement_sub_rule(always_touching);
    ant_movement->add_movement_sub_rule(cannot_stack);
    _rules_manager.get()->add_static_rule(ant_movement);

    // THE BEETLE CAN MOVE ONLY ONE TILE, IT CAN STACK ON TOP OF ANOTHER PIECES AND IT MUST BE ALWAYS TOUCHING AT LEAST
    // ONE PIECE
    shared_ptr<MovementFilterRule> beetle_movement = make_shared<MovementFilterRule>();
    beetle_movement->set_max_steps(1);
    beetle_movement->set_usage(e_movement_rule);
    beetle_movement->add_applicable_bit(_bits_manager->get_bit_id_by_name(BEETLE_NAME));
    beetle_movement->add_movement_sub_rule(always_touching);
    _rules_manager->add_static_rule(beetle_movement);

    // |THE GRASSHOPPER| |CAN JUMP OVER ANOTHER PIECES|
    shared_ptr<JumpOverNeighbours> grasshopper_movement = make_shared<JumpOverNeighbours>();
    grasshopper_movement->set_usage(e_movement_rule);
    grasshopper_movement->add_applicable_bit(_bits_manager->get_bit_id_by_name(GRASSHOPPER_NAME));
    _rules_manager->add_static_rule(grasshopper_movement);


}

void BgCore::start(GameController &game_controller) {
    _initialize_pieces();

    for (uint32_t i = 0; i < _players.size(); i++) {
        _players[i]->set_controller(game_controller.get_player_controller(i));
    }

    while (!_is_over) {
        _turns_manager->next_turn();
    }
}

shared_ptr<Player> BgCore::get_player(uint32_t id) {
    return _players[id];
}

shared_ptr<GameBit> BgCore::get_table_bit(string bit_id) const {
    return _bits_manager->get_first_bit(bit_id);
}

void BgCore::register_new_bit(shared_ptr<GameBit> bit) {
    // Add bit to the general list of bits and give it an unique id
    _bits_manager->register_bit(bit);
    // Subscribe the bit to the init signal
    _initialize_pieces.connect(boost::bind(&GameBit::init, bit.get()));
}

const shared_ptr<State> &BgCore::curr_state() {
    return _turns_manager->get_curr_state();
}
