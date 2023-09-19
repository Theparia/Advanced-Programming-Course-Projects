#include "Player.hpp"
#include "Enemy.hpp"
#include <sstream>
#include "Tesla.hpp"
#include "Missile.hpp"
#include "Gatling.hpp"
#include "Glue.hpp"

using namespace std;

#define INITIAL_HEARTS 20
#define INITIAL_COINS 200
#define FONT_ADDRESS "assets/OpenSans.ttf"
#define COIN_ADDRESS "assets/coin.png"
#define HEART_ADDRESS "assets/heart.png"

Player::Player()
{
    hearts = INITIAL_HEARTS;
    coins = INITIAL_COINS;
}
int Player::get_hearts() { return hearts; }
int Player::get_coins() { return coins; }
vector<Tower *> Player::get_towers() { return towers; }
void Player::add_coins(int reward)
{
    coins += reward;
}
void Player::reduce_hearts(int damage)
{
    hearts -= damage;
}
bool Player::can_efford(int cost)
{
    if (coins - cost >= 0)
        return true;
    return false;
}

Tower *Player::find_tower_by_point(Point pos)
{
    for (int i = 0; i < towers.size(); i++)
    {
        if (find_center(towers[i]->get_position()).x == find_center(pos).x && find_center(towers[i]->get_position()).y == find_center(pos).y)
            return towers[i];
    }
    return NULL;
}
void Player::pay_cost(int cost)
{
    coins -= cost;
}
void Player::buy_tower(Tower *tower)
{
    if (can_efford(tower->get_construction_cost()))
    {
        towers.push_back(tower);
        pay_cost(tower->get_construction_cost());
    }
}
void Player::add_glue(Point pos, Enemy *enemy)
{
    Glue *glue = new Glue(find_center(pos));
    glue->set_target(enemy);
    buy_tower(glue);
}
void Player::add_gatling(Point pos, Enemy *enemy)
{
    Gatling *gatling = new Gatling(find_center(pos));
    gatling->set_target(enemy);
    buy_tower(gatling);
}
void Player::add_missile(Point pos, Enemy *enemy)
{
    Missile *missile = new Missile(find_center(pos));
    missile->set_target(enemy);
    buy_tower(missile);
}
void Player::add_tesla(Point pos, Enemy *enemy)
{
    Tesla *tesla = new Tesla(find_center(pos));
    tesla->set_target(enemy);
    buy_tower(tesla);
}

void Player::upgrade_tower(Point pos)
{
    if (find_tower_by_point(pos) != NULL)
    {
        if (can_efford(find_tower_by_point(pos)->get_upgrade_cost()))
        {
            find_tower_by_point(pos)->upgrade();
            pay_cost(find_tower_by_point(pos)->get_upgrade_cost());
        }
    }
}
void Player::build_towers(Point pos, char tower_type, Enemy *enemy)
{
    switch (tower_type)
    {
    case 'g':
        add_gatling(pos, enemy);
        break;
    case 'm':
        add_missile(pos, enemy);
        break;
    case 't':
        add_tesla(pos, enemy);
        break;
    case 'l':
        add_glue(pos, enemy);
        break;
    case 'u':
        upgrade_tower(pos);
        break;
    }
}
void Player::show_towers(Window *window)
{
    for (int i = 0; i < towers.size(); i++)
        towers[i]->print_photo(window);
}
void Player::show_info(Window *window)
{
    ostringstream hearts_info, coins_info;
    coins_info << ": " << coins;
    hearts_info << ": " << hearts;
    window->show_text(hearts_info.str(), Point(130, 50), WHITE, FONT_ADDRESS, 35);
    window->show_text(coins_info.str(), Point(430, 50), WHITE, FONT_ADDRESS, 35);
    window->draw_img(COIN_ADDRESS, Rectangle(Point(350, 35), 80, 90), NULL_RECT);
    window->draw_img(HEART_ADDRESS, Rectangle(Point(50, 40), 80, 80), NULL_RECT);
}