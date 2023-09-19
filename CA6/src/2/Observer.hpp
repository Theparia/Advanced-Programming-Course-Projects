#ifndef OBSERVER_H
#define OBSERVER_H "OBSERVER_H"

#include "Robot.hpp"
#include "Channel.hpp"
#include <vector>
#include <string>

class Observer
{
private:
    std::vector<Channel *> channels;

public:
    bool isNameDuplicated(std::string name);
    void addChannel(std::string title);
    Channel* findChannelByName(std::string name);
    void addEcho(std::string src,std::string dst);
    void addLogger(std::string fileName);
    void addLibrarian(std::string channel);
    void addFred(std::string channel);
    void sendMessageByUser(std::string channel,std::string message);
};

#endif
