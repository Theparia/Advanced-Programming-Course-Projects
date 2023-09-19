#ifndef DATA_H
#define DATA_H "DATA_H"

#include <string>

class Data
{
protected:
    std::string key;
    static int tab;
public:
    std::string getKey();
    virtual void print(int parentId)=0;
    static int printTab();
    bool isThereKey();
};

#endif