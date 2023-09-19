#include "Channel.hpp"

using namespace std;

Channel::Channel(string initName)
{
    name=initName;
}
string Channel::getName()
{
    return name;
}

void Channel::receiveMessage(string message)
{
    notifyRobots(message);
}
void Channel::notifyRobots(string message)
{
    for (int i = 0; i < registered.size(); i++)
        registered[i]->update(message);
}

void Channel::registerRobot(Robot* robot)
{
    registered.push_back(robot);
}