#ifndef RUNNER_H
#define RUNNER_H "RUNNER_H"

#include "rsdl.hpp"
#include "coordinates.hpp"
#include <vector>
#include "Enemy.hpp"

typedef std::vector<FPoint> path_t;

class Runner : public Enemy
{
public:
    Runner(FPoint current, FPoint next);
    void print_photo(Window *window, const path_t &path,int frame,std::string direction);
};

#endif