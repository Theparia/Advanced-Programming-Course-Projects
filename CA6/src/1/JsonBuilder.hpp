#ifndef JSON_BUILDER_H
#define JSON_BUILDER_H "JSON_BUILDER_H"

#include <vector>
#include <string>
#include "Object.hpp"
#include "Array.hpp"

class JsonBuilder
{
private:
    std::vector<Object *> objects;
    std::vector<Array*> arrays;
    static int idNumber;
public:
    JsonBuilder();
    Object *findObjectById(int id);
    Array* findArrayById(int id);
    void print(int id);
    static void produceIdNumber();
    void addStringToObject(int parentId, std::string key, std::string value);
    void addIntegerToObject(int parentId, std::string key, int value);
    int addContainerToObject(int parentId,std::string key,std::string type);
    void addObjectToObject(int parentId,std::string key);
    void addArrayToObject(int parentId,std::string key);
    void addStringToArray(int parentId,std::string value);
    void addIntegerToArray(int parentId,int value);
    int addContainerToArray(int parentId,std::string type);
    void addObjectToArray(int parentId);
    void addArrayToArray(int parentId);

};

#endif
