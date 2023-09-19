#ifndef SUPER_TROOPER_H
#define SUPER_TROOPER_H "SUPER_TROOPER_H"

#include "rsdl.hpp"
#include "coordinates.hpp"
#include <vector>
#include "Enemy.hpp"
#include <string>

typedef std::vector<FPoint> path_t;

class SuperTrooper : public Enemy
{
public:
    SuperTrooper(FPoint current, FPoint next);
    void print_photo(Window *window,const path_t &path,int frame,std::string direction);
};

#endif