#include "Gatling.hpp"
#include <sstream>
#include "Enemy.hpp"

using namespace std;

#define DAMAGE 35
#define INTERVAL 1000
#define CONSTRUCTION_COST 55
#define UPGRADE_COST  40
#define ADDITION_DAMAGE  35
#define DELAY 10
#define GATLING_ADDRESS "assets/gattling"

typedef vector<Enemy *> enemies_t;

Gatling::Gatling(Point pos)
    : Tower(DAMAGE, INTERVAL,CONSTRUCTION_COST,UPGRADE_COST, pos,ADDITION_DAMAGE) {}
void Gatling::print_photo(Window *window)
{
    ostringstream file_name;
    file_name << GATLING_ADDRESS << power << ".png";
    window->draw_img(file_name.str(), Rectangle(position - Point(40, 30), 80, 80), NULL_RECT);
}
void Gatling::shoot_target(const enemies_t &field_runners, Window *window, int frame)
{
    static bool is_time_to_attack;
    if (frame % (INTERVAL/DELAY) == 0 && frame != 0)
    {
        update_bullet(field_runners);
        is_time_to_attack = true;
    }
    if (is_time_to_attack)
    {
        shoot_bullet(is_time_to_attack, window, field_runners,frame);
    }
}
void Gatling::upgrade()
{
    damage += addition_damage;
    if (power == Middle)
        power = High;
    if (power == Low)
        power = Middle;
}
void Gatling::hurt_enemy(Enemy* enemy,int frame)
{
    enemy->get_hurt(damage);
}