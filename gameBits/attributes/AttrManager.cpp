//
// Created by Celito on 7/17/2015.
//

#include "AttrManager.h"

uint32_t AttrManager::register_id(string id_name) {
    if(!is_registered(id_name)) _attr_ids[id_name] = _curr_ids++;
    return _attr_ids[id_name];
}
