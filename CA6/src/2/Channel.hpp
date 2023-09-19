#ifndef CHANNEL_H
#define CHANNEL_H "CHANNEL_H"

#include <string>
#include <vector>
#include "Robot.hpp"

class Channel
{
private:
    std::string name;
    std::vector<Robot *> registered;

public:
    Channel(std::string initName);
    std::string getName();
    void receiveMessage(std::string message);
    void notifyRobots(std::string message);
    virtual void registerRobot(Robot* robot);
};

#endif