#ifndef FUNCTIONS_H
#define FUNCTIONS_H "FUNCTIONS_H"
#include <string>
#include "Goodreads.hpp"

void do_command(Goodreads goodreads);
void process_output(std::string command, Goodreads goodreads);
std::vector <std::string> get_parsed_data(std::string line,char delimiter);

#endif