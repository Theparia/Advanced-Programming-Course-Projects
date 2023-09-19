#ifndef TESLA_h
#define TESLA_h "TESLA_h"

#include "Tower.hpp"
#include <vector>

class Tesla : public Tower
{
public:
    Tesla(Point pos);
    void print_photo(Window *window);
    void shoot_target(const std::vector<Enemy *> &field_runners, Window *window, int frame);
    void upgrade();
    void hurt_enemy(Enemy* enemy,int frame);
};

#endif