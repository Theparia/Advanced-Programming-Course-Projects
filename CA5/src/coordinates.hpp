#ifndef COORDINATES_H
#define COORDINATES_H "COORDINATES_H"

#include <vector>
#include "rsdl.hpp"

struct FPoint
{
    float x;
    float y;
    FPoint() {}
    FPoint(float x_, float y_);

    FPoint operator+(FPoint p);
    FPoint operator-(FPoint p);
    FPoint operator+=(FPoint p);
    FPoint operator-=(FPoint p);
};
float get_distance(FPoint src, FPoint dst);
bool is_equal(FPoint a, FPoint b);
Point to_point(FPoint fpoint);
FPoint to_fpoint(Point point);
FPoint find_dst(const std::vector<FPoint> &path, FPoint current_pos);
Point find_center(Point point);


#endif