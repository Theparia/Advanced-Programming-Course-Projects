#ifndef GOODREADS_H
#define GOODREADS_H "GOODREADS_H"
#include <vector>
#include <string>
#include "Book.hpp"
#include "Author.hpp"
#include "User.hpp"
#include "Review.hpp"
class Goodreads
{
private:
	std::vector <Author> authors;
	std::vector <Book> books;
	std::vector <Review> reviews;
	std::vector <User> users;
public:
    std::vector <User> get_users();
    std::vector <Author> get_authors();
    std::vector <Review> get_reviews();
    std::vector <Book> get_books();
    User* find_user_by_id(int id);
    Book* find_book_by_id(int id);
    Author* find_author_by_id(int id);
    Review* find_review_by_id(int id);
    std::vector <Book*> find_shelf_by_ids(std::vector <std::string> ids);
    void read_books_info(std::string address);
    void read_authors_info(std::string address);
    void read_users_info(std::string address);
    void read_reviews_info(std::string address);
    void set_book_reviews();
    void set_user_reviews();
    void read_follow_edges_info(std::string address);
    void read_files_content(std::string address);
    std::vector <Book> get_author_books(Author* author);
    static bool compare_id(Book b1,Book b2);
    void show_author_info(int id);
    int get_total_number_of_likes();
    double get_credit(User* user);
    void set_books_ratings();
    static bool compare_ratings( Book b1, Book b2);
    Book find_best_book();
    void set_likes_of_user();
    static bool compare_likes(User u1,User u2);
    User find_best_reviewer();
    double calculate_book_score(Book* book);
    void set_all_books_scores(User* user);
    Book find_the_first_recommended_book(int user_id);
    bool static compare_reviews(Review* r1,Review* r2);
    void recommend_first_approach(int user_id);
    static bool compare_scores(Book* b1,Book* b2);
    std::vector <Book*> find_best_three_books(User* user,std::vector <Book*> read);
    std::vector <Book*> find_best_books_of_followings(User* user,std::vector <User*> all_followings);
    void set_all_followings(User* user,std::vector <User*> &all_followings,int id);
    static bool compare_book_id(Book* b1,Book* b2);
    Book* find_the_second_recommended_book(User* user,std::vector <User*> all_followings);
    void recommend_second_approach(int id);
};


#endif