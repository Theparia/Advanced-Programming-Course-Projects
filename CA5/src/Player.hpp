#ifndef PLAYER_H
#define PLAYER_H "PLAYER_H"

#include "Tower.hpp"
#include <vector>
class Enemy;
class Player
{
private:
    int hearts;
    int coins;
    std::vector<Tower *> towers;

public:
    Player();
    int get_hearts();
    int get_coins();
    void add_coins(int reward);
    void reduce_hearts(int damage);
    bool can_efford(int cost);
    std::vector<Tower *> get_towers();
    Tower *find_tower_by_point(Point pos);
    void pay_cost(int cost);
    virtual void buy_tower(Tower *tower);
    void add_glue(Point pos, Enemy *enemy);
    void add_gatling(Point pos, Enemy *enemy);
    void add_missile(Point pos, Enemy *enemy);
    void add_tesla(Point pos, Enemy *enemy);
    void upgrade_tower(Point pos);
    virtual void build_towers(Point pos, char tower_type, Enemy *enemy);
    void show_towers(Window *window);
    void show_info(Window *window);
};
#endif