//
// Created by Celito on 7/17/2015.
//

#ifndef BGCORE_ATTRMANAGER_H
#define BGCORE_ATTRMANAGER_H

#include <map>
#include <string>

class Game;

using namespace std;

class AttrManager {
public:
    bool is_registered(string id_name) { return _attr_ids.count(id_name) != 0; }
    void register_id(string id_name) { if(!is_registered(id_name)) _attr_ids[id_name] = _curr_ids++; }
    uint32_t get_id(string id_name) { return _attr_ids[id_name]; }
private:
    uint32_t _curr_ids;
    map<string, uint32_t> _attr_ids;
};


#endif //BGCORE_ATTRMANAGER_H
