#ifndef STUBBORN_RUNNER_H
#define STUBBORN_RUNNER_H "STUBBORN_RUNNER_H"

#include "rsdl.hpp"
#include "coordinates.hpp"
#include <vector>
#include "Enemy.hpp"
#include <string>

typedef std::vector<FPoint> path_t;

class StubbornRunner : public Enemy
{
public:
    StubbornRunner(FPoint current, FPoint next);
    virtual void print_photo(Window *window,const path_t &path,int frame,std::string direction);
};

#endif