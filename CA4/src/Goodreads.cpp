#include <iostream>
#include "Goodreads.hpp"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include "functions.hpp"

using namespace std;

#define COMMA ','
#define DOLLAR '$'
#define NEW_LINE '\n'
#define AUTHORS_FILE "authors.csv"
#define BOOKS_FILE "books.csv"
#define USERS_FILE "users.csv"
#define REVIEWS_FILE "reviews.csv"
#define FOLLOW_EDGES_FILE "follow_edges.csv"
#define SAME_GENRE_SCORE 5
#define NUMBER_OF_BEST_BOOKS 3

vector <User> Goodreads::get_users()
{
	return users;
}
vector <Author> Goodreads::get_authors() 
{ 
	return authors; 
}
vector <Review> Goodreads::get_reviews() 
{ 
	return reviews; 
}
vector <Book> Goodreads::get_books() 
{ 
	return books; 
}
User* Goodreads::find_user_by_id(int id)
{
	for (int i = 0; i<users.size(); i++)
	{
		if (users[i].get_id() == id)
			return &users[i];
	}
}
Book* Goodreads::find_book_by_id(int id)
{
	for (int i = 0; i<books.size(); i++)
	{
	    if (books[i].get_id() == id)
			return &books[i];
	}
}
Author* Goodreads::find_author_by_id(int id)
{
	for (int i = 0; i<authors.size(); i++)
	{
		if (authors[i].get_id() == id)
			return &authors[i];
	}
}
Review* Goodreads::find_review_by_id(int id)
{
	for(int i=0;i<reviews.size();i++)
	{
		if(reviews[i].get_id()==id)
			return &reviews[i];
	}
}
vector <Book*> Goodreads::find_shelf_by_ids(vector <string> ids)
{
	vector <Book*> shelf;
	for(int i=0;i<ids.size();i++)
	{
		shelf.push_back(find_book_by_id(atoi(ids[i].c_str())));
	}
	return shelf;
}
void Goodreads::read_books_info(string address)
{
	string line;
	ifstream file;
	file.open(address +"/"+ BOOKS_FILE);
	file.ignore(std::numeric_limits<std::streamsize>::max(),NEW_LINE);
	while (getline(file,line, NEW_LINE))
	{
		vector <string> data=get_parsed_data(line,COMMA);
		books.push_back(Book(atoi(data[0].c_str()),data[1],find_author_by_id(atoi(data[2].c_str())),data[3]));
	}
	file.close();
}
void Goodreads::read_authors_info(string address)
{
	string line;
	vector <string> genres,data;
	ifstream file;
	file.open(address +"/"+AUTHORS_FILE);
	file.ignore(std::numeric_limits<std::streamsize>::max(),NEW_LINE);
	while (getline(file,line,NEW_LINE))
	{
		data=get_parsed_data(line,COMMA);
		genres=get_parsed_data(data[6],DOLLAR);
		authors.push_back(Author(atoi(data[0].c_str()),data[1],data[2],data[3],atoi(data[4].c_str()),data[5],genres));
	}
	file.close();
}

