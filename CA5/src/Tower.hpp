#ifndef TOWER_H
#define TOWER_H "TOWER_H"

#include "rsdl.hpp"
#include "coordinates.hpp"
#include <vector>
#include "Bullet.hpp"

typedef std::vector<Enemy *> enemies_t;

enum towerPower
{
    Low = 1,
    Middle = 2,
    High = 3
};
class Enemy;
class Tower
{
public:
    Tower(int damage_, int interval_per_attack_, int construction_cost_, int upgrade_cost_, Point position_, int addition_damage_);
    virtual void shoot_target(const enemies_t &field_runners, Window *window, int frame) = 0;
    int get_interval_per_attack();
    towerPower get_power();
    virtual void print_photo(Window *window) = 0;
    Point get_position();
    int get_construction_cost();
    int get_upgrade_cost();
    void set_range(int range_);
    virtual void upgrade() = 0;
    void set_target(Enemy *enemy);
    void update_bullet(const enemies_t &field_runners);
    void find_target(const enemies_t &field_runners);
    bool contains_enemy(const enemies_t &field_runners);
    float get_distance_from_target(FPoint target_pos);
    bool contains_range(FPoint target_pos);
    bool is_target_available();
    bool is_shooting_neutral();
    void hurt_enemies_around_missile(const enemies_t &field_runners, int frame);
    void hurt_enemies_around_glue(const enemies_t &field_runners, int frame);
    void shoot_bullet(bool &turn, Window *window, const enemies_t &field_runners, int frame);
    virtual void hurt_enemy(Enemy *enemy, int frame) = 0;

protected:
    int range;
    Enemy *target;
    Point position;
    int damage;
    int interval_per_attack;
    int construction_cost;
    int upgrade_cost;
    int addition_damage;
    towerPower power;
    Bullet bullet;
    bool is_gatling();
    bool is_missile();
    bool is_glue();
};

#endif