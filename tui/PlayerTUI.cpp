//
// Created by Celito on 2015-06-27.
//

#include <memory>
#include <c++/iostream>
#include <algorithm>
#include "PlayerTUI.h"
#include "../gameBits/boards/Tile.h"
#include "../player/PlayerInterface.h"
#include "../turns/Action.h"
#include "../turns/options/Option.h"
#include "../turns/ChooseTileOnBoard.h"
#include "../turns/options/TileOption.h"

void PlayerTUI::resolve_action(shared_ptr<Action> action) {
    //system("cls");
    vector<shared_ptr<Option>> const &options = action->get_options();
    shared_ptr<PlayerInterface> interface = get_interface().lock();
    uint32_t id = interface->get_id();
    if(ChooseTileOnBoard * board_action = dynamic_cast<ChooseTileOnBoard *>(action.get())) {
        shared_ptr<Board> board = board_action->get_board();
        if(board != nullptr){
            print_board(options, board);
        }
    }
    cout << action->get_description() << ":" << endl;
    for (int i = 0; i < options.size(); ++i) {
        cout << i << ") " << options[i]->get_description() << endl;
    }
    uint32_t option_id;
    while(!(cin >> option_id) || option_id >= options.size()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }
    action->choose(options[option_id]);
}

void PlayerTUI::print_board(const vector<shared_ptr<Option>> &options, const shared_ptr<Board> &board) const {
    vector< shared_ptr<Tile> > tiles = board.get()->get_tiles();
    sort(tiles.begin(), tiles.end(), [](shared_ptr<Tile> &t1, shared_ptr<Tile> &t2) {
                return t1->y() == t2->y() ? t1->x() < t2->x() : t1->y() > t2->y();
            });
    vector<string> lines;
    int curr_x = tiles[0]->x();
    int min_x = curr_x;
    int curr_y = tiles[0]->y();
    for (int i = 0, j = 0; i < tiles.size(); ++i) {
                shared_ptr<Tile> tile = tiles[i];
                bool new_line = false;
                if(curr_y != tile->y()){
                    new_line = true;
                    j += curr_y - tile->y();
                    curr_y = tile->y();
                }
                while(lines.size() <= j) lines.push_back("");
                if(new_line){
                    for (int k = 0; k < tile->x() - min_x; ++k) {
                        lines[j] += "   ";
                    }
                }
                while(curr_x < (tile->x() - 1)){
                    lines[j] += "   ";
                    curr_x++;
                }
                curr_x = tile->x();
                if(min_x > curr_x){
                    for (int k = 0; k < lines.size() - 1; ++k) {
                        for (int l = 0; l < min_x - curr_x; ++l) {
                            lines[k] = "   " + lines[k];
                        }
                    }
                    min_x = curr_x;
                }
                if(tile->is_empty()){
                    int opt_num = -1;
                    for (int k = 0; k < options.size(); ++k) {
                        if(auto tile_opt = dynamic_cast<TileOption *>(options[k].get())){
                            if(tile_opt != nullptr && tile_opt->get_tile() == tile){
                                opt_num = k;
                            }
                        }
                    }
                    if(opt_num == -1){
                        lines[j] += "[ ]";
                    }
                    else {
                        lines[j] += "[" + to_string(opt_num) + "]";
                    }
                }
                else {
                    lines[j] += "[X]";
                }
            }
    for (int k = 0; k < lines.size(); ++k) {
                cout << lines[k] << endl;
            }
}
