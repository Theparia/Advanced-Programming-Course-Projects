#ifndef SCRAMBLER_H
#define SCRAMBLER_H " SCRAMBLER_H"

#include "rsdl.hpp"
#include "coordinates.hpp"
#include <vector>
#include "Enemy.hpp"
#include <string>

typedef std::vector<FPoint> path_t;

class Scrambler : public Enemy
{
public:
    Scrambler(FPoint current, FPoint next);
    void print_photo(Window *window,const path_t &path,int frame,std::string direction);
};

#endif