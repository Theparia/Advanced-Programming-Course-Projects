#ifndef BULLET_H
#define BULLET_H "BULLET_H"

#include "coordinates.hpp"
#include "rsdl.hpp"

class Enemy;
class Bullet
{
public:
    Bullet();
    void draw_bullet(Window *window, FPoint towerdst);
    void move_vertical(Enemy *target);
    void move_horizontal(Enemy *target);
    bool has_reached_target(Enemy *target);
    void move(Enemy *target, int damage, int interval_per_attack);
    FPoint get_position();
    void set_position(FPoint new_position);

private:
    FPoint position;
    float velocity;
};

#endif