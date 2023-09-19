#include "Echo.hpp"

using namespace std;

void Echo::update(std::string message)
{
    destChannel->receiveMessage(message);
}
Echo:: Echo(Channel* src,Channel* dst)
{
    srcChannel=src;
    destChannel=dst;
}