void Goodreads::read_users_info(string address)
{
	vector <Author*> favorite_authors;
	vector <string> data,favorite_genres,authors_ids,first_shelf,second_shelf,third_shelf;
	vector <Book*> want_to_read,currently_reading,read;
	string line;
	ifstream file;
	file.open(address +"/"+ USERS_FILE);
	file.ignore(std::numeric_limits<std::streamsize>::max(),NEW_LINE);
	while (getline(file, line,NEW_LINE))
	{
		data=get_parsed_data(line,COMMA);
		authors_ids=get_parsed_data(data[4],DOLLAR);
		favorite_genres=get_parsed_data(data[5],DOLLAR);
		for(int i=0;i<authors_ids.size();i++)
		{
			favorite_authors.push_back(find_author_by_id(atoi(authors_ids[i].c_str())));
		}
		want_to_read=find_shelf_by_ids(get_parsed_data(data[6],DOLLAR));
		currently_reading=find_shelf_by_ids(get_parsed_data(data[7],DOLLAR));
		read=find_shelf_by_ids(get_parsed_data(data[8],DOLLAR));
		users.push_back(User(atoi(data[0].c_str()),data[1],data[2],data[3],favorite_authors,favorite_genres,want_to_read,currently_reading,read));
		favorite_authors.clear();
	}
	file.close();
}
void Goodreads::read_reviews_info(string address)
{
	vector <string> data;
	string line;
	ifstream file;
	file.open(address + "/"+ REVIEWS_FILE);
	file.ignore(std::numeric_limits<std::streamsize>::max(), NEW_LINE);
	while (getline(file,line,NEW_LINE))
	{	
		data=get_parsed_data(line,COMMA);
		reviews.push_back(Review(atoi(data[0].c_str()),atoi(data[1].c_str()),atoi(data[2].c_str()),atoi(data[3].c_str()),data[4],atoi(data[5].c_str())));
	}
	file.close();
}
void Goodreads::read_follow_edges_info (string address)
{
	vector <User*> followings;
	ifstream file;
	vector <string> followings_line,data;
	string line;
	file.open(address+"/"+FOLLOW_EDGES_FILE);
	file.ignore(std::numeric_limits<std::streamsize>::max(),NEW_LINE);
    while(getline(file,line,NEW_LINE))
    {
		data=get_parsed_data(line,COMMA);
		followings_line=get_parsed_data(data[1],DOLLAR);
		for(int i=0;i<followings_line.size();i++)
		{
			followings.push_back(find_user_by_id(atoi(followings_line[i].c_str())));
		}
		find_user_by_id(atoi(data[0].c_str()))->set_followings(followings);
		followings.clear();
	}
	file.close();
}
void Goodreads::set_book_reviews()
{
	for(int i=0;i<reviews.size();i++)
	{
		find_book_by_id(reviews[i].get_book_id())->add_review(find_review_by_id(reviews[i].get_id()));
	}
}
void Goodreads::set_user_reviews()
{
	for(int i=0;i<reviews.size();i++)
	{
		find_user_by_id(reviews[i].get_user_id())->add_review(find_review_by_id(reviews[i].get_id()));
	}
}
void Goodreads::read_files_content(string address)
{
	read_authors_info(address);
	read_books_info(address);
	read_users_info(address);
	read_reviews_info(address);
	read_follow_edges_info(address);
	set_book_reviews();
	set_user_reviews();
}
vector <Book> Goodreads::get_author_books(Author* author)
{
	vector <Book> author_books;
	for (int i = 0; i<books.size(); i++)
	{
		if ((books[i]).get_author()->get_id() == author->get_id()) 
        {
			author_books.push_back(books[i]);
		}
	}
	return author_books;
}

