#ifndef LIBRARIAN_H
#define LIBRARIAN_H "LIBRARIAN_H"

#include "Robot.hpp"
#include "Channel.hpp"
#include <string>

class Librarian : public Robot
{
private:
    Channel* channel;
    int timeToSendMessage ;

public:
    Librarian(Channel* initChannel);
    void update(std::string message);
};

#endif