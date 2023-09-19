#include "Tesla.hpp"
#include <sstream>
#include "Enemy.hpp"

using namespace std;

#define DAMAGE 700
#define INTERVAL 1500
#define CONSTRUCTION_COST 120
#define UPGRADE_COST  100
#define ADDITION_DAMAGE  1000
#define DELAY 10
#define TESLA_ADDRESS "assets/tesla"

typedef vector<Enemy *> enemies_t;

Tesla::Tesla(Point pos)
    : Tower(DAMAGE, INTERVAL,CONSTRUCTION_COST,UPGRADE_COST, pos,ADDITION_DAMAGE) {}
void Tesla::print_photo(Window *window)
{
    ostringstream file_name;
    file_name << TESLA_ADDRESS << power << ".png";
    window->draw_img(file_name.str(), Rectangle(position - Point(35, 28), 70, 70), NULL_RECT);
}
void Tesla::shoot_target(const enemies_t &field_runners, Window *window, int frame)
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
void Tesla::upgrade()
{
    damage += addition_damage;
    if (power == Middle)
        power = High;
    if (power == Low)
        power = Middle;
}
void Tesla::hurt_enemy(Enemy* enemy,int frame)
{
    enemy->get_hurt(damage);
}