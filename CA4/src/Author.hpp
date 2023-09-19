#ifndef AUTHOR_H
#define AUTHOR_H "AUTHOR_H"

#include <vector>
#include <string>

class Author
{
private:
	int id;
	std::string name;
	std::string gender;
	std::string member_since;
	int year_of_birth;
	std::string place_of_birth;
	std::vector <std::string> genres;
public:
    Author(int init_id,std:: string init_name,std:: string init_gender, std::string init_member_since, int init_year_of_birth, std::string init_place_of_birth,std:: vector <std::string> init_genres);
    int get_id();
    std::string get_name();
    std::string get_gender();
    std::string get_member_since();
    int get_year_of_birth();
    std::string get_place_of_birth();
    std::vector <std::string> get_genres();
    static bool compare_genres(std::string s1,std::string s2);
    void show_author_info();
};

#endif