#include "Logger.hpp"
#include <sstream>
#include <fstream>

using namespace std;

Logger::Logger(string initFileName,vector<Channel*> initChannels)
{
    fileName=initFileName;
    channels=initChannels;
}


void Logger::update(std::string message)
{
    messages.push_back(message);
    stringstream receivedMessages;
    ofstream file(fileName);
    for (int i = 0; i < messages.size(); i++)
    {
        receivedMessages <<messages[i]<<"\n";
    }
    file<<receivedMessages.str();
}