#include "Observer.hpp"
#include "Echo.hpp"
#include "Logger.hpp"
#include "Librarian.hpp"
#include "Fred.hpp"
#include "SameSrcAndDst.hpp"
#include "Nonexistence.hpp"
#include "DuplicateName.hpp"
#include <iostream>

using namespace std;

bool Observer::isNameDuplicated(string name)
{
    for (int i = 0; i < channels.size(); i++)
    {
        if (channels[i]->getName() == name)
            return true;
    }
    return false;
}
void Observer::addChannel(string title)
{
    if (isNameDuplicated(title))
        throw DuplicateName();
    Channel *channel = new Channel(title);
    channels.push_back(channel);
}
Channel *Observer::findChannelByName(string name)
{
    for (int i = 0; i < channels.size(); i++)
    {
        if (channels[i]->getName() == name)
            return channels[i];
    }
    throw Nonexistence();
}
void Observer::addEcho(string src, string dst)
{
    if (src == dst)
        throw SameSrcAndDst();
    try
    {
        Echo *echo = new Echo(findChannelByName(src), findChannelByName(dst));
        findChannelByName(src)->registerRobot(echo);
    }
    catch (Nonexistence &error)
    {
        cerr << error.what();
    }
}
void Observer::addLogger(string fileName)
{
    Logger *logger = new Logger(fileName, channels);
    for (int i = 0; i < channels.size(); i++)
    {
        channels[i]->registerRobot(logger);
    }
}
void Observer::addLibrarian(string channel)
{
    try
    {
        Librarian *librarian = new Librarian(findChannelByName(channel));
        findChannelByName(channel)->registerRobot(librarian);
    }
    catch (Nonexistence &error)
    {
        cerr << error.what();
    }
}
void Observer::addFred(string channel)
{
    try
    {
        Fred *fred = new Fred(findChannelByName(channel));
        findChannelByName(channel)->registerRobot(fred);
    }
    catch (Nonexistence &error)
    {
        cerr << error.what();
    }
}
void Observer::sendMessageByUser(std::string channel, std::string message)
{
    try
    {
        findChannelByName(channel)->receiveMessage(message);
    }
    catch (Nonexistence &error)
    {
        cerr << error.what();
    }
}
