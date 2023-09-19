#include "Scrambler.hpp"

using namespace std;

#define INITIAL_HEARTS 100
#define VELOCITY 90
#define KILLING_REWARD 4
#define REDUCED_HEARTS 2
#define SCRAMBLER_ADDRESS "assets/scrambler-"

typedef vector<FPoint> path_t;

Scrambler::Scrambler(FPoint current, FPoint next)
    : Enemy(current, next, INITIAL_HEARTS, VELOCITY, KILLING_REWARD, REDUCED_HEARTS) {}
void Scrambler::print_photo(Window *window, const path_t &path, int frame, string direction)
{
    static int condition = 0;
    if (frame % 15 == 0)
        condition++;
    if (!has_reached_end(path) && is_alive())
        window->draw_img(SCRAMBLER_ADDRESS + direction + "-" + to_string(condition % 4) + ".png", Rectangle(to_point(position) - Point(30, 30), 50,50), NULL_RECT);
}