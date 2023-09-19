#ifndef GATLING_H
#define GATLING_H "GATLING_H"

#include "Tower.hpp"
#include <vector>

typedef std::vector<Enemy *> enemies_t;

class Gatling : public Tower
{
public:
    Gatling(Point pos);
    void print_photo(Window *window);
    void shoot_target(const enemies_t &field_runners, Window *window, int frame);
    void upgrade();
    void hurt_enemy(Enemy* enemy,int frame);
};

#endif