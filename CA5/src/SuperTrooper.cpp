#include "SuperTrooper.hpp"

using namespace std;

#define INITIAL_HEARTS 500
#define VELOCITY 25
#define KILLING_REWARD 8
#define REDUCED_HEARTS 4
#define SUPER_TROOPER_ADDRESS "assets/supertrooper-"

typedef vector<FPoint> path_t;

SuperTrooper::SuperTrooper(FPoint current, FPoint next)
    : Enemy(current, next, INITIAL_HEARTS, VELOCITY, KILLING_REWARD, REDUCED_HEARTS) {}

void SuperTrooper::print_photo(Window *window, const path_t &path, int frame, string direction)
{
    static int condition = 0;
    if (frame % 15 == 0)
        condition++;
    if (!has_reached_end(path) && is_alive())
        window->draw_img(SUPER_TROOPER_ADDRESS + direction + "-" + to_string(condition % 6) + ".png", Rectangle(to_point(position) - Point(30, 30), 50,50), NULL_RECT);
}