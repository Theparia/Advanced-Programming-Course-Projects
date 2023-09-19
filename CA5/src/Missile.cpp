#include "Missile.hpp"
#include <sstream>
#include "Enemy.hpp"

using namespace std;

#define DAMAGE 75
#define INTERVAL 3000
#define CONSTRUCTION_COST 70
#define UPGRADE_COST  60
#define ADDITION_DAMAGE  75
#define DELAY 10
#define MISSILE_ADDRESS "assets/missile"

typedef vector<Enemy *> enemies_t;

Missile::Missile(Point pos)
    : Tower(DAMAGE, INTERVAL,CONSTRUCTION_COST,UPGRADE_COST, pos,ADDITION_DAMAGE) {}
void Missile::print_photo(Window *window)
{
    ostringstream file_name;
    file_name << MISSILE_ADDRESS << power << ".png";
    window->draw_img(file_name.str(), Rectangle(position - Point(40, 40), 80, 80), NULL_RECT);
}
void Missile::shoot_target(const enemies_t &field_runners, Window *window, int frame)
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
void Missile::upgrade()
{
    damage += addition_damage;
    if (power == Middle)
        power = High;
    if (power == Low)
        power = Middle;
}
void Missile:: hurt_enemy(Enemy* enemy,int frame)
{
    enemy->get_hurt(damage);
}