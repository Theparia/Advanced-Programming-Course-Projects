#ifndef INPUT_H
#define INPUT_H "INPUT_H"

#include <vector>
#include <string>
#include "coordinates.hpp"

typedef std::vector<int> wave_t;
typedef std::vector<FPoint> path_t;

std::vector<std::string> get_parsed_data(std::string data_line, char delimiter);
std::vector<int> find_numbers(std::string line);
path_t get_enemy_path(std::vector<int> numbers);
std::vector<wave_t> get_waves(std::vector<std::string> data);
std::vector<std::string> get_input();
void set_background(Window *window);

#endif
