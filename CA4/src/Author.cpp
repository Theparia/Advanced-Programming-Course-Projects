#include <algorithm>
#include <iostream>
#include "Author.hpp"

using namespace std;

Author::Author(int init_id, string init_name, string init_gender, string init_member_since, int init_year_of_birth, string init_place_of_birth, vector <string> init_genres)
{
	id = init_id;
	name = init_name;
	gender = init_gender;
	member_since = init_member_since;
	year_of_birth = init_year_of_birth;
	place_of_birth = init_place_of_birth;
	genres = init_genres;
}
int Author:: get_id() 
{
	return id; 
}
string Author:: get_name() 
{ 
	return name; 
}
string Author::get_gender() 
{ 
	return gender; 
}
string Author:: get_member_since() 
{ 
	return member_since; 
}
int Author::get_year_of_birth() 
{ 
	return year_of_birth; 
}
string Author::get_place_of_birth() 
{ 
	return place_of_birth; 
}
vector <string> Author::get_genres() 
{ 
	return genres; 
}
bool Author::compare_genres(string s1,string s2)
{
	return s1<s2;
}
void Author::show_author_info()
{
	cout << "id: " << id << endl;
	cout << "Name: " << name << endl;
	cout << "Year of Birth: " << year_of_birth << endl;
	cout << "Place of Birth: " << place_of_birth << endl;
	cout << "Member Since: " << member_since << endl;
	cout << "Genres: ";
	sort(genres.begin(),genres.end(),compare_genres);
	for (int i = 0; i<genres.size(); i++)
	{
		if (i == genres.size() - 1)
			cout << genres[i] << endl;
		else
			cout << genres[i] << ", ";
	}
}