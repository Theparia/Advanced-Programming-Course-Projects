#include "Librarian.hpp"

using namespace std;

Librarian::Librarian(Channel *initChannel)
{
    channel = initChannel;
    timeToSendMessage=0;
}

void Librarian::update(string message)
{
    timeToSendMessage++;
    if (timeToSendMessage % 5 == 0 )
    {
        channel->receiveMessage("Quiet!");
    }
}