#ifndef ARRAY_H
#define ARRAY_H "ARRAY_H"

#include "Data.hpp"
#include <vector>
#include <string>

class Array : public Data
{
private:
    int id;
    std::vector<Data *> datas;

public:
    Array(std::string key_,int id_);
    int getId();
    void print(int parentId);
    void addString(std::string value);
    void addInteger(int value);
    virtual void addContainer(Data* data);
};

#endif