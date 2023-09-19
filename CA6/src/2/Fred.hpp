#ifndef FRED_H
#define FRED_H

#include "Robot.hpp"
#include <string>
#include "Channel.hpp"

class Fred : public Robot
{
private:
    Channel *channel;

public:
    Fred(Channel* initChannel);
    virtual void update(std::string message);
};

#endif