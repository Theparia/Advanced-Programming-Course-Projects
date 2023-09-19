#include "Runner.hpp"

using namespace std;

#define INITIAL_HEARTS 250
#define VELOCITY 50
#define KILLING_REWARD 6
#define REDUCED_HEARTS 1
#define RUNNER_ADDRESS "assets/runner-"

typedef vector<FPoint> path_t;

Runner::Runner(FPoint current, FPoint next)
    : Enemy(current,next, INITIAL_HEARTS, VELOCITY, KILLING_REWARD, REDUCED_HEARTS) {}

void Runner::print_photo(Window *window,const path_t &path,int frame,string direction)
{
    static int condition=0;
    if(frame%15==0)
    condition++;
    if (!has_reached_end(path) && is_alive())
    {
        window->draw_img(RUNNER_ADDRESS+direction+"-"+to_string(condition%6)+".png",Rectangle(to_point(position) - Point(20, 30), 40, 50), NULL_RECT);
    }
}