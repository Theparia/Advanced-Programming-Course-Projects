#ifndef GAME_H
#define GAME_H "GAME_H"

#include <vector>
#include "Enemy.hpp"
#include "Player.hpp"

typedef std::vector<FPoint> path_t;
typedef std::vector<int> wave_t;
typedef std::vector<Enemy *> enemies_t;

class Game
{
private:
    path_t path;
    std::vector<wave_t> waves;
    Player player;
    enemies_t enemies;
    enemies_t field_runners;
    void find_path(FPoint src, FPoint dst, path_t &road);
    path_t find_road();
    void draw_path(Window *window);

public:
    Game(const path_t &path_, const std::vector<wave_t> &waves_, Player player_);
    void set_default_targets(Enemy *enemy);
    void set_background(Window *window);
    void add_enemies(int number, int type);
    void move_single_enemy(Window *window, Enemy *enemy, int wave,int frame);
    void draw_enemies(Window *window, int wave,int frame);
    void enter_enemies(int frame, std::vector<int> &indexes);
    void draw_bullets(Window *window, int frame);
    bool is_wave_finished(const std::vector<int> &indexes);
    void check_if_player_lost(Window *window);
    void update(Window *window, std::vector<int> &indexes, int wave);
    void check_if_player_won(Window *window);
    void play(Window *window);
    void set_enemies_hearts(int number_of_wave);
    void add_runners(int number);
    void add_stubborn_runners(int number);
    void add_super_troopers(int number);
    void add_scramblers(int number);
};

#endif