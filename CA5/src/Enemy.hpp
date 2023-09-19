#ifndef ENEMY_H
#define ENEMY_H "ENEMY_H"

#include "coordinates.hpp"
#include <vector>
#include <string>

typedef std::vector<FPoint> path_t;

class Enemy
{
public:
    Enemy(FPoint position_, FPoint next_position_, int hearts_, float velocity_, int being_killed_coins_, int player_reduced_hearts_);
    int get_player_reduced_hearts();
    int get_being_killed_coins();
    int get_hearts();
    int get_velocity();
    FPoint get_position();
    virtual void print_photo(Window *window, const path_t &path,int frame,std::string direction) = 0;
    bool is_stubborn_runner();
    void set_hearts(int wave);
    void get_hurt(int damage);
    void move_up();
    void move_down();
    void move_vertical(FPoint next_position,Window *window, const path_t &path,int frame);
    void move_right();
    void move_left();
    void move_horizontal(FPoint next_position,Window *window, const path_t &path,int frame);
    void move(Window *window, const path_t &path,int frame);
    bool has_reached_end(const path_t &path);
    bool is_alive();
    bool is_dead();
    void set_velocity(int velocity_);
    void draw_hearts(Window *window, int wave);
    void check_if_is_effected_by_glue(int frame);
    void effect_by_glue(int frame,float reduce_velocity_percent,int effection_duration);
    bool is_effected();

protected:
    FPoint next_position;
    FPoint position;
    float hearts;
    float velocity;
    int being_killed_coins;
    int player_reduced_hearts;
    float get_initial_hearts(int wave);
    float get_initial_velocity();
    int being_free_frame;
    bool is_effected_by_glue;
};

#endif