#include "Enemy.hpp"

using namespace std;

#define DELAY 10
#define ONE_SECOND 1000
#define MIN_DISTANCE 2
#define RUNNER_COINS 6
#define STUBBORN_RUNNER_COINS 10
#define SUPER_TROOPER_COINS 8
#define SCRAMBLER_COINS 4
#define RUNNER_VELOCITY 50
#define STUBBORN_RUNNER_VELOCITY 30
#define SUPER_TROOPER_VELOCITY 25
#define SCRAMBLER_VELOCITY 90
#define RUNNER_HEARTS 250
#define STUBBORN_RUNNER_HEARTS 400
#define SUPER_TROOPER_HEARTS 500
#define SCRAMBLER_HEARTS 100
#define UP "up"
#define DOWN "down"
#define RIGHT "right"
#define LEFT "left"

typedef vector<FPoint> path_t;

Enemy::Enemy(FPoint position_, FPoint next_position_, int hearts_, float velocity_, int being_killed_coins_, int player_reduced_hearts_)
{
    position = position_;
    next_position = next_position_;
    hearts = hearts_;
    velocity = velocity_;
    being_killed_coins = being_killed_coins_;
    player_reduced_hearts = player_reduced_hearts_;
    being_free_frame = false;
}
int Enemy::get_player_reduced_hearts() { return player_reduced_hearts; }
int Enemy::get_being_killed_coins() { return being_killed_coins; }
int Enemy::get_hearts() { return hearts; }
int Enemy::get_velocity() { return velocity; }
FPoint Enemy::get_position() { return position; }
bool Enemy::is_stubborn_runner()
{
    if (being_killed_coins == STUBBORN_RUNNER_COINS)
        return true;
    return false;
}
void Enemy::get_hurt(int damage)
{
    hearts -= damage;
}
float Enemy::get_initial_velocity()
{
    int init_velocity;
    switch (being_killed_coins)
    {
    case RUNNER_COINS:
        init_velocity = RUNNER_VELOCITY;
        break;
    case STUBBORN_RUNNER_COINS:
        init_velocity = STUBBORN_RUNNER_VELOCITY;
        break;
    case SUPER_TROOPER_COINS:
        init_velocity = SUPER_TROOPER_VELOCITY;
        break;
    case SCRAMBLER_COINS:
        init_velocity = SCRAMBLER_VELOCITY;
        break;
    }
    return init_velocity;
}
void Enemy::move_down()
{
    position += FPoint(0, velocity * DELAY / ONE_SECOND);
}
void Enemy::move_up()
{
    position -= FPoint(0, velocity * DELAY / ONE_SECOND);
}
void Enemy::move_vertical(FPoint next_position, Window *window, const vector<FPoint> &path, int frame)
{
    if (position.y < next_position.y)
    {
        move_down();
        print_photo(window, path, frame, DOWN);
    }
    if (position.y > next_position.y)
    {
        move_up();
        print_photo(window, path, frame, UP);
    }
}
void Enemy::move_right()
{
    position += FPoint(velocity * DELAY / ONE_SECOND, 0);
}
void Enemy::move_left()
{
    position -= FPoint(velocity * DELAY / ONE_SECOND, 0);
}

void Enemy::move_horizontal(FPoint next_position, Window *window, const vector<FPoint> &path, int frame)
{
    if (position.x < next_position.x)
    {
        move_right();
        print_photo(window, path, frame, RIGHT);
    }
    if (position.x > next_position.x)
    {
        move_left();
        print_photo(window, path, frame, LEFT);
    }
}
bool Enemy::has_reached_end(const path_t &path)
{
    return is_equal(position, path[path.size() - 1]);
}
void Enemy::move(Window *window, const vector<FPoint> &path, int frame)
{
    if (get_distance(position, next_position) < MIN_DISTANCE)
    {
        position.x = next_position.x;
        position.y = next_position.y;
        next_position = find_dst(path, position);
    }
    if (position.x == next_position.x)
        move_vertical(next_position, window, path, frame);
    if (position.y == next_position.y)
        move_horizontal(next_position, window, path, frame);
}
bool Enemy::is_alive()
{
    if (hearts > 0)
        return true;
    return false;
}
bool Enemy::is_dead()
{
    if (hearts <= 0)
        return true;
    return false;
}
void Enemy::set_hearts(int wave)
{
    hearts = (0.9 + 0.1 * wave) * hearts;
}
void Enemy::set_velocity(int velocity_)
{
    velocity = velocity_;
}
float Enemy::get_initial_hearts(int wave)
{
    int init_hearts;
    switch (being_killed_coins)
    {
    case RUNNER_COINS:
        init_hearts = RUNNER_HEARTS;
        break;
    case STUBBORN_RUNNER_COINS:
        init_hearts = STUBBORN_RUNNER_HEARTS;
        break;
    case SUPER_TROOPER_COINS:
        init_hearts = SUPER_TROOPER_HEARTS;
        break;
    case SCRAMBLER_COINS:
        init_hearts = SCRAMBLER_HEARTS;
        break;
    }
    return (0.9 + 0.1 * wave) * init_hearts;
}

void Enemy::draw_hearts(Window *window, int wave)
{
    float width = (hearts / get_initial_hearts(wave)) * 45;
    window->fill_rect(Rectangle(to_point(position) - Point(25, 33), int(width), 6), RGB(5, 102, 8));
    window->fill_rect(Rectangle(to_point(position) - Point(25, 33) + Point(int(width), 0), 45 - int(width), 6), RGB(191, 10, 48));
}
void Enemy::check_if_is_effected_by_glue(int frame)
{
    if (is_effected_by_glue)
    {
        if (frame > being_free_frame)
        {
            velocity = get_initial_velocity();
            is_effected_by_glue = false;
        }
    }
}
void Enemy::effect_by_glue(int frame, float reduce_velocity_percent, int effection_duration)
{
    is_effected_by_glue = true;
    being_free_frame = frame + effection_duration;
    velocity *= (1 - reduce_velocity_percent);
}
bool Enemy::is_effected()
{
    return is_effected_by_glue;
}