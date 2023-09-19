#ifndef ECHO_H
#define ECHO_H "ECHO_H"

#include "Robot.hpp"
#include "Channel.hpp"

class Echo : public Robot
{
private:
    Channel *srcChannel;
    Channel *destChannel;

public:
    Echo(Channel* src,Channel* dst);
    virtual void update(std::string message);
};
#endif