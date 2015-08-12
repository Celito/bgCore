//
// Created by Celito on 8/12/2015.
//

#ifndef BGCORE_STATE_H
#define BGCORE_STATE_H

#include <memory>
#include <map>
#include <vector>

class GameBit;

using namespace std;

class State {
public:
    shared_ptr<GameBit> get_parent(uint32_t bit_id) const;

    const vector<weak_ptr<GameBit>> & get_children(uint32_t bit_id) const;

    void transfer(uint32_t parent_id, shared_ptr<GameBit> child);

    void remove_from_parent(uint32_t parent_id, shared_ptr<GameBit> child);

private:
    // map of parenting for all the objects in the game
    map<uint32_t, weak_ptr<GameBit>> _parenting_table;
    map<uint32_t, vector<weak_ptr<GameBit>>> _children_table;

    vector<weak_ptr<GameBit>> _no_children;
};


#endif //BGCORE_STATE_H
