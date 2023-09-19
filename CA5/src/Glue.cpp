#include "Glue.hpp"
#include <sstream>
#include "Enemy.hpp"

using namespace std;

#define DAMAGE 0
#define INTERVAL 2000
#define CONSTRUCTION_COST 60
#define UPGRADE_COST 45
#define ADDITION_DAMAGE 0
#define DELAY 10
#define REDUCE_SPEED 0.4
#define DURATION 2500
#define REDUCE_SPEED_ADDITION 0.1
#define DURATION_ADDITION 500
#define GLUE_ADDRESS "assets/glue"

typedef vector<Enemy *> enemies_t;

Glue::Glue(Point pos)
    : Tower(DAMAGE, INTERVAL, CONSTRUCTION_COST, UPGRADE_COST, pos, ADDITION_DAMAGE)
{
    reduce_speed_percent = REDUCE_SPEED;
    impression_duration = DURATION;
}
void Glue::print_photo(Window *window)
{
    ostringstream file_name;
    file_name << GLUE_ADDRESS << power << ".png";
    window->draw_img(file_name.str(), Rectangle(position - Point(40, 40), 80, 80), NULL_RECT);
}
void Glue::shoot_target(const enemies_t &field_runners, Window *window, int frame)
{
    static bool is_time_to_attack;
    if (frame % (INTERVAL / DELAY) == 0 && frame != 0)
    {
        update_bullet(field_runners);
        is_time_to_attack = true;
    }
    if (is_time_to_attack)
    {
        shoot_bullet(is_time_to_attack, window, field_runners, frame);
    }
}
void Glue::upgrade()
{
    reduce_speed_percent += REDUCE_SPEED_ADDITION;
    impression_duration += DURATION_ADDITION;
    if (power == Middle)
        power = High;
    if (power == Low)
        power = Middle;
}
void Glue::hurt_enemy(Enemy *enemy, int frame)
{
    if (!enemy->is_effected())
        enemy->effect_by_glue(frame, reduce_speed_percent, impression_duration / DELAY);
}