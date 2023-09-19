#include "Observer.hpp"
#include "functions.hpp"
#include <iostream>

using namespace std;

int main()
{
    Observer* observer=new Observer();
    doCommand(observer);
}