bool Goodreads::compare_id(Book b1,Book b2)
{
    return b1.get_id()<b2.get_id();
}
void Goodreads::show_author_info(int id)
{
	Author* author = find_author_by_id(id);
	author->show_author_info();
	cout << "Books:" << endl;
	vector <Book> author_books=get_author_books(author);
	sort(author_books.begin(),author_books.end(),compare_id);
	for (int i = 0; i< author_books.size(); i++)
	{
		author_books[i].show_author_book();
	}
}
int Goodreads:: get_total_number_of_likes()
{
    int likes_no=0;
    for(int i=0;i<reviews.size();i++)
    {
        likes_no+=reviews[i].get_number_of_likes();
    }
    return likes_no;
}
double Goodreads::get_credit(User* user)
{
    return user->calculate_user_credit(user->get_number_of_user_reviews_likes(),get_total_number_of_likes(),user->get_reviews().size(),reviews.size());
}
void Goodreads:: set_books_ratings()
{
	for(int i=0;i<books.size();i++)
	{
		books[i].set_rating(books[i].calculate_avg_rating());
	}
}
bool Goodreads::compare_ratings( Book b1, Book b2)
{
	if(b1.get_rating()==b2.get_rating())
		return b1.get_id()<b2.get_id();
	return b1.get_rating()<b2.get_rating();
}
Book Goodreads::find_best_book()
{
	set_books_ratings();
	sort(books.begin(),books.end(),compare_ratings);
	return books[books.size()-1];
}
void Goodreads:: set_likes_of_user()
{
	for(int i=0;i<users.size();i++)
	{
		users[i].set_likes((find_user_by_id(users[i].get_id()))->get_number_of_user_reviews_likes());
	}
}
bool Goodreads:: compare_likes(User u1,User u2)
{
	if(u1.get_likes()==u2.get_likes())
		return u1.get_id()<u2.get_id();
	return u1.get_likes()<u2.get_likes();
}
User Goodreads:: find_best_reviewer()
{
	set_likes_of_user();
	sort(users.begin(),users.end(),compare_likes);
	return users[users.size()-1];
}
double Goodreads::calculate_book_score(Book* book)
{
	double sum=0,score=0;
	vector <Review*> book_reviews=book->get_reviews();
	if(book_reviews.size()==0)
		return 0;
	for(int i=0;i<book_reviews.size();i++)
	{
		sum+=(book_reviews[i]->get_rating())*(get_credit(find_user_by_id(book_reviews[i]->get_user_id())));
	}
	score=sum/(book_reviews.size());

	return score;
}
void Goodreads::set_all_books_scores(User* user)
{
	double score;
	for(int i=0;i<books.size();i++)
	{
		score=calculate_book_score(&books[i]);
		for(int j=0;j<(user->get_favorite_genres()).size();j++)
	    {
			if(user->get_favorite_genres()[j]==books[i].get_genre())
			{
				score+=SAME_GENRE_SCORE;
				break;
			}
		}
		books[i].set_rating(score);
	}
}
Book Goodreads::find_the_first_recommended_book(int user_id)
{
	User* user=find_user_by_id(user_id);
	set_all_books_scores(user);
	sort(books.begin(),books.end(),compare_ratings);
	return books[books.size()-1];
}
bool Goodreads:: compare_reviews(Review* r1,Review* r2)
{
	return r1->get_id()<r2->get_id();
}
void Goodreads::recommend_first_approach(int user_id)
{
	Book recommended=find_the_first_recommended_book(user_id);
	vector <Review*> book_reviews=recommended.get_reviews();
	recommended.show_book_info_in_shelf();
	sort(book_reviews.begin(),book_reviews.end(),compare_reviews);
	cout<<"Reviews:"<<endl;
	for(int i=0;i<book_reviews.size();i++)
		book_reviews[i]->show();
}
bool Goodreads:: compare_scores(Book* b1,Book* b2)
{
	if(b1->get_rating()==b2->get_rating())
		return b1->get_id()<b2->get_id();
	return b1->get_rating()<b2->get_rating();
}
vector <Book*> Goodreads::find_best_three_books(User* user,vector <Book*> read)
{
	vector <Book*> best_books;
	for(int i=0;i<read.size();i++)
	{
		double score=calculate_book_score(read[i]);
		read[i]->set_rating(score);
	}
	sort(read.begin(),read.end(),compare_scores);
	if(read.size()<=3)
		return read;
	for(int i=1;i<=NUMBER_OF_BEST_BOOKS;i++)
	{
		best_books.push_back(read[read.size()-i]);
	}	
	return best_books;
}
vector <Book*> Goodreads::find_best_books_of_followings(User* user,vector <User*> all_followings)
{
	vector <Book*> best_books,best_three_books;
	for(int i=0;i<all_followings.size();i++)
	{
		best_three_books=find_best_three_books(user,all_followings[i]->get_read());
		for(int j=0;j<best_three_books.size();j++)
			best_books.push_back(best_three_books[j]);
	}
	return best_books;
}
void Goodreads:: set_all_followings(User* user,vector <User*> &all_followings,int id)
{
	for(int i=0;i<user->get_followings().size();i++)
	{
		if(find(all_followings.begin(),all_followings.end(),user->get_followings()[i])!=all_followings.end())
		{
			return;	
		}
		if(user->get_followings()[i]->get_id()!=id)
		{
			all_followings.push_back(user->get_followings()[i]);
		}
		set_all_followings(user->get_followings()[i],all_followings,id);
	}		
}
bool Goodreads:: compare_book_id(Book* b1,Book* b2)
{
	return b1->get_id()< b2->get_id();
}
Book* Goodreads::find_the_second_recommended_book(User* user,vector <User*> all_followings)
{
	vector <Book*> best_books=find_best_books_of_followings(user,all_followings);
	sort(best_books.begin(),best_books.end(),compare_book_id); 
	int max_count = 1, curr_count = 1; 
	Book* recommended=best_books[0];
	for (int i = 1; i < best_books.size(); i++) 
	{ 
		if (best_books[i]->get_id() == best_books[i - 1]->get_id()) 
			curr_count++; 
		else 
		{ 
			if (curr_count > max_count) 
			{ 
				max_count = curr_count; 
				recommended = best_books[i - 1]; 
			} 
			curr_count = 1; 
		} 
	} 
	if (curr_count > max_count) 
	{ 
		max_count = curr_count; 
		recommended = best_books[best_books.size() - 1]; 
	} 
	
	return recommended; 
} 
void Goodreads::recommend_second_approach(int id)
{
	User* user=find_user_by_id(id);
	vector <User*> followings;
	set_all_followings(user,followings,id);
	Book* recommended=find_the_second_recommended_book(user,followings);
	vector <Review*> book_reviews=recommended->get_reviews();
	recommended->show_book_info_in_shelf();
	sort(book_reviews.begin(),book_reviews.end(),compare_reviews);
	cout<<"Reviews:"<<endl;
	for(int i=0;i<book_reviews.size();i++)
		book_reviews[i]->show();
}
