#ifndef BOOK_H
#define BOOK_H "BOOK_H"
#include <string>
#include <vector>
#include "Review.hpp"

class Author;
class Book
{
private:
	int id;
	std::string title;
	std::string genre;
	Author* author;
	double rating;
    std::vector <Review*> reviews;
public:
    Book(int init_id,std:: string init_title, Author* init_author,std::string init_genre);
    int get_id();
    std::string get_title();
    std::string get_genre();
    Author* get_author();
    double get_rating();
    std::vector <Review*> get_reviews();
    void add_review(Review* review);
    void set_rating(double new_rating);
    void show_book_info_in_shelf();
    double calculate_avg_rating();
    void show_best_book();
    void show_author_book();
};
#endif