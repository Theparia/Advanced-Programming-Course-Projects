#ifndef EVENT_H
#define EVENT_H "EVENT_H"

#include "rsdl.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

void process_event(Window *window, Player &player, Enemy *enemy);

#endif