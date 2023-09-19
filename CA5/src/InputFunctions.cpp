#include "InputFunctions.hpp"
#include <sstream>
#include <cstdlib>

using namespace std;

#define CENTER_OF_FIRST_HOUSE_X 153
#define CENTER_OF_FIRST_HOUSE_Y 206
#define HOUSE_LENGTH 60

typedef vector<int> wave_t;
typedef vector<FPoint> path_t;

vector<string> get_parsed_data(string data_line, char delimiter)
{
    string line;
    vector<string> data;
    stringstream file(data_line);
    while (getline(file, line, delimiter))
    {
        data.push_back(line);
    }
    return data;
}
vector<int> find_numbers(string line)
{
    vector<int> numbers;
    vector<string> temp = get_parsed_data(line, ' ');
    for (int i = 0; i < temp.size(); i++)
    {
        numbers.push_back(stoi(temp[i].c_str()));
    }
    return numbers;
}
path_t get_enemy_path(vector<int> numbers)
{
    path_t positions;
    for (int i = 1; i < numbers.size(); i += 2)
    {
        positions.push_back(FPoint(numbers[i - 1] * HOUSE_LENGTH + CENTER_OF_FIRST_HOUSE_X, numbers[i] * HOUSE_LENGTH + CENTER_OF_FIRST_HOUSE_Y));
    }

    return positions;
}
vector<wave_t> get_waves(vector<string> data)
{
    vector<wave_t> waves;
    for (int i = 1; i < data.size(); i++)
    {
        vector<int> temp = find_numbers(data[i]);
        waves.push_back(temp);
    }
    return waves;
}

vector<string> get_input()
{
    string input;
    vector<string> data;
    while (getline(cin, input))
        data.push_back(input);
    return data;
}
void set_background(Window *window)
{
    window->draw_img("assets/background.png", NULL_RECT, NULL_RECT);
    window->update_screen();
}
