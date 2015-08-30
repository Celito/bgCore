//
// Created by Celito on 7/17/2015.
//

#ifndef BGCORE_ATTRMANAGER_H
#define BGCORE_ATTRMANAGER_H

#include <map>
#include <string>
#include <stdint.h>

class BgCore;

using namespace std;

class AttrManager {
public:
    uint32_t register_id(string id_name);

    bool is_registered(string id_name) { return _attr_ids.count(id_name) != 0; }
    uint32_t get_id(string id_name) const { return _attr_ids.at(id_name); }
private:
    uint32_t _curr_ids;
    map<string, uint32_t> _attr_ids;
};


#endif //BGCORE_ATTRMANAGER_H
