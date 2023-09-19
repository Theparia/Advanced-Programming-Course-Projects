#ifndef GLUE_H
#define GLUE_H "GLUE_H"

#include "Tower.hpp"
#include <vector>

typedef std::vector<Enemy *> enemies_t;

class Glue : public Tower
{
private:
    float reduce_speed_percent;
    int impression_duration;

public:
    Glue(Point pos);
    void print_photo(Window *window);
    void shoot_target(const enemies_t &field_runners, Window *window, int frame);
    void upgrade();
    void hurt_enemy(Enemy* enemy,int frame);

};

#endif