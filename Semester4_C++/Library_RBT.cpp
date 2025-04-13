#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <random>
#include <chrono>

using namespace std;

// Структура для хранения информации о книге
struct Book {
    int id;
    string author;
    string title;

    void Print() const {
        cout << "ID: " << id << ", Author: " << author << ", Title: " << title << endl;
    }
};

class Library {
public:
    map<int, Book> books; // Используем map, где ключ - id книги, значение - Book

    Library() {}

    void AddBook(const Book& book) {
        auto start = chrono::high_resolution_clock::now();
        books[book.id] = book; // Добавляем книгу в map по id
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // microseconds для большей точности
        insertionTime += duration.count();
    }

    void DeleteBook(int id) {
        books.erase(id); // Удаляем книгу из map по id
    }

    Book* FindBook(int id) {
        auto start = chrono::high_resolution_clock::now();
        auto it = books.find(id); // Ищем книгу в map по id
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start); // microseconds для большей точности
        findTime += duration.count();

        if (it != books.end()) {
            it->second.Print(); // Выводим информацию о книге
            return &it->second; // Возвращаем указатель на найденную книгу
        } else {
            cout << "Book with ID " << id << " not found" << endl;
            return nullptr; // Возвращаем nullptr, если книга не найдена
        }
    }

    void PrintAllBooksToFile(const string& filename) {
        ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        outputFile << "All books in the library (sorted by ID):" << endl;
        for (const auto& [id, book] : books) { // Итерируемся по map
            outputFile << "ID: " << book.id << ", Author: " << book.author << ", Title: " << book.title << endl;
        }
        outputFile.close();
        cout << "Book list written to file: " << filename << endl;
    }

    long long getTotalInsertionTime() const { return insertionTime; } // Getters для времени
    long long getTotalFindTime() const { return findTime; }

private:
    long long insertionTime = 0; // Общее время в микросекундах, затраченное на вставку
    long long findTime = 0; // Общее время в микросекундах, затраченное на поиск
};

// Функция для генерации случайной строки
string generateRandomString(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; // Include space
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, characters.size() - 1);
    string randomString = "";
    for (int i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }
    return randomString;
}

int main() {
    Library myLibrary;

    // Генерация 10000 случайных книг
    int numBooks = 10000;
    cout << "Generating " << numBooks << " random books..." << endl;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i <= numBooks; ++i) { // Start ID from 1
        Book book;
        book.id = i;
        book.author = generateRandomString(20);
        book.title = generateRandomString(30);
        myLibrary.AddBook(book);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Generated and added " << numBooks << " books in " << duration.count() << " ms" << endl;

    // Вывод всех книг в файл
    myLibrary.PrintAllBooksToFile("library_catalog.txt");

    cout << "Total insertion time: " << myLibrary.getTotalInsertionTime() << " microseconds" << endl;
    cout << "Total find time: " << myLibrary.getTotalFindTime() << " microseconds" << endl;

    return 0;
}