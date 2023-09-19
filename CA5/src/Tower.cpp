#include "Tower.hpp"
#include "Enemy.hpp"

using namespace std;

#define RANGE 150
#define MISSILE_RANGE 50
#define GATLING_INTERVAL 1000
#define MISSILE_INTERVAL 3000
#define GLUE_INTERVAL 2000
#define GLUE_RANGE 30

typedef vector<Enemy *> enemies_t;

Tower::Tower(int damage_, int interval_per_attack_, int construction_cost_, int upgrade_cost_, Point position_, int addition_damage_)
{
    range = RANGE;
    power = Low;
    damage = damage_;
    interval_per_attack = interval_per_attack_;
    construction_cost = construction_cost_;
    upgrade_cost = upgrade_cost_;
    position = position_;
    addition_damage = addition_damage_;
    bullet.set_position(to_fpoint(position_));
}
int Tower::get_interval_per_attack() { return interval_per_attack; }
towerPower Tower::get_power() { return power; }
Point Tower::get_position() { return position; }
int Tower::get_construction_cost() { return construction_cost; }
int Tower::get_upgrade_cost() { return upgrade_cost; }
void Tower::set_range(int range_) { range = range_; }
void Tower::set_target(Enemy *enemy)
{
    target = enemy;
}
void Tower::update_bullet(const enemies_t &field_runners)
{
    bullet.set_position(to_fpoint(position));
    if (!is_target_available() && contains_enemy(field_runners))
        find_target(field_runners);
}
void Tower::find_target(const enemies_t &field_runners)
{
    for (int i = 0; i < field_runners.size(); i++)
    {
        if (contains_range(field_runners[i]->get_position()) &&
            get_distance_from_target(field_runners[i]->get_position()) < get_distance_from_target(target->get_position()))
            target = field_runners[i];
    }
}
bool Tower::contains_enemy(const enemies_t &field_runners)
{
    for (int i = 0; i < field_runners.size(); i++)
    {
        if (contains_range(field_runners[i]->get_position()))
            return true;
    }
    return false;
}
float Tower::get_distance_from_target(FPoint target_pos)
{
    return sqrt((target_pos.x - position.x) * (target_pos.x - position.x) + (target_pos.y - position.y) * (target_pos.y - position.y));
}
bool Tower::contains_range(FPoint target_pos)
{
    float distance = get_distance_from_target(target_pos);
    if (distance <= range)
        return true;
    else
        return false;
}
bool Tower::is_target_available()
{
    return (target->is_alive() && contains_range(target->get_position()));
}
bool Tower::is_gatling()
{
    if (interval_per_attack == GATLING_INTERVAL)
        return true;
    return false;
}
bool Tower::is_missile()
{
    if (interval_per_attack == MISSILE_INTERVAL)
        return true;
    return false;
}
bool Tower::is_glue()
{
    if (interval_per_attack == GLUE_INTERVAL)
        return true;
    return false;
}
bool Tower::is_shooting_neutral()
{
    if ((is_gatling() || is_glue()) && target->is_stubborn_runner())
        return true;
    return false;
}
void Tower::hurt_enemies_around_missile(const enemies_t &field_runners, int frame)
{
    for (int i = 0; i < field_runners.size(); i++)
    {
        if (get_distance(target->get_position(), field_runners[i]->get_position()) <= MISSILE_RANGE)
            hurt_enemy(field_runners[i], frame);
    }
}
void Tower::hurt_enemies_around_glue(const enemies_t &field_runners, int frame)
{
    for (int i = 0; i < field_runners.size(); i++)
    {
        if (get_distance(target->get_position(), field_runners[i]->get_position()) <= GLUE_RANGE && !field_runners[i]->is_stubborn_runner())
            hurt_enemy(field_runners[i], frame);
    }
}
void Tower::shoot_bullet(bool &turn, Window *window, const enemies_t &field_runners, int frame)
{
    if (is_target_available())
    {
        if (bullet.has_reached_target(target))
        {
            turn = false;
            if (is_missile())
                hurt_enemies_around_missile(field_runners, frame);
            else if (is_glue())
                hurt_enemies_around_glue(field_runners, frame);
            else if (!is_shooting_neutral())
                hurt_enemy(target, frame);
        }
        bullet.move(target, damage, interval_per_attack);
        bullet.draw_bullet(window, to_fpoint(position));
    }
}