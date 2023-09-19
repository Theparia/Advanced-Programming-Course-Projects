#include "Utrip.hpp"
#include "ManagementInterface.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Utrip *utrip = new Utrip(argv[1], argv[2]);
    ManagementInterface managementInterface(utrip);
    string command;
    while (getline(cin, command))
    {
        managementInterface.parseCommand(command);
    }
}