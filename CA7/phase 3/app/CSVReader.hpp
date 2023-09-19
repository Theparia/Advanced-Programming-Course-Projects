#ifndef _CSV_READER_H
#define _CSV_READER_H "_CSV_READER_H"

#include <string>
#include <vector>
#include <map>
#include "Hotel.hpp"

class CSVReader
{
private:
    std::vector<Room *> getTotalRooms(const std::vector<std::string> &data);
    std::vector<Hotel *> addHotel(std::string info, std::vector<Hotel *> hotels);
    void addRooms(int number, std::string type, std::vector<Room *> &rooms);

public:
    std::vector<std::string> parseData(std::string dataLine, char delimiter);
    std::vector<Hotel *> readHotelsData(std::string filePath);
};

#endif