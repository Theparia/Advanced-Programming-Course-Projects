#include "Game.hpp"
#include "Runner.hpp"
#include "Scrambler.hpp"
#include "StubbornRunner.hpp"
#include "SuperTrooper.hpp"
#include <algorithm>
#include "Event.hpp"
#include <iostream>

using namespace std;

#define HOUSE_LENGHT 60
#define INTERVAL_PER_ENEMY 500
#define DELAY 10
#define INTERVAL_PER_WAVE 3000
#define FONT_SIZE 200
#define YOU_LOSE "YOU LOSE!"
#define YOU_WON "YOU WON!"
#define CIRCLE_ADDRESS "assets/circle.png"
#define BACKGROUND_ADDRESS "assets/background.png"
#define FONT_ADDRESS "assets/OpenSans.ttf"
#define MUSIC_ADDRESS "assets/Grasslands.mp3"

typedef vector<FPoint> path_t;
typedef vector<int> wave_t;

Game::Game(const path_t &path_, const vector<wave_t> &waves_, Player player_)
{
    path = path_;
    waves = waves_;
    player = player_;
}
void Game::find_path(FPoint src, FPoint dst, path_t &road)
{
    while (src.x == dst.x && src.y < dst.y)
    {
        road.push_back(FPoint(src.x, src.y));
        src.y += HOUSE_LENGHT;
    }
    while (src.y == dst.y && src.x < dst.x)
    {
        road.push_back(FPoint(src.x, src.y));
        src.x += HOUSE_LENGHT;
    }
    while (src.x == dst.x && src.y > dst.y)
    {
        road.push_back(FPoint(src.x, src.y));
        src.y -= HOUSE_LENGHT;
    }
    while (src.y == dst.y && src.x > dst.x)
    {
        road.push_back(FPoint(src.x, src.y));
        src.x -= HOUSE_LENGHT;
    }
}
path_t Game::find_road()
{
    path_t road;
    for (int i = 0; i < path.size() - 1; i++)
    {
        find_path(path[i], path[i + 1], road);
    }
    road.push_back(path[path.size() - 1]);
    return road;
}
void Game::set_default_targets(Enemy *enemy)
{
    for (int i = 0; i < player.get_towers().size(); i++)
    {
        player.get_towers()[i]->set_target(enemy);
    }
}
void Game::draw_path(Window *window)
{
    for (int i = 0; i < find_road().size(); i++)
    {
        window->draw_img(CIRCLE_ADDRESS, Rectangle(to_point(find_road()[i]) - Point(22, 22), 40, 40), NULL_RECT);
    }
}
void Game::set_background(Window *window)
{
    window->draw_img(BACKGROUND_ADDRESS, NULL_RECT, NULL_RECT);
}
void Game::add_runners(int number)
{
    for (int i = 0; i < number; i++)
    {
        Runner *runner = new Runner(path[0], path[1]);
        enemies.push_back(runner);
    }
}
void Game::add_stubborn_runners(int number)
{
    for (int i = 0; i < number; i++)
    {
        StubbornRunner *stubborn_runner = new StubbornRunner(path[0], path[1]);
        enemies.push_back(stubborn_runner);
    }
}
void Game::add_scramblers(int number)
{
    for (int i = 0; i < number; i++)
    {
        Scrambler *scrambler = new Scrambler(path[0], path[1]);
        enemies.push_back(scrambler);
    }
}
void Game::add_super_troopers(int number)
{
    for (int i = 0; i < number; i++)
    {
        SuperTrooper *super_trooper = new SuperTrooper(path[0], path[1]);
        enemies.push_back(super_trooper);
    }
}
void Game::add_enemies(int number, int type)
{
    switch (type)
    {
    case 0:
        add_runners(number);
        break;
    case 1:
        add_stubborn_runners(number);
        break;
    case 2:
        add_super_troopers(number);
        break;
    case 3:
        add_scramblers(number);
        break;
    }
}
void Game::move_single_enemy(Window *window, Enemy *enemy, int wave, int frame)
{
    if (enemy->has_reached_end(path) || !enemy->is_alive())
    {
        if (!enemy->is_alive())
        {
            player.add_coins(enemy->get_being_killed_coins());
        }
        else
        {
            player.reduce_hearts(enemy->get_player_reduced_hearts());
            enemy->get_hurt(enemy->get_hearts());
        }
        field_runners.erase(find(field_runners.begin(), field_runners.end(), enemy));
    }
    else
    {
        enemy->check_if_is_effected_by_glue(frame);
        enemy->move(window, path, frame);
        enemy->draw_hearts(window, wave);
    }
}
void Game::draw_enemies(Window *window, int wave, int frame)
{
    for (int i = 0; i < field_runners.size(); i++)
    {
        move_single_enemy(window, field_runners[i], wave, frame);
    }
}
void Game::enter_enemies(int frame, vector<int> &indexes)
{
    srand(time(0));
    int index = rand() % (enemies.size());

    if ((frame % (INTERVAL_PER_ENEMY / DELAY) == 0) && frame != 0 && ((frame / (INTERVAL_PER_ENEMY / DELAY)) < enemies.size()))
    {
        while (find(indexes.begin(), indexes.end(), index) != indexes.end())
        {
            index = rand() % (enemies.size());
        }
        indexes.push_back(index);
        field_runners.push_back(enemies[index]);
    }
}
void Game::draw_bullets(Window *window, int frame)
{
    for (int i = 0; i < player.get_towers().size(); i++)
    {
        player.get_towers()[i]->shoot_target(field_runners, window, frame);
    }
}
bool Game::is_wave_finished(const vector <int> &indexes)
{
    if (field_runners.size() == 0 && indexes.size()==enemies.size())
        return true;
    return false;
}
void Game::check_if_player_lost(Window *window)
{
    if (player.get_hearts() <= 0)
    {
        window->show_text(YOU_LOSE, Point(150, 400), RED, FONT_ADDRESS, FONT_SIZE);
        window->update_screen();
        delay(INTERVAL_PER_WAVE);
        exit(0);
    }
}
void Game::check_if_player_won(Window *window)
{
    window->show_text(YOU_WON, Point(150, 400), RED, FONT_ADDRESS, FONT_SIZE);
    window->update_screen();
    delay((INTERVAL_PER_WAVE));
    exit(0);
}
void Game::update(Window *window, vector<int> &indexes, int wave)
{
    int frame = 0;
    while (true)
    {
        enter_enemies(frame, indexes);
        process_event(window, player, field_runners[0]);
        if (is_wave_finished(indexes))
            break;
        window->clear();
        set_background(window);
        draw_path(window);
        player.show_towers(window);
        draw_enemies(window, wave, frame);
        draw_bullets(window, frame);
        player.show_info(window);
        check_if_player_lost(window);
        window->update_screen();
        delay(DELAY);
        frame++;
    }
}
void Game::set_enemies_hearts(int number_of_wave)
{
    for (int i = 0; i < enemies.size(); i++)
        enemies[i]->set_hearts(number_of_wave);
}
void Game::play(Window *window)
{
    window->play_music(MUSIC_ADDRESS);
    srand(time(0));
    vector<int> indexes;
    for (int i = 0; i < waves.size(); i++)
    {
        enemies.clear();
        field_runners.clear();
        indexes.clear();
        for (int j = 0; j < waves[i].size(); j++)
            add_enemies(waves[i][j], j);
        set_enemies_hearts(i + 1);
        int index = rand() % (enemies.size());
        field_runners.push_back(enemies[index]);
        indexes.push_back(index);
        set_default_targets(field_runners[0]);
        update(window, indexes, i + 1);
        if (i != waves.size() - 1)
            delay((INTERVAL_PER_WAVE));
    }
    check_if_player_won(window);
}
