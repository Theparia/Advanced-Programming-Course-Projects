#include "Data.hpp"
#include <iostream>

using namespace std;

#define TAB "    "

int Data::tab = 0;

string Data::getKey()
{
    return key;
}
int Data::printTab()
{
    for (int i = 0; i < tab; i++)
    {
        cout << TAB;
    }
}
bool Data::isThereKey()
{
    if (key != "")
        return true;
    return false;
}