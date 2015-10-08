//
// Created by Celito on 8/12/2015.
//

#include <algorithm>
#include "State.h"
#include "../BgCore.h"
#include "../BitsManager.h"

shared_ptr<GameBit> State::get_parent(uint32_t bit_id) const {
    return _parenting_table.count(bit_id) == 0 ||  _parenting_table.at(bit_id).expired() ?
           nullptr : _parenting_table.at(bit_id).lock();
}

const vector<weak_ptr<GameBit>> &State::get_children(uint32_t bit_id) const {
    if(_children_table.count(bit_id) == 0) return _no_children;
    return _children_table.at(bit_id);
}

void State::transfer(uint32_t child_id, shared_ptr<GameBit> parent_ptr) {
    const shared_ptr<GameBit> &old_parent = get_parent(child_id);
    shared_ptr<GameBit> child_ptr = _core.bits_manager()->get_bit(child_id);
    if(old_parent != nullptr){
        vector<weak_ptr<GameBit>> &children = _children_table[old_parent->get_unique_id()];
        children.erase(
                remove_if(
                        children.begin(),
                        children.end(),
                        [child_ptr](weak_ptr<GameBit> &item) -> bool {
                            return item.lock().get() == child_ptr.get();
                        }
                ),
                children.end()
        );
    }
    _parenting_table[child_id] = parent_ptr;
    if(parent_ptr != nullptr) _children_table[parent_ptr->get_unique_id()].push_back(child_ptr);
}

void State::remove_from_parent(uint32_t parent_id, shared_ptr<GameBit> child) {
    vector<weak_ptr<GameBit>> &children = _children_table[parent_id];
    children.erase(
            remove_if(
                    children.begin(),
                    children.end(),
                    [child](weak_ptr<GameBit> &item) -> bool {
                        return item.lock().get() == child.get();
                    }
            ),
            children.end()
    );
    _parenting_table.erase(child->get_unique_id());
}
