#ifndef MISSILE_H
#define MISSILE_H "MISSILE_H"

#include "Tower.hpp"
#include <vector>

typedef std::vector<Enemy *> enemies_t;

class Missile : public Tower
{
public:
     Missile(Point pos);
     void print_photo(Window *window);
     void shoot_target(const enemies_t &field_runners, Window *window, int frame);
     void upgrade();
     void hurt_enemy(Enemy* enemy,int frame);
};

#endif