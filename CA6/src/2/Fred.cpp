#include "Fred.hpp"

using namespace std;

#define HI "Hi"
#define HELLO "Hello"

void Fred::update(std::string message)
{
    if(message==HI)
    {
        channel->receiveMessage(HELLO);
    }
}
Fred:: Fred(Channel* initChannel)
{
    channel=initChannel;
}