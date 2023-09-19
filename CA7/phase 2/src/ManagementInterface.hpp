#ifndef _MANAGEMENT_INTERFACE_H_
#define _MANAGEMENT_INTERFACE_H_ "_MANAGEMENT_INTERFACE_H_"

#include "Utrip.hpp"
#include <string>
#include <iostream>
#include "StructsAndDefines.hpp"

class ManagementInterface
{
public:
    ManagementInterface(Utrip *utrip_);
    void parseCommand(std::string command);

private:
    Utrip *utrip;
    std::vector<std::string> split(std::string command, std::size_t wordLimit);
    void handlePostCommand(std::vector<std::string> args);
    void handleGetCommand(std::string args);
    void handleDeleteCommand(std::vector<std::string> args);
    void signup(std::vector<std::string> args);
    void login(std::vector<std::string> args);
    void bookRooms(std::vector<std::string> args);
    void chargeWallet(std::vector<std::string> args);
    void printHotelsInfo(std::string args);
    void deleteReservation(std::vector<std::string> args);
    void printTurnover(std::vector<std::string> args);
    void filterHotels(std::string arg);
    void filterBasedOnCity(std::vector<std::string> args);
    void filterBasedOnStarRating(std::vector<std::string> args);
    void filterBasedOnPrice(std::vector<std::string> args);
    void filterBasedOnDuration(std::vector<std::string> args);
    void filterBasedOnDefaultPrice(std::vector<std::string> args);
    void addComment(std::vector<std::string> args);
    void getComments(std::vector<std::string> args);
    void addRating(std::vector<std::string> args);
    void addManualWeight(std::vector<std::string> args);
    void getRatings(std::vector<std::string> args);
    void sortHotels(std::vector<std::string> args);
   
};

#endif