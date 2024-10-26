#include <iostream>
#include <cmath>

using namespace std;


struct Book_aughor {
 
 string name;
 string surname;

};

struct Books {

    string book_name ;
    Book_aughor author;

    int year ;
    int pages;

    Book() {

book_name = "Unknown";
Book_author.name = "Unknown";
Book_aughor.surname = "Unknown";

year = 0;
paged = 0;


    };

};



int main() {

Books book;

cout << "Name of the book";
getline(cin, book.book_name);

cout << "Augtor's of the book";
 getline(cin, book.name);

 cout << "Author's surname";
 getline(cin, book.surname);

 cout << "Published year";
 cin >> book.year;

 cout << "Page number";
cin >> book.pages;





}