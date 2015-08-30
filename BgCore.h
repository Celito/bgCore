//
// Created by Celito on 5/27/2015.
//

#ifndef BGCORE_GAMEMANAGER_H
#define BGCORE_GAMEMANAGER_H

#include <vector>
#include <memory>
#include <map>
#include <boost/signals2.hpp>

class Player;
class BitsManager;
class ConfigManager;
class GameBit;
class TurnsManager;
class RulesManager;
class EventManager;
class AttrManager;
class PlayerController;
class GameController;
class State;

using namespace std;

class BgCore {
public:
    BgCore();

    //interface:
    void start(GameController &game_controller);

    //internal:
    shared_ptr<Player> get_player(uint32_t id);

    uint32_t get_num_of_players() const { return _num_of_players; }

    shared_ptr<GameBit> get_table_bit(string bit_id) const;

    void register_new_bit(shared_ptr<GameBit> bit);

    const shared_ptr<AttrManager> &attr_manager() const { return  _attr_manager; }

    const shared_ptr<BitsManager> &bits_manager() const { return _bits_manager; }

    const shared_ptr<RulesManager> &rules_manager() const { return _rules_manager; }

    const shared_ptr<TurnsManager> &turns_manager() const { return _turns_manager; }

    const shared_ptr<EventManager> &event_manager() const { return _event_manager; }

    const shared_ptr<State> &curr_state();

private:
//game config:
    uint32_t _num_of_players;
    bool _is_over;

    //game pointers:
    vector< shared_ptr<Player> > _players;

    //helper managers:
    shared_ptr<BitsManager> _bits_manager;
    shared_ptr<TurnsManager> _turns_manager;
    shared_ptr<RulesManager> _rules_manager;
    shared_ptr<AttrManager> _attr_manager;
    shared_ptr<EventManager> _event_manager;

    // important game events
    boost::signals2::signal<void()> _initialize_pieces;
};


#endif //BGCORE_GAMEMANAGER_H
