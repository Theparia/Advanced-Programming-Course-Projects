#include "coordinates.hpp"
#include <cmath>

using namespace std;

typedef vector<FPoint> path_t;

#define CENTER_OF_FIRST_HOUSE_X 153
#define CENTER_OF_FIRST_HOUSE_Y 206
#define FIRST_HOUSE_X 123
#define FIRST_HOUSE_Y 176
#define HOUSE_LENGTH 60

FPoint::FPoint(float x_, float y_)
{
    x = x_;
    y = y_;
}
FPoint FPoint::operator+(FPoint p)
{
    return FPoint(roundf((x + p.x) * 10) / 10, roundf((y + p.y) * 10) / 10);
}
FPoint FPoint::operator-(FPoint p)
{
    return FPoint(roundf((x - p.x) * 10) / 10, roundf((y - p.y) * 10) / 10);
}
FPoint FPoint::operator+=(FPoint p)
{
    (*this) = (*this) + p;
    return (*this);
}
FPoint FPoint::operator-=(FPoint p)
{
    (*this) = (*this) - p;
    return (*this);
}
float get_distance(FPoint src, FPoint dst)
{
    return sqrt((src.x - dst.x) * (src.x - dst.x) + (src.y - dst.y) * (src.y - dst.y));
}
bool is_equal(FPoint a, FPoint b)
{
    if ((a.x) == (b.x) && (a.y) == (b.y))
        return true;
    return false;
}
Point to_point(FPoint fpoint)
{
    Point point;
    point.x = int(fpoint.x);
    point.y = int(fpoint.y);
    return point;
}
FPoint to_fpoint(Point point)
{
    FPoint fpoint;
    fpoint.x = float(point.x);
    fpoint.y = float(point.y);
    return fpoint;
}
FPoint find_dst(const path_t &path, FPoint current_pos)
{
    for (int i = 0; i < path.size(); i++)
    {
        if (is_equal(current_pos, path[i]) && i != path.size() - 1)
            return path[i + 1];
    }
}
Point find_center(Point point)
{
    Point center;
    center.x = CENTER_OF_FIRST_HOUSE_X+ ((point.x - FIRST_HOUSE_X) / HOUSE_LENGTH) * HOUSE_LENGTH;
    center.y = CENTER_OF_FIRST_HOUSE_Y + ((point.y - FIRST_HOUSE_Y) / HOUSE_LENGTH) * HOUSE_LENGTH;
    return center;
}