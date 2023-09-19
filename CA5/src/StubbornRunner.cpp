#include "StubbornRunner.hpp"

using namespace std;

#define INITIAL_HEARTS 400
#define VELOCITY 30
#define KILLING_REWARD 10
#define REDUCED_HEARTS 4
#define STUBBORN_RUNNER_ADDRESS "assets/stubborn-runner-"

typedef vector<FPoint> path_t;

StubbornRunner::StubbornRunner(FPoint current, FPoint next)
    : Enemy(current, next, INITIAL_HEARTS, VELOCITY, KILLING_REWARD, REDUCED_HEARTS) {}

void StubbornRunner::print_photo(Window *window, const path_t &path, int frame, string direction)
{
    static int condition = 0;
    if (frame % 15 == 0)
        condition++;
    if (!has_reached_end(path) && is_alive())
        window->draw_img(STUBBORN_RUNNER_ADDRESS + direction + "-" + to_string(condition % 6) + ".png", Rectangle(to_point(position) - Point(30, 30), 53, 50), NULL_RECT);
}