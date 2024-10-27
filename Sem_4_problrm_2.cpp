#include <iostream>
#include <cmath>

using namespace std;


struct Book_author {
 
 string name = "Unknown";
 string surname = "Unknown";

};

struct Books {

    string book_name = "Unknown" ;
    Book_author author;

    int year=0 ;
    int pages=0;


};

// создала конструктор объекта структуры вне структуры. Оно работает, так как объект не изменяется, а только создается
// если объект будет изменяться, то лучше функцию лучше писать внутри структуры, чтобы работать непосредственно с объектом, а не его копией
Books CreateBook(string book_name, string author_name, string author_surname, int year, int pages) {
     // название, автора, год издания и количество страниц

    struct Books book; // создала объект структуры

    book.book_name = book_name;
    book.author.name = author_name;
    book.author.surname = author_surname;
    book.year = year;
    book.pages = pages;

return book;

}

void DisplayBook(Books book) { // можем создать эту функция вне структуры так как она 
// не изменяет объект и ничего не возвращает, а только вывод данные об объекте
// если поместить ЭТУ функцию внутрь структуры, ничего не изменится

// book_name, author_name, author_surname, year, pages 
    cout << "Book's name:  " << book.book_name << endl;
    cout << "Author: " << book.author.name << " " << book.author.surname << endl;
    cout << "Year published: " << book.year << endl;
    cout << "Number of pages: " << book.pages << endl;


}




int main() {


Books book1, book2, book3;
Books some_books[3] = {book1, book2, book3};

int size;
string book_name, author_name, author_surname;
int year, pages;


size = sizeof(some_books)/sizeof(some_books[0]);


for (int i=0; i < size; ++i) {

getline(cin, book_name);
getline(cin, author_name);
getline(cin, author_surname);
cin >> year;
cin >> pages;
cin.ignore();
some_books[i] = CreateBook(book_name, author_name, author_surname,
 year, pages);
}


for (int i=0; i<size; i++) {

    DisplayBook(some_books[i]);
    cout << endl;

}

}
