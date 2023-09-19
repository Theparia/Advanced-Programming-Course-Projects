#include <iostream>
#include "rsdl.hpp"
#include "Player.hpp"
#include "InputFunctions.hpp"
#include "Game.hpp"

using namespace std;

#define WINDOW_LENGHT 1365
#define WINDOW_WIDTH 1024

typedef vector<int> wave_t;
typedef vector<FPoint> path_t;

int main()
{
    Player player;
    Window *window = new Window(WINDOW_LENGHT, WINDOW_WIDTH, "Field Runners");
    set_background(window);
    vector<string> input = get_input();
    path_t path = get_enemy_path(find_numbers(input[0]));
    vector<wave_t> waves = get_waves(input);
    Game field_runners(path, waves, player);
    field_runners.play(window);
}
