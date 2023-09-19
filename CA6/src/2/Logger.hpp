#ifndef LOGGER_H
#define LOGGER_H "LOGGER_H"

#include "Robot.hpp"
#include <string>
#include "Channel.hpp"

class Logger : public Robot
{
private:
    std::string fileName;
    std::vector <std::string> messages;
    std::vector<Channel*> channels;

public:
    Logger(std::string initFileName,std::vector<Channel*> initChannels);
    virtual void update(std::string message);
};

#endif