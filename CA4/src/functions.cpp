#include "functions.hpp"
#include <iostream>
#include "Book.hpp"
#include "User.hpp"
#include <iomanip>
#include <sstream>

using namespace std;

#define SHOW_AUTHOR_INFO_PHRASE "show_author_info"
#define SHOW_SORTED_SHELF_PHRASE "show_sorted_shelf"
#define CREDIT_PHRASE "credit"
#define BEST_BOOK_PHRASE "best_book"
#define BEST_REVIEWER_PHRASE "best_reviewer"
#define RECOMMEND_FIRST_APPROACH_PHRASE "recommend_first_approach"
#define RECOMMEND_SECOND_APPROACH_PHRASE "recommend_second_approach"

void process_output(string command, Goodreads goodreads)
{
	int id;
	if (command == SHOW_AUTHOR_INFO_PHRASE)
	{
		cin >> id;
		goodreads.show_author_info(id);
	}
	if (command == SHOW_SORTED_SHELF_PHRASE)
	{
		string shelf_type, genre;
		cin >> id >> shelf_type;
		getline(cin,genre);
		genre=genre.substr(1);
		goodreads.find_user_by_id(id)->show_sorted_shelf(shelf_type,genre);
	}
    if(command == CREDIT_PHRASE)
    {
        cin>>id;
        User* user=goodreads.find_user_by_id(id);
        cout<<fixed<<setprecision(6)<<goodreads.get_credit(user)<<endl;
    }
	if(command==BEST_BOOK_PHRASE)
	{
		Book book=goodreads.find_best_book();
		book.show_best_book();
	}
	if(command==BEST_REVIEWER_PHRASE)
	{
		User user=goodreads.find_best_reviewer();
		user.show_best_reviewer();
	}
	if(command==RECOMMEND_FIRST_APPROACH_PHRASE)
	{
		cin>>id;
		goodreads.recommend_first_approach(id);
	}
		if(command==RECOMMEND_SECOND_APPROACH_PHRASE)
	{
		cin>>id;
		goodreads.recommend_second_approach(id);
	}
}
void do_command(Goodreads goodreads)
{
	string command;
	while(cin>>command)
	{
		process_output(command,goodreads);
	}
}
vector <string> get_parsed_data(string data_line,char delimiter)
{
	string line;
	vector <string> data;
	stringstream file(data_line);
	while(getline(file,line,delimiter))
	{
		data.push_back(line);
	}
	return data;
}