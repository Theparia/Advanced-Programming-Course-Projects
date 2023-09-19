#include "Bullet.hpp"
#include "Enemy.hpp"

using namespace std;

#define BULLET_SPEED 200
#define DELAY 10
#define ONE_SECOND 1000
#define MIN_DISTANCE 1
#define BULLET_ADDRESS "assets/fireball.png"

Bullet::Bullet()
{
    velocity = BULLET_SPEED;
}
void Bullet::draw_bullet(Window *window, FPoint towerdst)
{
    if (!is_equal(position, towerdst))
    window->draw_img(BULLET_ADDRESS,Rectangle(to_point(position)-Point(10,10),20,20),NULL_RECT);
}
void Bullet::move_vertical(Enemy *target)
{
    if (target->get_position().y < position.y)
        position.y -= (velocity*DELAY / ONE_SECOND) * (position.y - target->get_position().y) / get_distance(target->get_position(), position);
    else if (target->get_position().y > position.y)
        position.y += (velocity*DELAY /ONE_SECOND) * (target->get_position().y - position.y) / get_distance(target->get_position(), position);
    else
        position.y += 0;
}
void Bullet::move_horizontal(Enemy *target)
{
    if (target->get_position().x < position.x)
        position.x -= (velocity*DELAY / ONE_SECOND) * (position.x - target->get_position().x) / get_distance(target->get_position(), position);
    else if (target->get_position().x > position.x)
        position.x += (velocity*DELAY /ONE_SECOND) * (target->get_position().x - position.x) / get_distance(target->get_position(), position);
    else
        position.x += 0;
}
bool Bullet::has_reached_target(Enemy *target)
{
    return get_distance(position, target->get_position()) < MIN_DISTANCE;
}

void Bullet::move(Enemy *target, int damage, int interval_per_attack)
{
    move_vertical(target);
    move_horizontal(target);
}

FPoint Bullet::get_position() { return position; }
void Bullet::set_position(FPoint new_position) { position = new_position; }