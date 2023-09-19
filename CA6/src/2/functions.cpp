#include "functions.hpp"
#include "DuplicateName.hpp"
#include "SameSrcAndDst.hpp"
#include <iostream>
#include <string>

using namespace std;

#define ADD_CHANNEL_PHRASE "add_channel"
#define ADD_BOT_PHRASE "add_bot"
#define TELL_PHRASE "tell"
#define ECHO_BOT "echo"
#define LOGGER_BOT "logger"
#define LIBRARIAN_BOT "librarian"
#define FRED_BOT "fred"

void addChannel(Observer *observer)
{
    try
    {
        string name;
        cin >> name;
        observer->addChannel(name);
    }
    catch (DuplicateName &error)
    {
        cerr << error.what();
    }
}
void addEchoBot(Observer *observer)
{
    try
    {
        string src_channel, dst_channel;
        cin >> src_channel >> dst_channel;
        observer->addEcho(src_channel, dst_channel);
    }
    catch (SameSrcAndDst &error)
    {
        cerr << error.what();
    }
}
void addLoggerBot(Observer *observer)
{
    string fileName;
    cin >> fileName;
    observer->addLogger(fileName);
}
void addLibrarianBot(Observer *observer)
{
    string channelName;
    cin >> channelName;
    observer->addLibrarian(channelName);
}
void addFredBot(Observer *observer)
{
    string channelName;
    cin >> channelName;
    observer->addFred(channelName);
}
void addBot(Observer *observer)
{
    string robotName;
    cin >> robotName;
    if (robotName == ECHO_BOT)
    {
        addEchoBot(observer);
    }
    if (robotName == LOGGER_BOT)
    {
        addLoggerBot(observer);
    }
    if (robotName == LIBRARIAN_BOT)
    {
        addLibrarianBot(observer);
    }
    if (robotName == FRED_BOT)
    {
        addFredBot(observer);
    }
}
void tell(Observer *observer)
{
    string channel, message;
    cin >> channel;
    getline(cin, message);
    message = message.substr(1);
    observer->sendMessageByUser(channel, message);
}
void doCommand(Observer *observer)
{
    string command;
    while (cin >> command)
    {
        if (command == ADD_CHANNEL_PHRASE)
        {
            addChannel(observer);
        }
        if (command == ADD_BOT_PHRASE)
        {
            addBot(observer);
        }
        if (command == TELL_PHRASE)
        {
            tell(observer);
        }
    }
}
